// Copyright 2022 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

// INTERNAL PATCH NOTE (2026-02-09):
// Boost/Asio compat (vcpkg Boost >= 1.80+):
// - Use io_context + executor_work_guard (make_work_guard).
// - Map emplace uses piecewise_construct to build steady_timer in-place.

#include "scheduler.h"
#include "dispatcher.h"

Scheduler g_scheduler;

SchedulerTask* createSchedulerTask(uint32_t delay, TaskFunc&& f)
{
	return new SchedulerTask(delay, std::move(f));
}

uint32_t Scheduler::addEvent(SchedulerTask* task)
{
	uint32_t eventId = ++lastEventId;
	task->setEventId(eventId);

	auto [it, inserted] = eventIdTimerMap.emplace(
		std::piecewise_construct,
		std::forward_as_tuple(eventId),
		std::forward_as_tuple(io_context)
	);

	auto& timer = it->second;
	timer.expires_from_now(std::chrono::milliseconds(task->getDelay()));
	timer.async_wait([this, task](const boost::system::error_code& error) {
		eventIdTimerMap.erase(task->getEventId());
		delete task;

		if (error) {
			return;
		}

		g_dispatcher.addTask(task);
	});

	return eventId;
}

void Scheduler::stopEvent(uint32_t eventId)
{
	auto it = eventIdTimerMap.find(eventId);
	if (it != eventIdTimerMap.end()) {
		it->second.cancel();
		eventIdTimerMap.erase(it);
	}
}

void Scheduler::shutdown()
{
	// release work guard so run() can exit once no pending ops
	work_guard.reset();
	io_context.stop();
}
