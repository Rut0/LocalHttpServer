#include "tcpserver.h"
#include "util.h"
#include <sstream>

tcpserver::tcpserver(boost::asio::io_service& io_serv, int port)
	: _acceptor(io_serv, tcp::endpoint(tcp::v4(), port)), _socket(io_serv)
{
	util::log("Begin accept on port: " + std::to_string(port));
	begin_accept();
}


tcpserver::~tcpserver()
{
}

void tcpserver::begin_accept()
{
	_acceptor.async_accept(_socket, [this](boost::system::error_code ec)
	{
		std::stringstream ss;
		ss << "Accepted: " << ++_incrementor;
		util::log(ss.str().c_str());
		if (!ec) {
			std::make_shared<tcpsession>(std::move(_socket))->begin_read();
		}
		begin_accept();
	});
}