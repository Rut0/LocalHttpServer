#pragma once
#include "packet.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

class packetparser
{
public:
	packetparser()
	{
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
				_buffer.erase(0, index + 2); // Erase command from buffer
				_status = header;
			}
			if (_status == header)
			{
				int eoh = 0;
				if ((eoh = _buffer.find("\r\n\r\n")) != std::string::npos)
				{
					std::string headers = _buffer.substr(0, eoh);
					_buffer.erase(0, eoh + 4); // Erase headers from buffer
					// Parse header
					int hindex;
					int del;
					std::string header;
					while (headers.length() > 0)
					{
						hindex = _buffer.find("\r\n");
						header = headers.substr(0, hindex);
						headers.erase(0, hindex + 2);
						del = header.find(": ");
						_packet.addheader(boost::algorithm::to_upper_copy(header.substr(0, del)), header.substr(del + 2));
					}
					// Erase header-payload delimeter
					_buffer.erase(0, 2);
					_status = command;
					if (_packet.hasheader("CONTENT-LENGTH"))
					{
						_contentlength = atoi(_packet.getheader("CONTENT-LENGTH").c_str());
						_status = payload;
					}
					else
					{
						finalize();
					}
				}
			}
			if (_status == payload)
			{
				if (_buffer.length() < _contentlength) return;
				_packet.payload = _buffer.substr(0, _contentlength).c_str();
				_buffer.erase(0, _contentlength);
				_status = command;
				finalize();
			}
			parse();
		}
	}

	void finalize()
	{
		//_session.handlepacket(_packet);
		_packet.clear();
	};

	enum parsestatus {
		command,
		header,
		payload
	};

	packet _packet;
	size_t _contentlength = 0;
	std::string _buffer;
	parsestatus _status;
};