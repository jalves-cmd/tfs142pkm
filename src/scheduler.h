// Copyright 2022 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#ifndef FS_SCHEDULER_H_2905B3D5EAB34B4BA8830167262D2DC1
#define FS_SCHEDULER_H_2905B3D5EAB34B4BA8830167262D2DC1

// INTERNAL PATCH NOTE (2026-02-09):
// Boost/Asio compat (vcpkg Boost >= 1.80+):
// - Replace io_context::work with executor_work_guard (make_work_guard).
// - Keep behavior: keep io_context alive until shutdown().

#include "tasks.h"
#include "thread_holder_base.h"

#include <atomic>
#include <unordered_map>

#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/executor_work_guard.hpp>

static constexpr int32_t SCHEDULER_MINTICKS = 50;

class SchedulerTask : public Task
{
	public:
		void setEventId(uint32_t id) {
			eventId = id;
		}
		uint32_t getEventId() const {
			return eventId;
		}

		uint32_t getDelay() const {
			return delay;
		}
	private:
		SchedulerTask(uint32_t delay, TaskFunc&& f) : Task(std::move(f)), delay(delay) {}

		uint32_t eventId = 0;
		uint32_t delay = 0;

		friend SchedulerTask* createSchedulerTask(uint32_t, TaskFunc&&);
};

SchedulerTask* createSchedulerTask(uint32_t delay, TaskFunc&& f);

class Scheduler : public ThreadHolder<Scheduler>
{
	public:
		Scheduler() :
			work_guard(boost::asio::make_work_guard(io_context))
		{}

		uint32_t addEvent(SchedulerTask* task);
		void stopEvent(uint32_t eventId);

		void shutdown();

		void threadMain() { io_context.run(); }
	private:
		std::atomic<uint32_t> lastEventId{0};
		std::unordered_map<uint32_t, boost::asio::steady_timer> eventIdTimerMap;

		boost::asio::io_context io_context;
		boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard;
};

extern Scheduler g_scheduler;

#endif
