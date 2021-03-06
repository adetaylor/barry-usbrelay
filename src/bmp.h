///
/// \file	bmp.h
///		BMP conversion routines
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

#ifndef __BARRY_BMP_H__
#define __BARRY_BMP_H__

#include "dll.h"
#include "data.h"
#include "m_javaloader.h"

namespace Barry {

BXEXPORT size_t GetTotalBitmapSize(const JLScreenInfo &info);
BXEXPORT void ScreenshotToBitmap(const JLScreenInfo &info,
	const Data &screenshot, Data &bitmap);

}

#endif

