
#line 1 "include/jsmincpp/deserialize/ParseBool.rlh"
#ifndef INCLUDE_DESERIALIZE_PARSEBOOL_H_
#define INCLUDE_DESERIALIZE_PARSEBOOL_H_

#include <cstdint>

namespace jsmincpp {

namespace deserialize {

template < typename S >
bool ParseBool( bool &data, S &p ) {

  
#line 14 "include/jsmincpp/deserialize/ParseBool.rlh"
  
#line 19 "include/jsmincpp/deserialize/ParseBool.h"
static const int BoolParser_start = 1;
static const int BoolParser_first_final = 11;
static const int BoolParser_error = 0;

static const int BoolParser_en_value = 1;


#line 15 "include/jsmincpp/deserialize/ParseBool.rlh"

  int cs;
  S pe = p.End( );
  S eof = p.End( );

  
#line 34 "include/jsmincpp/deserialize/ParseBool.h"
	{
	cs = BoolParser_start;
	}

#line 21 "include/jsmincpp/deserialize/ParseBool.rlh"
  
#line 29 "include/jsmincpp/deserialize/ParseBool.rlh"


  
#line 45 "include/jsmincpp/deserialize/ParseBool.h"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 102: goto st2;
		case 116: goto st7;
	}
	goto st0;
tr7:
#line 24 "include/jsmincpp/deserialize/ParseBool.rlh"
	{ return false; }
	goto st0;
#line 61 "include/jsmincpp/deserialize/ParseBool.h"
st0:
cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 97 )
		goto st3;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 108 )
		goto st4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 115 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 101 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	switch( (*p) ) {
		case 44: goto tr8;
		case 93: goto tr8;
		case 125: goto tr8;
	}
	goto tr7;
tr8:
#line 26 "include/jsmincpp/deserialize/ParseBool.rlh"
	{ data = false; }
#line 23 "include/jsmincpp/deserialize/ParseBool.rlh"
	{ return true; }
	goto st11;
tr12:
#line 25 "include/jsmincpp/deserialize/ParseBool.rlh"
	{ data = true; }
#line 23 "include/jsmincpp/deserialize/ParseBool.rlh"
	{ return true; }
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 119 "include/jsmincpp/deserialize/ParseBool.h"
	goto tr7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 114 )
		goto st8;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 117 )
		goto st9;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 101 )
		goto st10;
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	switch( (*p) ) {
		case 44: goto tr12;
		case 93: goto tr12;
		case 125: goto tr12;
	}
	goto tr7;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 6: 
	case 10: 
#line 24 "include/jsmincpp/deserialize/ParseBool.rlh"
	{ return false; }
	break;
#line 173 "include/jsmincpp/deserialize/ParseBool.h"
	}
	}

	_out: {}
	}

#line 32 "include/jsmincpp/deserialize/ParseBool.rlh"

  return false;
}

}          // namespace deserialize

}          // namespace jsmincpp

#endif          // INCLUDE_DESERIALIZE_PARSEBOOL_H_
