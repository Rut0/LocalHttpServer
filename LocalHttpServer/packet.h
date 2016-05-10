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
	const char* serialize();
	const char* command;
	std::map<std::string, std::string> headers;
	const char* payload;
};

