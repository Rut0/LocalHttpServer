#pragma once
#include <iostream>
#include <string>

class util
{
public:
	static void log(std::string);
	static std::string getfile(std::string);
	static std::string rootdirectory;
	static std::string getdefaultfile(std::string);
	static std::string readcontent(std::string);
};

