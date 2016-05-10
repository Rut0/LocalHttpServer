#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "tcpsession.h"

using boost::asio::ip::tcp;

class tcpserver
	: public std::enable_shared_from_this<tcpserver>
{
public:
	tcpserver(boost::asio::io_service&, int);
	~tcpserver();

private:
	void begin_accept();
	int _incrementor = 0;
	tcp::acceptor _acceptor;
	tcp::socket _socket;
};

