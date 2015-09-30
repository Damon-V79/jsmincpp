#ifndef INCLUDE_SERIALIZE_JSONSERIALIZER_H_
#define INCLUDE_SERIALIZE_JSONSERIALIZER_H_

#include <jsmincpp/serialize/Serializer.h>
#include <cstdio>
#include <inttypes.h>
#include <float.h>

namespace jsmincpp {

namespace serialize {

//
//    struct SerializeHandler {
//      bool operator()( const char *str, uint32_t len );
//      bool SerializeEnd( );
//    };
//
//    typedef jsmincpp::serialize::Serializer <
//        jsmincpp::serialize::JSONSerializer < SerializeHandler >
//    > Serializer_t;
//

template < typename H >
class JSONSerializer {
public:
  JSONSerializer( H &handler )
      :
          _handler( handler ),
          _firstItem( true ),
          _firstArrayItem( true ),
          _insertedCounter( 0 ) {
  }

  bool ParamName(
      const char *name,
      uint32_t len ) {

    if ( !_firstItem )
      if( !PrintSeparator( ) ) return false;
    _firstItem = false;

    const char b [ ] = { "\"" };
    const char e [ ] = { "\":" };
    return _handler( b, sizeof( b ) - 1 )
        && _handler( name, len )
        && _handler( e, sizeof( e ) - 1 );
  }
  bool ArrayStart( ) {
    _firstArrayItem = true;

    const char str [ ] = { "[" };
    return _handler( str, sizeof( str ) - 1 );
  }
  bool ArrayItem( ) {

    if ( !_firstArrayItem )
      if( !PrintSeparator( ) ) return false;
    _firstArrayItem = false;

    return true;
  }
  bool ArrayEnd( ) {
    const char str [ ] = { "]" };
    return _handler( str, sizeof( str ) - 1 );
  }
  bool ObjectStart( ) {
    ++_insertedCounter;
    _firstItem = true;

    const char str [ ] = { "{" };
    return _handler( str, sizeof( str ) - 1 );
  }
  bool ObjectEnd( ) {
    const char str [ ] = { "}" };
    if( !_handler( str, sizeof( str ) - 1 ) )
      return false;
    if ( --_insertedCounter == 0 )
      return _handler.SerializeEnd( );
    return true;
  }

  H & GetHandler( ) {
    return _handler;
  }

private:
  H &_handler;

  bool _firstItem;
  bool _firstArrayItem;
  uint32_t _insertedCounter;

  bool PrintSeparator( ) {
    const char str [ ] = { "," };
    return _handler( str, sizeof( str ) - 1 );
  }
};



template < typename S >
bool operator <<( S &serializer, bool val ) {
  const char t [ ] = { "true" };
  const char f [ ] = { "false" };
  if ( val )
    return serializer.GetHandler( )( t, sizeof( t ) - 1 );
  else
    return serializer.GetHandler( )( f, sizeof( f ) - 1 );
}



template < typename S >
bool operator <<( S &serializer, int8_t val ) {
  const char f [ ] = "%" PRId8;
  char buffer [ 5 ];
  uint32_t len = ::sprintf( buffer, f, val );
  return ( len > 0 ) && serializer.GetHandler( )( buffer, len );
}

template < typename S >
bool operator <<( S &serializer, int16_t val ) {
  const char f [ ] = "%" PRId16;
  char buffer [ 8 ];
  uint32_t len = ::sprintf( buffer, f, val );
  return ( len > 0 ) && serializer.GetHandler( )( buffer, len );
}

template < typename S >
bool operator <<( S &serializer, int32_t val ) {
  const char f [ ] = "%" PRId32;
  char buffer [ 11 ];
  uint32_t len = ::sprintf( buffer, f, val );
  return ( len > 0 ) && serializer.GetHandler( )( buffer, len );
}

template < typename S >
bool operator <<( S &serializer, int64_t val ) {
  const char f [ ] = "%" PRId64;
  char buffer [ 20 ];
  uint32_t len = ::sprintf( buffer, f, val );
  return ( len > 0 ) && serializer.GetHandler( )( buffer, len );
}



template < typename S >
bool operator <<( S &serializer, uint8_t val ) {
  const char f [ ] = "%" PRIu8;
  char buffer [ 5 ];
  uint32_t len = ::sprintf( buffer, f, val );
  return ( len > 0 ) && serializer.GetHandler( )( buffer, len );
}

template < typename S >
bool operator <<( S &serializer, uint16_t val ) {
  const char f [ ] = "%" PRIu16;
  char buffer [ 8 ];
  uint32_t len = ::sprintf( buffer, f, val );
  return ( len > 0 ) && serializer.GetHandler( )( buffer, len );
}

template < typename S >
bool operator <<( S &serializer, uint32_t val ) {
  const char f [ ] = "%" PRIu32;
  char buffer [ 11 ];
  uint32_t len = ::sprintf( buffer, f, val );
  return ( len > 0 ) && serializer.GetHandler( )( buffer, len );
}

template < typename S >
bool operator <<( S &serializer, uint64_t val ) {
  const char f [ ] = "%" PRIu64;
  char buffer [ 20 ];
  uint32_t len = ::sprintf( buffer, f, val );
  return ( len > 0 ) && serializer.GetHandler( )( buffer, len );
}



template < typename S >
bool operator <<( S &serializer, float val ) {
  const char f [ ] = "%f";
  char buffer [ 20 ];
  uint32_t len = ::sprintf( buffer, f, val );
  return ( len > 0 ) && serializer.GetHandler( )( buffer, len );
  return true;
}

template < typename S >
bool operator <<( S &serializer, double val ) {
  const char f [ ] = "%lf";
  char buffer [ 20 ];
  uint32_t len = ::sprintf( buffer, f, val );
  return ( len > 0 ) && serializer.GetHandler( )( buffer, len );
  return true;
}

}          // namespace serialize

}          // namespace jsmincpp

#endif          // INCLUDE_SERIALIZE_JSONSERIALIZER_H_
