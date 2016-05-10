#pragma once
#include "packet.h"
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>

typedef void(*packethandler)(packet);

class packetparser
{
public:
	packetparser(packethandler handler)
	{
		_handler = handler;
		_packet.clear();
		_status = command;
	};
	void buffer(const char* data)
	{
		if (strlen(data) > 0)
			_buffer += data;
		parse();
	};

private:
	void parse()
	{
		size_t index = 0;
		if ((index = _buffer.find("\r\n")) != std::string::npos)
		{
			if (_status == command) 
			{
				_packet.command = boost::algorithm::to_upper_copy(_buffer.substr(0, index)).c_str();
				_buffer.erase(0, index + 2);
				parse();
			}
			else if (_status == header)
			{

			}
		}
	}

	enum parsestatus {
		command,
		header,
		payload
	};

	packet _packet;
	size_t contentlength = 0;
	std::string _buffer;
	packethandler _handler;
	parsestatus _status;
};