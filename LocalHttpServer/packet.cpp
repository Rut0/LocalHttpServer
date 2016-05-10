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
	command = { '\0' };
	headers.clear();
	payload = { '\0' };
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

const char* packet::serialize()
{
	return{ '\0' };
}