check_PROGRAMS = test_jsmincpp

AM_CPPFLAGS = -I$(top_srcdir)/include -O3 -std=c++11
AM_LDFLAGS = -O3 
LIBS += -lstdc++ -lm -lgmock -lgtest -lgtest_main -lpthread  

TESTS = $(check_PROGRAMS)

test_jsmincpp_SOURCES = \
	MockSerializeHandler.h \
	SymbolStream.h \
	test_GetNameHash.cpp \
	test_JSONParser.cpp \
	test_JSONSerialiser.cpp \
	test_ParseBool.cpp \
	test_ParseFloat.cpp \
	test_ParseInteger.cpp \
	test_SaticString.cpp \
	test_SkipEndJSONString.cpp \
	test_STLContainersDeserialise.cpp \
	test_STLContainersSerialise.cpp
