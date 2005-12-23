///
/// \file	btool.cc
///		Barry library tester
///

/*
    Copyright (C) 2005, Net Direct Inc. (http://www.netdirect.ca/)

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
   << "btool - Command line USB Blackberry Test Tool\n"
   << "        Copyright 2005, Net Direct Inc. (http://www.netdirect.ca/)\n\n"
   << "   -c dn     Convert address book database to LDIF format, using the\n"
   << "             specified baseDN\n"
   << "   -d db     Load database 'db' and dump to screen\n"
   << "             Can be used multiple times to fetch more than one DB\n"
   << "   -f file   Filename to save or load handheld data to/from\n"
   << "   -h        This help\n"
   << "   -l        List devices\n"
   << "   -p pin    PIN of device to talk with\n"
   << "             If only one device plugged in, this flag is optional\n"
   << "   -s db     Save database 'db' from data loaded from -f file\n"
   << "   -t        Show database database table\n"
   << "   -v        Dump protocol data during operation\n"
   << endl;
}

class Contact2Ldif
{
	std::string m_baseDN;
public:
	Contact2Ldif(const std::string &baseDN) : m_baseDN(baseDN) {}
	void operator()(const Contact &rec)
	{
		rec.DumpLdif(cout, m_baseDN);
	}
};

template <class Record>
struct Store
{
	std::vector<Record> records;
	mutable typename std::vector<Record>::const_iterator rec_it;
	std::string filename;
	bool load;
	int count;

	Store(const string &filename, bool load)
		: rec_it(records.end()),
		filename(filename),
		load(load),
		count(0)
	{
#ifdef __BOOST_MODE__
		try {

			if( load && filename.size() ) {
				// filename is available, attempt to save
				cout << "Loading: " << filename << endl;
				ifstream ifs(filename.c_str());
				boost::archive::text_iarchive ia(ifs);
				ia >> records;
				cout << records.size()
				     << " records loaded from '"
				     << filename << "'" << endl;
				sort(records.begin(), records.end());
				rec_it = records.begin();

				// debugging aid
				typename std::vector<Record>::const_iterator beg = records.begin(), end = records.end();
				for( ; beg != end; beg++ ) {
					dout(*beg);
				}
			}

		} catch( boost::archive::archive_exception &ae ) {
			cerr << "Archive exception in ~Store(): "
			     << ae.what() << endl;
		}
#endif
	}
	~Store()
	{
		cout << "Store counted " << count << " records." << endl;
#ifdef __BOOST_MODE__
		try {

			if( !load && filename.size() ) {
				// filename is available, attempt to save
				cout << "Saving: " << filename << endl;
				const std::vector<Record> &r = records;
				ofstream ofs(filename.c_str());
				boost::archive::text_oarchive oa(ofs);
				oa << r;
				cout << r.size() << " records saved to '"
					<< filename << "'" << endl;
			}

		} catch( boost::archive::archive_exception &ae ) {
			cerr << "Archive exception in ~Store(): "
			     << ae.what() << endl;
		}
#endif
	}

	// storage operator
	void operator()(const Record &rec)
	{
		count++;
		std::cout << rec << std::endl;
		records.push_back(rec);
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
};

auto_ptr<Parser> GetParser(const string &name, const string &filename)
{
	// check for recognized database names
	if( name == "Address Book" ) {
		return auto_ptr<Parser>(
			new RecordParser<Contact, Store<Contact> > (
				new Store<Contact>(filename, false)));
	}
	else if( name == "Messages" ) {
		return auto_ptr<Parser>(
			new RecordParser<Message, Store<Message> > (
				new Store<Message>(filename, false)));
	}
	else if( name == "Calendar" ) {
		return auto_ptr<Parser>(
			new RecordParser<Calendar, Store<Calendar> > (
				new Store<Calendar>(filename, false)));
	}
	else {
		// unknown database, use null parser
		return auto_ptr<Parser>( new Parser );
	}
}

auto_ptr<Builder> GetBuilder(const string &name, const string &filename)
{
	// check for recognized database names
	if( name == "Address Book" ) {
		return auto_ptr<Builder>(
			new RecordBuilder<Contact, Store<Contact> > (
				new Store<Contact>(filename, true)));
	}
/*
	else if( name == "Messages" ) {
		return auto_ptr<Parser>(
			new RecordParser<Message, Store<Message> > (
				new Store<Message>(filename, true)));
	}
	else if( name == "Calendar" ) {
		return auto_ptr<Parser>(
			new RecordParser<Calendar, Store<Calendar> > (
				new Store<Calendar>(filename, true)));
	}
*/
	else {
		throw std::runtime_error("No Builder available for database");
	}
}

