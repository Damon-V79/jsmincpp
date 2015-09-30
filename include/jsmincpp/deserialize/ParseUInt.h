
#line 1 "include/jsmincpp/deserialize/ParseUInt.rlh"
#ifndef INCLUDE_DESERIALIZE_PARSEUINT_H_
#define INCLUDE_DESERIALIZE_PARSEUINT_H_

#include <jsmincpp/IntegerOverflowControl.h>

namespace jsmincpp {

namespace deserialize {

template < typename T, typename S >
bool ParseUInt( T &data, S &p ) {
  
  
#line 14 "include/jsmincpp/deserialize/ParseUInt.rlh"
  
#line 19 "include/jsmincpp/deserialize/ParseUInt.h"
static const int UnsignedIntegerParser_start = 1;
static const int UnsignedIntegerParser_first_final = 3;
static const int UnsignedIntegerParser_error = 0;

static const int UnsignedIntegerParser_en_value = 1;


#line 15 "include/jsmincpp/deserialize/ParseUInt.rlh"

  int cs;
  S pe = p.End( );
  S eof = p.End( );

  
#line 34 "include/jsmincpp/deserialize/ParseUInt.h"
	{
	cs = UnsignedIntegerParser_start;
	}

#line 21 "include/jsmincpp/deserialize/ParseUInt.rlh"
  
#line 37 "include/jsmincpp/deserialize/ParseUInt.rlh"


  
#line 45 "include/jsmincpp/deserialize/ParseUInt.h"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr0;
	goto st0;
tr2:
#line 34 "include/jsmincpp/deserialize/ParseUInt.rlh"
	{ return false; }
	goto st0;
#line 59 "include/jsmincpp/deserialize/ParseUInt.h"
st0:
cs = 0;
	goto _out;
tr0:
#line 25 "include/jsmincpp/deserialize/ParseUInt.rlh"
	{
                     if( !jsmincpp::IntegerOverflowControl< T >::Mult( data, 10 ) )
                       return false;
                     if( !jsmincpp::IntegerOverflowControl< T >::Summ( data, ( *p - '0' ) ) )
                       return false;
                    }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 76 "include/jsmincpp/deserialize/ParseUInt.h"
	switch( (*p) ) {
		case 44: goto tr3;
		case 93: goto tr3;
		case 125: goto tr3;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr0;
	goto tr2;
tr3:
#line 33 "include/jsmincpp/deserialize/ParseUInt.rlh"
	{ return true; }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 93 "include/jsmincpp/deserialize/ParseUInt.h"
	goto tr2;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 2: 
#line 34 "include/jsmincpp/deserialize/ParseUInt.rlh"
	{ return false; }
	break;
#line 107 "include/jsmincpp/deserialize/ParseUInt.h"
	}
	}

	_out: {}
	}

#line 40 "include/jsmincpp/deserialize/ParseUInt.rlh"

  return false;
}

}          // namespace deserialize

}          // namespace jsmincpp

#endif         // INCLUDE_DESERIALIZE_PARSEUINT_H_
