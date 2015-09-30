#ifndef INCLUDE_SERIALIZE_STLSUPPORT_MAP_H_
#define INCLUDE_SERIALIZE_STLSUPPORT_MAP_H_

#include <jsmincpp/serialize/Serializer.h>
#include <jsmincpp/serialize/JSONSerializer.h>

#include <map>
#include <algorithm>

namespace jsmincpp {

namespace serialize {

template < typename K, typename T >
struct Pair : public Serialized {
  const K &key;
  const T &value;

  Pair( const K &k, const T &v )
      :
          key( k ),
          value( v ) {
  }

  template < typename S >
  bool Serialize( S &serializer ) const {
    SERIALIZE( key );
    SERIALIZE( value );
    return true;
  }

};

template < typename S, typename K, typename T, typename C, typename A >
bool operator <<( S &serializer, const std::map < K, T, C, A > &data ) {
  if ( !serializer.ArrayStart( ) )
    return false;

  std::find_if_not( data.begin( ), data.end( ),
      [ &serializer ] ( const std::pair< K, T > &elem ) {
        Pair< K, T > p( elem.first, elem.second );
        return serializer.ArrayItem( )
            && serializer.Serialize( p );
      } );

  return serializer.ArrayEnd( );
}

}          // namespace serialize

}          // namespace jsmincpp

#endif          // INCLUDE_SERIALIZE_STLSUPPORT_MAP_H_