int main(int argc, char *argv[])
{
	cout.sync_with_stdio(true);	// leave this on, since libusb uses
					// stdio for debug messages

	try {

		uint32_t pin = 0;
		bool	list_only = false,
			show_dbdb = false,
			ldif_contacts = false,
			data_dump = false;
		string ldifBaseDN;
		string filename;
		vector<string> dbNames, saveDbNames;

		// process command line options
		for(;;) {
			int cmd = getopt(argc, argv, "c:d:f:hlp:s:tv");
			if( cmd == -1 )
				break;

			switch( cmd )
			{
			case 'c':	// contacts to ldap ldif
				ldif_contacts = true;
				ldifBaseDN = optarg;
				break;

			case 'd':	// show dbname
				dbNames.push_back(string(optarg));
				break;

			case 'f':	// filename
#ifdef __BOOST_MODE__
				filename = optarg;
#else
				cerr << "-f option not supported - no Boost "
					"serialization support available";
#endif
				break;
			case 'l':	// list only
				list_only = true;
				break;

			case 'p':	// Blackberry PIN
				pin = strtoul(optarg, NULL, 16);
				break;

			case 's':	// save dbname
				saveDbNames.push_back(string(optarg));
				break;

			case 't':	// display database database
				show_dbdb = true;
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

		Init(data_dump);

		Probe probe;
		int activeDevice = -1;
		cout << "Blackberry devices found:" << endl;
		for( int i = 0; i < probe.GetCount(); i++ ) {
			cout << probe.Get(i) << endl;
			if( probe.Get(i).m_pin == pin )
				activeDevice = i;
		}

		if( list_only )
			return 0;	// done

		if( activeDevice == -1 ) {
			if( pin == 0 ) {
				// can we default to single device?
				if( probe.GetCount() == 1 )
					activeDevice = 0;
				else {
					cerr << "No device selected" << endl;
					return 1;
				}
			}
			else {
				cerr << "PIN " << setbase(16) << pin
					<< " not found" << endl;
				return 1;
			}
		}

		// create our controller object
		Controller con(probe.Get(activeDevice));

		// execute each mode that was turned on

		if( show_dbdb ) {
			// open desktop mode socket
			con.OpenMode(Controller::Desktop);
			cout << con.GetDBDB() << endl;
		}

		if( ldif_contacts ) {
			con.OpenMode(Controller::Desktop);
			Contact2Ldif storage(ldifBaseDN);
			RecordParser<Contact, Contact2Ldif> parser(storage);
			con.LoadDatabase(con.GetDBID("Address Book"), parser);
		}

		if( dbNames.size() ) {
			vector<string>::iterator b = dbNames.begin();

			for( ; b != dbNames.end(); b++ ) {
				con.OpenMode(Controller::Desktop);
				auto_ptr<Parser> parse = GetParser(*b,filename);
				unsigned int id = con.GetDBID(*b);
				con.LoadDatabase(id, *parse.get());
			}
		}

		if( saveDbNames.size() ) {
			vector<string>::iterator b = saveDbNames.begin();

			for( ; b != saveDbNames.end(); b++ ) {
				con.OpenMode(Controller::Desktop);
				auto_ptr<Builder> build =
					GetBuilder(*b, filename);
				unsigned int id = con.GetDBID(*b);
				con.SaveDatabase(id, *build);
			}
		}

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

