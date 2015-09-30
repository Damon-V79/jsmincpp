
#line 1 "include/jsmincpp/deserialize/ParseStaticString.rlh"
#ifndef INCLUDE_DESERIALIZE_PARSESTATICSTRING_H_
#define INCLUDE_DESERIALIZE_PARSESTATICSTRING_H_

#include <cstdint>

namespace jsmincpp {

namespace deserialize {

template < typename T, typename S >
bool ParseStaticString( T &data, S &p ) {

  
#line 14 "include/jsmincpp/deserialize/ParseStaticString.rlh"
  
#line 19 "include/jsmincpp/deserialize/ParseStaticString.h"
static const int StaticStringParser_start = 1;
static const int StaticStringParser_first_final = 3;
static const int StaticStringParser_error = 0;

static const int StaticStringParser_en_main = 1;


#line 15 "include/jsmincpp/deserialize/ParseStaticString.rlh"

  int cs;
  S pe = p.End( );
  S eof = p.End( );

  
#line 34 "include/jsmincpp/deserialize/ParseStaticString.h"
	{
	cs = StaticStringParser_start;
	}

#line 21 "include/jsmincpp/deserialize/ParseStaticString.rlh"
  
#line 28 "include/jsmincpp/deserialize/ParseStaticString.rlh"


  
#line 45 "include/jsmincpp/deserialize/ParseStaticString.h"
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
#line 24 "include/jsmincpp/deserialize/ParseStaticString.rlh"
	{ return false; }
	goto st0;
#line 59 "include/jsmincpp/deserialize/ParseStaticString.h"
st0:
cs = 0;
	goto _out;
tr2:
#line 23 "include/jsmincpp/deserialize/ParseStaticString.rlh"
	{ if( !data.Add( *p ) ) return false; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 71 "include/jsmincpp/deserialize/ParseStaticString.h"
	if ( (*p) == 34 )
		goto tr3;
	goto tr2;
tr3:
#line 25 "include/jsmincpp/deserialize/ParseStaticString.rlh"
	{ ++p; return true; }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 83 "include/jsmincpp/deserialize/ParseStaticString.h"
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
#line 24 "include/jsmincpp/deserialize/ParseStaticString.rlh"
	{ return false; }
	break;
#line 98 "include/jsmincpp/deserialize/ParseStaticString.h"
	}
	}

	_out: {}
	}

#line 31 "include/jsmincpp/deserialize/ParseStaticString.rlh"

  return false;
}

}          // namespace deserialize

}          // namespace jsmincpp

#endif         // INCLUDE_DESERIALIZE_PARSESTATICSTRING_H_
