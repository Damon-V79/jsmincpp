#ifndef INCLUDE_DESERIALIZE_DESERIALIZER_H_
#define INCLUDE_DESERIALIZE_DESERIALIZER_H_

#include <jsmincpp/deserialize/CRC32Hash.h>
#include <jsmincpp/deserialize/Params.h>
#include <jsmincpp/deserialize/Tuple.h>

#include <jsmincpp/deserialize/SkipEndJSONString.h>
#include <jsmincpp/deserialize/GetNameHash.h>

#define DESERIALIZEOBJ( x ) jsmincpp::deserialize::ObjectParam < jsmincpp::deserialize::Crc32( #x ), x >
#define DESERIALIZE( x ) jsmincpp::deserialize::MakeParam < jsmincpp::deserialize::Crc32( #x ) >( x )

namespace jsmincpp {

namespace deserialize {

class NullObj {

};

template < uint32_t BuffSize >
class StaticCreator {
public:
  uint32_t _buff [ BuffSize / 4 + 1 ];

  template < typename T >
  T * Create( const T & ) {
    return new ( _buff ) T;
  }

  template < typename T >
  void Delete( T * ) {
  }
};

template < typename Stream, typename ObjList,
    typename Creator = StaticCreator < ObjList::MAX_SIZE > >
class Deserializer {
public:
  Deserializer(
      Stream &stream,
      Creator creator = Creator( ) )
      :
          _stream( stream ),
          _creator( creator ) {
  }

  template < typename H >
  bool Deserialize( H &handler ) {
    ObjList objects;
    CRC32Hash hash;

    if ( '{' != *_stream ) {
      ++_stream;
      return false;
    }
    ++_stream;

    if ( !GetNameHash( _stream, hash ) )
      return SkipEndJSONString( _stream );
    ++_stream;

    return objects( hash, *this, handler );
  }

  template < typename O >
  bool Deserialize( O *obj ) {
    return obj->Deserialize( *this );
  }

  bool operator()( ) {
    if ( ( 'n' != *_stream )
        || ( 'u' != *( ++_stream ) )
        || ( 'l' != *( ++_stream ) )
        || ( 'l' != *( ++_stream ) )
        )
      return SkipEndJSONString( _stream );

    ++_stream;
    return true;
  }

  template < typename ... P >
  bool operator()( P ... p ) {
    auto params = MakeTuple( p ... );

    if ( '{' != *_stream )
      return SkipEndJSONString( _stream );
    ++_stream;

    while ( true ) {
      CRC32Hash hash;
      if ( !GetNameHash( _stream, hash ) )
        return SkipEndJSONString( _stream );
      ++_stream;

      if ( !params( hash, *this ) )
        return SkipEndJSONString( _stream );

      if ( ',' == *_stream ) {
        ++_stream;
        continue;
      } else if ( '}' == *_stream ) {
        ++_stream;
        break;
      } else
        return false;
    }
    return true;
  }

  Creator & GetCreator( ) {
    return _creator;
  }

  Stream & GetStream( ) {
    return _stream;
  }

private:
  Stream &_stream;
  Creator _creator;

};

}          //namespace deserialize

}          // namespace jsmincpp

#endif         // INCLUDE_DESERIALIZE_DESERIALIZER_H_
