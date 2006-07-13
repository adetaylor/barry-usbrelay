///
/// \file	upldif.cc
///		LDIF contact uploader
///

/*
    Copyright (C) 2006, Net Direct Inc. (http://www.netdirect.ca/)

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

#include "barry.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <getopt.h>


using namespace std;
using namespace Barry;

void Usage()
{
   cerr
   << "upldif - Command line LDIF uploader\n"
   << "        Copyright 2006, Net Direct Inc. (http://www.netdirect.ca/)\n\n"
   << "   -p pin    PIN of device to talk with\n"
   << "             If only one device plugged in, this flag is optional\n"
   << "   -u        Do the upload.  If not specified, only dumps parsed\n"
   << "             LDIF data to stdout.\n"
   << "   -v        Dump protocol data during operation\n"
   << endl;
}

class Ldif2Contact
{
public:
	Ldif2Contact() {}
	bool operator()(Contact &rec)
	{
		return rec.ReadLdif(cin);
	}
};

template <class Record>
struct Store
{
	std::vector<Record> records;
	mutable typename std::vector<Record>::const_iterator rec_it;
	int count;

	Store(std::istream &is)
		: count(0)
	{
		Record rec;
		while( is ) {
			if( rec.ReadLdif(is) ) {
				count++;
				records.push_back(rec);
			}
		}

		rec_it = records.begin();
	}
	~Store()
	{
		cout << "Store counted " << dec << count << " records." << endl;
	}

	// retrieval operator
	bool operator()(Record &rec, unsigned int databaseId) const
	{
		if( rec_it == records.end() )
			return false;
		rec = *rec_it;
		rec_it++;
		return true;
	}

	void Dump(std::ostream &os) const
	{
		typename std::vector<Record>::const_iterator b = records.begin();
		for( ; b != records.end(); ++b ) {
			os << *b << endl;
		}
	}
};

template <class Record>
std::ostream& operator<< (std::ostream &os, const Store<Record> &store)
{
	store.Dump(os);
	return os;
}

int main(int argc, char *argv[])
{
	cout.sync_with_stdio(true);	// leave this on, since libusb uses
					// stdio for debug messages

	try {

		uint32_t pin = 0;
		bool	data_dump = false,
			do_upload = false;

		// process command line options
		for(;;) {
			int cmd = getopt(argc, argv, "hp:uv");
			if( cmd == -1 )
				break;

			switch( cmd )
			{
			case 'p':	// Blackberry PIN
				pin = strtoul(optarg, NULL, 16);
				break;

			case 'u':	// do upload
				do_upload = true;
				break;

			case 'v':	// data dump on
				data_dump = true;
				break;

			case 'h':	// help
			default:
				Usage();
				return 0;
			}
		}

		// Read all contacts from stdin
		Store<Contact> contactStore(cin);
		if( !do_upload) {
			// only dump to stdout
			cout << contactStore << endl;
			return 0;
		}

		// Initialize the barry library.  Must be called before
		// anything else.
		Barry::Init(data_dump);

		// Probe the USB bus for Blackberry devices
		// If user has specified a PIN, search for it
		Barry::Probe probe;
		int activeDevice = probe.FindActive(pin);
		if( activeDevice == -1 ) {
			cerr << "Device not found, or not specified" << endl;
			return 1;
		}

		// Create our controller object
		Barry::Controller con(probe.Get(activeDevice));

		// Create our builder object
		RecordBuilder<Contact, Store<Contact> > build(contactStore);

		// make sure we're in desktop mode
		con.OpenMode(Controller::Desktop);

		// upload all records to device
		con.SaveDatabaseByType<Barry::Contact>(contactStore);

	}
	catch( Barry::BError &se ) {
		std::cerr << "BError caught: " << se.what() << endl;
	}
	catch( Usb::UsbError &ue) {
		std::cerr << "UsbError caught: " << ue.what() << endl;
	}
	catch( std::runtime_error &re ) {
		std::cerr << "std::runtime_error caught: " << re.what() << endl;
		return 1;
	}
	catch( std::exception &e ) {
		std::cerr << "std::exception caught: " << e.what() << endl;
		return 1;
	}

	return 0;
}
