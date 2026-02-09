// Copyright 2022 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

// INTERNAL PATCH NOTE (2026-02-09):
// Boost/Asio compat: io_service is deprecated/removed with newer Boost (vcpkg Boost 1.90).
// Changes: io_service -> io_context.

#include "connection.h"
#include "service_port.h"
#include "connection.h"
#include "outputmessage.h"
#include "protocol.h"
#include "scheduler.h"

Connection_ptr ConnectionManager::createConnection(boost::asio::io_context& io_service, ConstServicePort_ptr servicePort)
{
	auto connection = std::make_shared<Connection>(io_service, std::move(servicePort));
	return connection;
}
