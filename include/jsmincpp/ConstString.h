/*
 * ConstString.h
 *
 *  Created on: 6 сент. 2015 г.
 *      Author: damon
 */

#ifndef INCLUDE_CONSTSTRING_H_
#define INCLUDE_CONSTSTRING_H_

#include <cstring>

namespace jsmincpp {

class ConstString {
public:
  ConstString( )
      :
          _str( nullptr ),
          _strLen( 0 ) {
  }
  ConstString( const char *str )
      :
          _str( str ),
          _strLen( ::strlen( str ) ) {
  }
  ConstString( const char *str, uint32_t strLen )
      :
          _str( str ),
          _strLen( strLen ) {
  }
  template < uint32_t Len >
  ConstString( const char (&str) [ Len ] )
      :
          _str( str ),
          _strLen( Len ) {
  }

  const char * c_str( ) const {
    return _str;
  }
  uint32_t length( ) const {
    return _strLen;
  }

private:
  const char *_str;
  uint32_t _strLen;

};

namespace serialize {

template < typename S >
bool operator <<( S &serializer, const ConstString &str ) {
  const char s [ ] = { "\"" };
  return serializer.GetHandler( )( s, sizeof( s ) - 1 )
      && serializer.GetHandler( )( str.c_str( ), str.length( ) )
      && serializer.GetHandler( )( s, sizeof( s ) - 1 );
}

}          // namespace serialize

}          // namespace jsmincpp

#endif          // INCLUDE_CONSTSTRING_H_
