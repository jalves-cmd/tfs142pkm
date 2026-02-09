// Copyright 2022 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#ifndef FS_CONNECTION_H_5B8D0E9A4D4D4AA8A16A5E3F0C58F4F0
#define FS_CONNECTION_H_5B8D0E9A4D4D4AA8A16A5E3F0C58F4F0

// INTERNAL PATCH NOTE (2026-02-09):
// Boost/Asio compat: io_service is deprecated/removed with newer Boost (vcpkg Boost 1.90).
// Changes: io_service -> io_context.
// Also remove hard include on service_port.h and use forward declarations to avoid include path issues.

#include <memory>
#include <boost/asio/io_context.hpp>

class ServicePort;
using ConstServicePort_ptr = std::shared_ptr<const ServicePort>;

class Connection;
using Connection_ptr = std::shared_ptr<Connection>;

class ConnectionManager
{
	public:
		Connection_ptr createConnection(boost::asio::io_context& io_service, ConstServicePort_ptr servicePort);
};

#endif
