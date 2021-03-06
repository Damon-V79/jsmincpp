#ifndef INCLUDE_SERIALIZE_STLSUPPORT_DEQUE_H_
#define INCLUDE_SERIALIZE_STLSUPPORT_DEQUE_H_

#include <deque>

namespace jsmincpp {

namespace serialize {

template < typename S, typename T, typename A >
bool operator <<( S &serializer, const std::deque < T, A > &data ) {
  if ( !serializer.ArrayStart( ) )
    return false;

  typename std::deque < T, A >::size_type length = data.size( );

  for ( typename std::deque < T, A >::size_type i = 0; i < length; ++i ) {
    if ( !serializer.ArrayItem( )
        || !serializer.Serialize( data [ i ] ) )
      return false;
  }

  return serializer.ArrayEnd( );
}

}          // namespace serialize

}          // namespace jsmincpp

#endif          // INCLUDE_SERIALIZE_STLSUPPORT_DEQUE_H_
