
#line 1 "include/jsmincpp/deserialize/ParseFloat.rlh"
#ifndef INCLUDE_DESERIALIZE_PARSEFLOAT_H_
#define INCLUDE_DESERIALIZE_PARSEFLOAT_H_

#include <cstdint>
#include <cmath>

namespace jsmincpp {

namespace deserialize {

template < typename T,typename S >
bool ParseFloat( T &data, S &p ) {

  
#line 15 "include/jsmincpp/deserialize/ParseFloat.rlh"
  
#line 20 "include/jsmincpp/deserialize/ParseFloat.h"
static const int FloatParser_start = 1;
static const int FloatParser_first_final = 9;
static const int FloatParser_error = 0;

static const int FloatParser_en_value = 1;


#line 16 "include/jsmincpp/deserialize/ParseFloat.rlh"

  int cs;
  T count = 1.0f;
  uint32_t exp = 0;
  T negNumber = 1;
  T negExp = 1;

  data = 0.0;
  S pe = p.End( );
  S eof = p.End( );

  
#line 41 "include/jsmincpp/deserialize/ParseFloat.h"
	{
	cs = FloatParser_start;
	}

#line 28 "include/jsmincpp/deserialize/ParseFloat.rlh"
  
#line 49 "include/jsmincpp/deserialize/ParseFloat.rlh"


  
#line 52 "include/jsmincpp/deserialize/ParseFloat.h"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	if ( (*p) == 45 )
		goto tr0;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr2;
	goto st0;
tr3:
#line 46 "include/jsmincpp/deserialize/ParseFloat.rlh"
	{ return false; }
	goto st0;
#line 68 "include/jsmincpp/deserialize/ParseFloat.h"
st0:
cs = 0;
	goto _out;
tr0:
#line 44 "include/jsmincpp/deserialize/ParseFloat.rlh"
	{ negNumber = -1; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 80 "include/jsmincpp/deserialize/ParseFloat.h"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr2;
	goto st0;
tr2:
#line 41 "include/jsmincpp/deserialize/ParseFloat.rlh"
	{ data = data * 10 + ( *p - '0' ); }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 92 "include/jsmincpp/deserialize/ParseFloat.h"
	switch( (*p) ) {
		case 44: goto tr4;
		case 46: goto st4;
		case 69: goto st6;
		case 93: goto tr4;
		case 101: goto st6;
		case 125: goto tr4;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr2;
	goto tr3;
tr4:
#line 45 "include/jsmincpp/deserialize/ParseFloat.rlh"
	{ data = data * ::pow( 10, exp * negExp ) * negNumber; return true; }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 112 "include/jsmincpp/deserialize/ParseFloat.h"
	goto tr3;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr7;
	goto st0;
tr7:
#line 38 "include/jsmincpp/deserialize/ParseFloat.rlh"
	{ count /= 10; data += ( ( *p - '0' ) * count ); }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 129 "include/jsmincpp/deserialize/ParseFloat.h"
	switch( (*p) ) {
		case 44: goto tr4;
		case 69: goto st6;
		case 93: goto tr4;
		case 101: goto st6;
		case 125: goto tr4;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr7;
	goto tr3;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	switch( (*p) ) {
		case 43: goto tr8;
		case 45: goto tr8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr9;
	goto st0;
tr8:
#line 32 "include/jsmincpp/deserialize/ParseFloat.rlh"
	{ if( *p == '-' ) negExp = -1; }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 159 "include/jsmincpp/deserialize/ParseFloat.h"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr9;
	goto st0;
tr9:
#line 35 "include/jsmincpp/deserialize/ParseFloat.rlh"
	{ exp = exp * 10 + ( *p - '0' ); }
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 171 "include/jsmincpp/deserialize/ParseFloat.h"
	switch( (*p) ) {
		case 44: goto tr4;
		case 93: goto tr4;
		case 125: goto tr4;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr9;
	goto tr3;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 3: 
	case 5: 
	case 8: 
#line 46 "include/jsmincpp/deserialize/ParseFloat.rlh"
	{ return false; }
	break;
#line 200 "include/jsmincpp/deserialize/ParseFloat.h"
	}
	}

	_out: {}
	}

#line 52 "include/jsmincpp/deserialize/ParseFloat.rlh"

  return false;
}

}          // namespace deserialize

}          // namespace jsmincpp

#endif          // INCLUDE_DESERIALIZE_PARSEFLOAT_H_
