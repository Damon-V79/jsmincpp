#ifndef INCLUDE_SERIALIZE_STLSUPPORT_SET_H_
#define INCLUDE_SERIALIZE_STLSUPPORT_SET_H_

#include <set>
#include <algorithm>

namespace jsmincpp {

namespace serialize {

template < typename S, typename T, typename C, typename A >
bool operator <<( S &serializer, const std::set < T, C, A > &data ) {
  if ( !serializer.ArrayStart( ) )
    return false;

  std::find_if_not( data.begin( ), data.end( ),
      [ &serializer ] ( const T &elem ) {
        return ( serializer.ArrayItem( )
            && serializer.Serialize( elem ) );
      } );

  return serializer.ArrayEnd( );
}

}          // namespace serialize

}          // namespace jsmincpp

#endif          // INCLUDE_SERIALIZE_STLSUPPORT_SET_H_
