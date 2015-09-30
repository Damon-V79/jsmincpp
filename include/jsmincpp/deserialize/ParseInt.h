
#line 1 "include/jsmincpp/deserialize/ParseInt.rlh"
#ifndef INCLUDE_DESERIALIZE_PARSEINT_H_
#define INCLUDE_DESERIALIZE_PARSEINT_H_

#include <jsmincpp/IntegerOverflowControl.h>

namespace jsmincpp {

namespace deserialize {

template < typename T, typename S >
bool ParseInt( T &data, S &p ) {

  
#line 14 "include/jsmincpp/deserialize/ParseInt.rlh"
  
#line 19 "include/jsmincpp/deserialize/ParseInt.h"
static const int IntegerParser_start = 1;
static const int IntegerParser_first_final = 4;
static const int IntegerParser_error = 0;

static const int IntegerParser_en_value = 1;


#line 15 "include/jsmincpp/deserialize/ParseInt.rlh"

  int cs;
  S pe = p.End( );
  S eof = p.End( );
  int8_t negNumber = 1;

  
#line 35 "include/jsmincpp/deserialize/ParseInt.h"
	{
	cs = IntegerParser_start;
	}

#line 22 "include/jsmincpp/deserialize/ParseInt.rlh"
  
#line 41 "include/jsmincpp/deserialize/ParseInt.rlh"


  
#line 46 "include/jsmincpp/deserialize/ParseInt.h"
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
#line 38 "include/jsmincpp/deserialize/ParseInt.rlh"
	{ return false; }
	goto st0;
#line 62 "include/jsmincpp/deserialize/ParseInt.h"
st0:
cs = 0;
	goto _out;
tr0:
#line 36 "include/jsmincpp/deserialize/ParseInt.rlh"
	{ negNumber = -1; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 74 "include/jsmincpp/deserialize/ParseInt.h"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr2;
	goto st0;
tr2:
#line 26 "include/jsmincpp/deserialize/ParseInt.rlh"
	{
                     if( !jsmincpp::IntegerOverflowControl< T >::Mult( data, 10 ) )
                       return false;
                     if( negNumber == -1 ) --data;
                     if( !jsmincpp::IntegerOverflowControl< T >::Summ( data, ( *p - '0' ) ) )
                       return false;
                     if( negNumber == -1 ) ++data;
                    }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 93 "include/jsmincpp/deserialize/ParseInt.h"
	switch( (*p) ) {
		case 44: goto tr4;
		case 93: goto tr4;
		case 125: goto tr4;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr2;
	goto tr3;
tr4:
#line 37 "include/jsmincpp/deserialize/ParseInt.rlh"
	{ data = data * negNumber; return true; }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 110 "include/jsmincpp/deserialize/ParseInt.h"
	goto tr3;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 3: 
#line 38 "include/jsmincpp/deserialize/ParseInt.rlh"
	{ return false; }
	break;
#line 125 "include/jsmincpp/deserialize/ParseInt.h"
	}
	}

	_out: {}
	}

#line 44 "include/jsmincpp/deserialize/ParseInt.rlh"

  return false;
}

}          // namespace deserialize

}          // namespace jsmincpp

#endif          // INCLUDE_DESERIALIZE_PARSEINT_H_
