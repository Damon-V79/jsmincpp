#ifndef INCLUDE_SERIALIZE_STLSUPPORT_FORWARDLIST_H_
#define INCLUDE_SERIALIZE_STLSUPPORT_FORWARDLIST_H_

#include <forward_list>
#include <algorithm>

namespace jsmincpp {

namespace serialize {

template < typename S, typename T, typename A >
bool operator <<( S &serializer, const std::forward_list < T, A > &data ) {
  if ( !serializer.ArrayStart( ) )
    return false;

  std::find_if_not( data.begin( ), data.end( ),
      [ &serializer ] ( const T &elem ) {
        return serializer.ArrayItem( )
            && serializer.Serialize( elem );
      } );

  return serializer.ArrayEnd( );
}

}          // namespace serialize

}          // namespace jsmincpp

#endif          // INCLUDE_SERIALIZE_STLSUPPORT_FORWARDLIST_H_
