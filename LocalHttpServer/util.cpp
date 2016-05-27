#include "util.h"
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>

std::string util::rootdirectory = "";

void util::log(std::string ch)
{
	std::cout << ch << std::endl;
}

std::string util::getfile(std::string path)
{
	std::string full = util::rootdirectory + path;
	if (path.back() == '/')
	{
		std::string defaultpath = util::getdefaultfile(full);
	}
	return "";
}

std::string util::getdefaultfile(std::string path)
{
	boost::filesystem::directory_iterator it(path);
	for (; it != boost::filesystem::directory_iterator(); ++it)
	{
		if (boost::filesystem::is_regular_file(*it))
		{
			std::string filename = it->path().filename().string();
			if (boost::starts_with(filename, "index"))
			{
				return it->path().string();
			}
		}
	}
	return "ERROR";
}

std::string util::readcontent(std::string path)
{
	boost::filesystem::ifstream fin;
	fin.open(path.c_str(), std::ios::in);
	std::stringstream ss;
	ss << fin.rdbuf();
	return ss.str();
}