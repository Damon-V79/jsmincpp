#ifndef INCLUDE_STATICSTRING_H_
#define INCLUDE_STATICSTRING_H_

#include <cstdint>
#include <string.h>
#include <jsmincpp/deserialize/ParseStaticString.h>

namespace jsmincpp {

template < uint32_t Num >
class StaticString {
public:
  StaticString( )
      :
          _length( 0 ) {
    _buff [ 0 ] = 0;
  }

  StaticString( const char *str ) {
    Assign( str );
  }


  bool Add( char symbol ) {
    if( Num == _length )
      return false;
    _buff[ _length++ ] = symbol;
    _buff[ _length ] = 0;

    return true;
  }

  bool Add( const char *str ) {
    uint32_t strSize = ::strlen( str );
    if( strSize > Num - _length )
      return false;
    ::strcpy( _buff, str );
    _length += strSize;
    _buff[ _length + 1 ] = 0;
    return true;
  }

  bool Assign( const char *str ) {
    _length = 0;
    _buff[ _length ] = 0;
    return Add( str );
  }

  const char * GetString( ) {
    return _buff;
  }

  uint32_t GetLength( ) {
    return _length;
  }

private:
  uint32_t _length;
  char _buff [ Num + 1 ];
};

namespace deserialize {

template < uint32_t Hash, uint32_t Num >
class StaticStringParam {
public:
  enum {
    HASH = Hash
  };

  StaticStringParam( StaticString< Num > &param )
      :
          _param( param ) {
  }

  template < typename D >
  bool Parse( D &deserializer ) {
    return ParseStaticString( _param, deserializer.GetStream( ) );
  }

private:
  StaticString< Num > &_param;
};

template < uint32_t Hash, uint32_t Num >
StaticStringParam < Hash, Num > MakeParam( StaticString< Num > &param ) {
  return StaticStringParam < Hash, Num >( param );
}

}          //namespace deserialize

}          // namespace jsmincpp

#endif          // INCLUDE_STATICSTRING_H_
