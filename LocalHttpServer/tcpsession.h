#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "packetparser.h"
#include "packet.h"

using boost::asio::ip::tcp;

class tcpsession
	: public std::enable_shared_from_this<tcpsession>
{
public:
	tcpsession(tcp::socket socket);
	~tcpsession();
	void begin_read();
	typedef void(*handler)(packet* param);
	void handlepacket(packet);

private:
	tcp::socket _socket;
	char _data[1024];
	packetparser _parser;
};

