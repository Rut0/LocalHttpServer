#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class tcpsession
	: public std::enable_shared_from_this<tcpsession>
{
public:
	tcpsession(tcp::socket socket);
	~tcpsession();
	void begin_read();

private:
	tcp::socket _socket;
	char _data[1024];
};

