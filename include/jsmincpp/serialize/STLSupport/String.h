#ifndef INCLUDE_SERIALIZE_STLSUPPORT_STRING_H_
#define INCLUDE_SERIALIZE_STLSUPPORT_STRING_H_

#include <string>
#include <algorithm>

namespace jsmincpp {

namespace serialize {

template < typename S, typename C, typename T, typename A >
bool operator <<( S &serializer, const std::basic_string < C, T, A > &data ) {
  const char q [ ] = { "\"" };

  if ( !serializer.GetHandler( )( q, sizeof( q ) - 1 )
      || !serializer.GetHandler( )( data.c_str( ), data.length( ) ) )
    return false;
  return serializer.GetHandler( )( q, sizeof( q ) - 1 );
}

}          // namespace serialize

}          // namespace jsmincpp

#endif          // INCLUDE_SERIALIZE_STLSUPPORT_STRING_H_
