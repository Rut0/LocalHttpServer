#include "tcpsession.h"
#include "util.h"
#include <functional>

tcpsession::tcpsession(tcp::socket socket)
	: _socket(std::move(socket))
{
	
}


tcpsession::~tcpsession()
{
}

void tcpsession::begin_read()
{
	_parser.handler = std::bind(&tcpsession::handlepacket, this, std::placeholders::_1);
	auto self(shared_from_this());
	_socket.async_read_some(boost::asio::buffer(_data, 1024),
		[this, self](boost::system::error_code ec, std::size_t len)
	{
		if (!ec)
		{
			// No error, message received
			util::log("message received:");
			//std::cout << std::string(_data, len) << std::endl;
			_parser.buffer(std::string(_data, len));
			begin_read();
		}
	});
}

void tcpsession::handlepacket(packet p)
{
	//std::cout << p.debug() << std::endl;
	if (p.command.substr(0, 3) == "GET")
	{
		std::string file = util::getfile("/");
		std::string data = util::readcontent(file);
		auto self(shared_from_this());
		_socket.async_write_some(boost::asio::buffer(data),
			[this, self](boost::system::error_code ec, std::size_t len)
		{
			if (!ec) {
				util::log("SENT DATA");
			} else {
				util::log("ERROR SEND DATA");
			}
		});
	}
}
