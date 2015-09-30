#ifndef INCLUDE_DESERIALIZE_STLSUPPORT_MAP_H_
#define INCLUDE_DESERIALIZE_STLSUPPORT_MAP_H_

#include <jsmincpp/deserialize/STLSupport/STLContiners.h>
#include <map>

namespace jsmincpp {

namespace deserialize {

template < typename K, typename T >
struct Pair {
  K _key;
  T _value;

  Pair( )
      :
          _key( ),
          _value( ) {
  }

  template < typename D >
  bool Deserialize( D &deserializer ) {
    return deserializer(
        MakeParam < Crc32( "key" ) >( _key ),
        MakeParam < Crc32( "value" ) >( _value )
            );
  }

  std::pair< K, T > GetPair( ) {
    return std::make_pair( _key, _value );
  }

};

template < typename K, typename T, typename C, typename A >
struct MapTraits {
  typedef Pair< K, T > value_type;

  static void Push( std::map < K, T, C, A > &a, value_type &d ) {
    a.insert( d.GetPair( ) );
  }
};

template < typename K, typename T, typename C, typename A >
struct MultiMapTraits {
  typedef Pair< K, T > value_type;

  static void Push( std::multimap < K, T, C, A > &a, T &d ) {
    a.insert( d.GetPair( ) );
  }
};

template < uint32_t Hash, typename K, typename T, typename C, typename A >
STLContinerParam < Hash, std::map < K, T, C, A >, MapTraits < K, T, C, A > > MakeParam(
    std::map < K, T, C, A > &param ) {
  return STLContinerParam < Hash, std::map < K, T, C, A >,
      MapTraits < K, T, C, A > >( param );
}

template < uint32_t Hash, typename K, typename T, typename C, typename A >
STLContinerParam < Hash, std::multimap < K, T, C, A >,
    MultiMapTraits < K, T, C, A > > MakeParam(
    std::multimap < K, T, C, A > &param ) {
  return STLContinerParam < Hash, std::multimap < K, T, C, A >,
      MultiMapTraits < K, T, C, A > >( param );
}

}          //namespace deserialize

}          // namespace jsmincpp

#endif /* INCLUDE_DESERIALIZE_STLSUPPORT_MAP_H_ */
