#pragma once
#include "packet.h"
class httppacket
	: public packet
{
public:
	httppacket();
	~httppacket();
	
protected:
	double httpVersion;
	std::string method;
};

