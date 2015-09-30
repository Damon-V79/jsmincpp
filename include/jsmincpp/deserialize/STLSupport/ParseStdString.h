
#line 1 "include/jsmincpp/deserialize/STLSupport/ParseStdString.rlh"
#ifndef INCLUDE_DESERIALIZE_STLSUPPORT_PARSESTDSTRING_H_
#define INCLUDE_DESERIALIZE_STLSUPPORT_PARSESTDSTRING_H_

#include <cstdint>

namespace jsmincpp {

namespace deserialize {

template < typename T, typename S >
bool ParseStdString( T &data, S &p ) {

  
#line 14 "include/jsmincpp/deserialize/STLSupport/ParseStdString.rlh"
  
#line 19 "include/jsmincpp/deserialize/STLSupport/ParseStdString.h"
static const int StdStringParser_start = 1;
static const int StdStringParser_first_final = 3;
static const int StdStringParser_error = 0;

static const int StdStringParser_en_main = 1;


#line 15 "include/jsmincpp/deserialize/STLSupport/ParseStdString.rlh"

  int cs;
  S pe = p.End( );
  S eof = p.End( );

  
#line 34 "include/jsmincpp/deserialize/STLSupport/ParseStdString.h"
	{
	cs = StdStringParser_start;
	}

#line 21 "include/jsmincpp/deserialize/STLSupport/ParseStdString.rlh"
  
#line 28 "include/jsmincpp/deserialize/STLSupport/ParseStdString.rlh"


  
#line 45 "include/jsmincpp/deserialize/STLSupport/ParseStdString.h"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	if ( (*p) == 34 )
		goto st2;
	goto tr0;
tr0:
#line 24 "include/jsmincpp/deserialize/STLSupport/ParseStdString.rlh"
	{ return false; }
	goto st0;
#line 59 "include/jsmincpp/deserialize/STLSupport/ParseStdString.h"
st0:
cs = 0;
	goto _out;
tr2:
#line 23 "include/jsmincpp/deserialize/STLSupport/ParseStdString.rlh"
	{ data += *p; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 71 "include/jsmincpp/deserialize/STLSupport/ParseStdString.h"
	if ( (*p) == 34 )
		goto tr3;
	goto tr2;
tr3:
#line 25 "include/jsmincpp/deserialize/STLSupport/ParseStdString.rlh"
	{ ++p; return true; }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 83 "include/jsmincpp/deserialize/STLSupport/ParseStdString.h"
	goto tr0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 1: 
	case 2: 
#line 24 "include/jsmincpp/deserialize/STLSupport/ParseStdString.rlh"
	{ return false; }
	break;
#line 98 "include/jsmincpp/deserialize/STLSupport/ParseStdString.h"
	}
	}

	_out: {}
	}

#line 31 "include/jsmincpp/deserialize/STLSupport/ParseStdString.rlh"

  return false;
}

}          // namespace deserialize

}          // namespace jsmincpp

#endif /* INCLUDE_DESERIALIZE_STLSUPPORT_PARSESTDSTRING_H_ */
