
#line 1 "include/jsmincpp/deserialize/GetNameHash.rlh"
#ifndef INCLUDE_DESERIALIZE_GETNAME_H_
#define INCLUDE_DESERIALIZE_GETNAME_H_

#include <jsmincpp/deserialize/CRC32Hash.h>

#include <cstdint>

namespace jsmincpp {

namespace deserialize {

template < typename S >
bool GetNameHash( S &p, CRC32Hash &h ) {

  
#line 16 "include/jsmincpp/deserialize/GetNameHash.rlh"
  
#line 21 "include/jsmincpp/deserialize/GetNameHash.h"
static const int NameParser_start = 1;
static const int NameParser_first_final = 5;
static const int NameParser_error = 0;

static const int NameParser_en_main = 1;


#line 17 "include/jsmincpp/deserialize/GetNameHash.rlh"

  int cs;
  S pe = p.End( );
  S eof = p.End( );

  
#line 36 "include/jsmincpp/deserialize/GetNameHash.h"
	{
	cs = NameParser_start;
	}

#line 23 "include/jsmincpp/deserialize/GetNameHash.rlh"
  
#line 30 "include/jsmincpp/deserialize/GetNameHash.rlh"


  
#line 47 "include/jsmincpp/deserialize/GetNameHash.h"
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
#line 26 "include/jsmincpp/deserialize/GetNameHash.rlh"
	{ h.Reset( ); return false; }
	goto st0;
#line 61 "include/jsmincpp/deserialize/GetNameHash.h"
st0:
cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 95 )
		goto tr2;
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 49 )
			goto tr2;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr2;
	} else
		goto tr2;
	goto tr0;
tr2:
#line 25 "include/jsmincpp/deserialize/GetNameHash.rlh"
	{ h( *p ); }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 88 "include/jsmincpp/deserialize/GetNameHash.h"
	switch( (*p) ) {
		case 34: goto st4;
		case 95: goto tr2;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 49 )
			goto tr2;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr2;
	} else
		goto tr2;
	goto tr0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 58 )
		goto tr4;
	goto tr0;
tr4:
#line 27 "include/jsmincpp/deserialize/GetNameHash.rlh"
	{ return true; }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 117 "include/jsmincpp/deserialize/GetNameHash.h"
	goto tr0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 1: 
	case 2: 
	case 3: 
	case 4: 
#line 26 "include/jsmincpp/deserialize/GetNameHash.rlh"
	{ h.Reset( ); return false; }
	break;
#line 136 "include/jsmincpp/deserialize/GetNameHash.h"
	}
	}

	_out: {}
	}

#line 33 "include/jsmincpp/deserialize/GetNameHash.rlh"

  return true;
}

}          // namespace deserialize

}          // namespace jsmincpp

#endif         // INCLUDE_DESERIALIZE_GETNAME_H_
