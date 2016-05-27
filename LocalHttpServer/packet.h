#pragma once
#include <map>
class packet
{
public:
	packet();
	~packet();
	void clear();
	void addheader(std::string, std::string);
	bool hasheader(std::string);
	std::string getheader(std::string);
	std::string serialize();
	std::string debug();
	std::string command;
	std::map<std::string, std::string> headers;
	std::string payload;
};

