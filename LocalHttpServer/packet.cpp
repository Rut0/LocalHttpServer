#include "packet.h"
#include <boost/algorithm/string.hpp>    

packet::packet()
{
	clear();
}

packet::~packet()
{
	clear();
}

void packet::clear()
{
	command = "";
	headers.clear();
	payload = "";
}

void packet::addheader(std::string key, std::string value)
{
	headers[key] = value;
}

bool packet::hasheader(std::string key)
{
	return headers.find(key) == headers.end();
}

std::string packet::getheader(std::string key)
{
	return headers[key];
}

std::string packet::serialize()
{
	return "";
}

std::string packet::debug()
{
	std::string msg = "---\nCommand: " + std::string(command);
	msg += "\n";
	msg += "Header Count: ";
	msg += std::to_string(headers.size());
	msg += "\n";
	if (hasheader("CONTENT-LENGTH"))
	{
		msg += "Content-Length: " + getheader("CONTENT-LENGTH");
		msg += "\n";
		msg += "Payload Size: ";
		msg += std::to_string(payload.size());
		msg += "\n";
	}
	msg += "---";
	return msg;
};