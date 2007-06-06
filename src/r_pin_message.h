///
/// \file	r_pin_message.h
///		Blackberry database record parser class for pin message records.
///

/*
    Copyright (C) 2005-2007, Net Direct Inc. (http://www.netdirect.ca/)
    Copyright (C) 2007, Brian Edginton (edge@edginton.net)

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

#ifndef __BARRY_RECORD_PIN_MESSAGE_H__
#define __BARRY_RECORD_PIN_MESSAGE_H__

#include "record.h"
#include <iosfwd>
#include <string>
#include <vector>
#include <map>
#include <stdint.h>

namespace Barry {

//
// NOTE:  All classes here must be container-safe!  Perhaps add sorting
//        operators in the future.
//

/// \addtogroup RecordParserClasses
/// @{

class PINMessage
{
public:

	Address From;
	Address To;
	Address Cc;
	Address Bcc;
	std::string Subject;
	std::string Body;
	uint32_t MessageRecordId;
	std::vector<UnknownField> Unknowns;

public:
	const unsigned char* ParseField(const unsigned char *begin,
		const unsigned char *end);

public:
	PINMessage();
	~PINMessage();

	// Parser / Builder API (see parser.h / builder.h)
	uint8_t GetRecType() const;
	uint32_t GetUniqueId() const;	// empty API, not required by protocol
	void SetIds(uint8_t Type, uint32_t Id);	// empty API, not required by protocol
	void ParseHeader(const Data &data, size_t &offset);
	void ParseFields(const Data &data, size_t &offset);
	void BuildHeader(Data &data, size_t &offset) const;
	void BuildFields(Data &data, size_t &offset) const;

	void Clear();

	void Dump(std::ostream &os) const;

	// sorting
	bool operator<(const PINMessage &other) const { return Subject < other.Subject; }

	// database name
	static const char * GetDBName() { return "PIN Messages"; }
	static uint8_t GetDefaultRecType() { return 0; }
};

inline std::ostream& operator<<(std::ostream &os, const PINMessage &msg) {
	msg.Dump(os);
	return os;
}

std::ostream& operator<<(std::ostream &os, const Address &msga);


/// @}

} // namespace Barry

#endif // __BARRY_RECORD_PIN_MESSAGE_H__


