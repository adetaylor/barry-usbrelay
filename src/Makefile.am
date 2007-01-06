
# The following version numbers are:  current:revision:age
#
# See also: http://sources.redhat.com/autobook/autobook/autobook_91.html
#
# Current - number of the current interface of the library
# Revision - implementation number of most recent interface
# Age - number of previous additional interfaces supported by this library
#
# Libtool uses the following calculation for Linux:
#
#    major = current - age
#    suffix = major.age.revision
#
# Therefore a libtool version of 1.4.0 will translate to a filename of:
#    libbarry.so.1.0.4
#
# Other operating systems just use current.revision, most of the time,
# and age is only used to subtract from current.
#
# Therefore, if you are careful never to increment the major version
# unless there is an incompatible break, you can get away with a
# two digit version number, and leave age as 0, always.
#
# Only ever increment the first 2 numbers in this version:
LIB_BARRY_VERSION = 0:5:0

# Disable the default -I. -I$(srcdir) -I$(topdir), etc, as our includes
# are proper anyway. :-)
DEFAULT_INCLUDES =
#INCLUDES = @PACKAGE_CXXFLAGS@ -I@LIBUSB_INC_PATH@
INCLUDES = -I@LIBUSB_INC_PATH@
AM_CXXFLAGS = -ansi -Wall -fno-strict-aliasing -g
include_barrydir = ${includedir}/barry

##
## Boost library usage - required for serialization support, but optional
##
#BOOSTFLAG = -D__BARRY_BOOST_MODE__ -I../../../../boost/rootdir/include/boost-1_33_1
#LDBOOST = ../../../../boost/rootdir/lib/libboost_serialization-gcc-mt-1_33_1.a
##BOOSTFLAG =
##LDBOOST =

# Heavy duty C++ warnings
#WARNFLAGS = -ansi -pedantic -Wall -W -Wold-style-cast -Wfloat-equal -Wwrite-strings -Wno-long-long
#WARNFLAGS = -ansi -pedantic -Wall -W -Weffc++ -Woverloaded-virtual -Wold-style-cast -Wfloat-equal -Wwrite-strings -Wno-long-long -Werror

#LDFLAGS = ../../external/rootdir/libusb/lib/libusb.a $(LDBOOST) -lpthread $(LDDEBUG)

lib_LTLIBRARIES = libbarry.la

include_barry_HEADERS = barry.h \
	builder.h \
	common.h \
	controller.h \
	controllertmpl.h \
	data.h \
	error.h \
	parser.h \
	probe.h \
	protocol.h \
	record.h \
	socket.h \
	usbwrap.h \
	time.h \
	s11n-boost.h


libbarry_la_SOURCES = time.cc \
	base64.cc base64.h \
	parser.cc \
	data.cc \
	usbwrap.cc \
	probe.cc \
	common.cc \
	error.cc \
	socket.cc \
	protocol.cc \
	record.cc \
	packet.cc packet.h \
	controller.cc \
	protostructs.h \
	debug.h \
	endian.h
libbarry_la_LIBADD = @LIBUSB_LIB_PATH@/libusb.la
libbarry_la_LDFLAGS = -version-info ${LIB_BARRY_VERSION}

##if DO_TEST
##	bin_PROGRAMS += test-base64 test-data test-time
##
##	test_base64_SOURCES = base64.h base64.cc
##	test_data_SOURCES = data.h data.cc
##	test_time_SOURCES = time.h time.cc
##endif
