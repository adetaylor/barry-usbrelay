///
/// \file	brimtrans.cc
///		Translates log files generated by RIM's USB driver
///		into something more or less readable.
///

/*
    Copyright (C) 2005-2010, Net Direct Inc. (http://www.netdirect.ca/)
    Copyright (C) 2009, Josh Kropf

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    See the GNU General Public License in the COPYING file at the
    root directory of this project for more details.
*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <cctype>
#include <stdint.h>
#include "i18n.h"

using namespace std;

string trim_right(const string& source , const string& t = " ");
string trim_data_line(const string& line);
void dump(const list<string>& event);
void parse_hex(const string& source, vector<uint16_t>& data);
void print_hex(const vector<uint16_t>& data);

int main(int argc, char* argv[])
{
	list<string>* event = NULL;
	string line;

	INIT_I18N(PACKAGE);

	while( !getline(cin, line).eof() ) {
		size_t pos = line.find_first_of(':');

		// skip lines missing colon
		if( pos == string::npos )
			continue;

		line = trim_right(line.substr(pos + 2), "\n\r ");

		// each sequence of write/read packets begins with this line
		if( line == "BbUsbDevice: WriteToDevice" ) {
			if( event != NULL ) {
				dump(*event);
				delete event;
			}

			event = new list<string>;
		}
		else if( line.substr(0, 3) == "<-:" ) { // send to device
			event->push_front(trim_data_line(line.erase(0, 3)));
		}
		else if( line.substr(0, 3) == "->:" ) { // receive from device
			event->push_back(trim_data_line(line.erase(0, 3)));
		}
	}

	if( event != NULL ) {
		dump(*event);
		delete event;
	}

	return 0;
}

string trim_right(const string& source , const string& t)
{
	string str = source;
	return str.erase(str.find_last_not_of(t) + 1);
}

string trim_data_line(const string& line)
{
	size_t pos = line.find_first_of(':');
	return line.substr(pos + 2);
}

void dump(const list<string>& event)
{
	vector<uint16_t> data;
	list<string>::const_iterator i, begin = event.begin(), end = event.end();
	for( i=begin; i != end; ++i ) {
		data.clear();
		parse_hex(*i, data);
		cout << (i == begin? "Send" : "Receive") << endl;
		print_hex(data);
	}
	cout << endl;
}

void parse_hex(const string& source, vector<uint16_t>& data)
{
	istringstream ss(source);
	uint16_t byte;

	while( !ss.eof() ) {
		ss >> hex >> byte;
		data.push_back(byte);
	}
}

void print_hex(const vector<uint16_t>& data)
{
	int remaining = data.size(), offset = 0;
	do {
		cout << "    " << hex << setfill('0') << setw(8) << offset;
		int margin = 13;

		for( int i=0, stop=min(16, remaining); i<stop; i++ ) {
			cout << ' ' << hex << setfill('0') << setw(2) << data[offset + i];
			margin += 3;
		}

		cout << string(62-margin, ' ');

		for( int i=0, stop=min(16, remaining); i<stop; i++) {
			char c = data[offset + i];
			cout << (isprint(c)? c : '.');
		}

		offset += 16;
		remaining -= 16;

		cout << endl;
	} while( remaining > 0 );
}
