#include "tcpsession.h"
#include "util.h"


tcpsession::tcpsession(tcp::socket socket)
	: _socket(std::move(socket))
{
	
}


tcpsession::~tcpsession()
{
}

void tcpsession::begin_read()
{
	auto self(shared_from_this());
	_socket.async_read_some(boost::asio::buffer(_data, 1024),
		[this, self](boost::system::error_code ec, std::size_t len)
	{
		if (!ec)
		{
			// No error, message received
			util::log("message received:");
			
			begin_read();
		}
	});
}

void tcpsession::handlepacket(packet p)
{
	std::cout << p.debug() << std::endl;
}
