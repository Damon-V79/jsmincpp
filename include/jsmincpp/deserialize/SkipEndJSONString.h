
#line 1 "include/jsmincpp/deserialize/SkipEndJSONString.rlh"
#ifndef INCLUDE_DESERIALIZE_SKIPENDJSONSTRING_H_
#define INCLUDE_DESERIALIZE_SKIPENDJSONSTRING_H_

#include <cstdint>

namespace jsmincpp {

namespace deserialize {

template < typename S >
bool SkipEndJSONString( S &p ) {

  
#line 14 "include/jsmincpp/deserialize/SkipEndJSONString.rlh"
  
#line 19 "include/jsmincpp/deserialize/SkipEndJSONString.h"
static const int Skip_end_JSON_string_start = 1;
static const int Skip_end_JSON_string_first_final = 2;
static const int Skip_end_JSON_string_error = 0;

static const int Skip_end_JSON_string_en_main = 1;


#line 15 "include/jsmincpp/deserialize/SkipEndJSONString.rlh"

  int cs;
  S pe = p.End( );
  S eof = p.End( );
  
  
#line 34 "include/jsmincpp/deserialize/SkipEndJSONString.h"
	{
	cs = Skip_end_JSON_string_start;
	}

#line 21 "include/jsmincpp/deserialize/SkipEndJSONString.rlh"
  
#line 27 "include/jsmincpp/deserialize/SkipEndJSONString.rlh"


  
#line 45 "include/jsmincpp/deserialize/SkipEndJSONString.h"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	switch( (*p) ) {
		case 123: goto tr1;
		case 125: goto tr2;
	}
	goto st1;
tr1:
#line 23 "include/jsmincpp/deserialize/SkipEndJSONString.rlh"
	{ ++p; SkipEndJSONString( p ); }
	goto st2;
tr2:
#line 24 "include/jsmincpp/deserialize/SkipEndJSONString.rlh"
	{ ++p; return false; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 72 "include/jsmincpp/deserialize/SkipEndJSONString.h"
	goto st0;
st0:
cs = 0;
	goto _out;
	}
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 30 "include/jsmincpp/deserialize/SkipEndJSONString.rlh"

  return false;
}

}          // namespace deserialize

}          // namespace jsmincpp

#endif          // INCLUDE_DESERIALIZE_SKIPENDJSONSTRING_H_
