#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include "tcpserver.h"
#include "util.h"

int main()
{
	try
	{
		util::rootdirectory = boost::filesystem::initial_path<boost::filesystem::path>().string();
		std::cout << "Root Directory is: " << util::rootdirectory << std::endl;
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