///
/// \file	cod.h
///		COD file API
///

/*
    Copyright (C) 2009-2010, Net Direct Inc. (http://www.netdirect.ca/)

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

#ifndef __BARRY_COD_H__
#define __BARRY_COD_H__

#include "dll.h"
#include "data.h"
#include <sys/types.h>
#include <stdint.h>
#include <iostream>
#include <sstream>

namespace Barry {


//
// SeekNextCod
//
/// Seeks the input stream to the next packed sibling .cod file and returns
/// the packed .cod file size.  When all siblings have been read, zero is
/// returned.
///
/// When input stream does not contain the signature for a packed .cod file,
/// it's assumed the entire stream is the .cod file.
///
/// \param input stream to read from
///
/// \return size of next packed .cod file, or 0 finished reading .cod files
///
size_t SeekNextCod(std::istream &input);


///
/// The CodFileBuilder class is used to assemble multiple .cod files into
/// a single packed .cod file using the pkzip file format.
///
class BXEXPORT CodFileBuilder
{
	std::string m_module_name;

	size_t m_module_count;
	unsigned int m_current_module;

	std::ostringstream m_directory;

public:
	CodFileBuilder(const std::string &module_name, size_t module_count = 1);

	~CodFileBuilder();

	///
	/// Writes packed .cod file header to the output stream, and appends
	/// an entry to the central directory.  If the module count used to
	/// create CodFileBuilder is equal to one, the call is ignored.
	///
	/// Note: it is the caller's responsibility to write the actual
	/// COD file data after calling this function.
	///
	/// \param output stream to write to
	///
	/// \param buffer buffered .cod file data, input to CRC-32 function
	///
	/// \param module_size total size of .cod file data
	///
	void WriteNextHeader(std::ostream &output, const uint8_t* buffer,
			uint32_t module_size);

	///
	/// Write the central directory and central directory ending indicator
	/// to the output stream.
	///
	/// \param output stream to write to
	///
	void WriteFooter(std::ostream &output);
};

}

#endif

