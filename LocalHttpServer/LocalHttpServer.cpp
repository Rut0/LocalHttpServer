#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <boost/asio.hpp>
#include "tcpserver.h"

int main()
{
	try
	{
		int port = 80;
		boost::asio::io_service io_serv;
		tcpserver s(io_serv, port);
		io_serv.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

}