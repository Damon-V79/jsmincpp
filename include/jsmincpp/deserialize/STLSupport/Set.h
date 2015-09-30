#ifndef INCLUDE_DESERIALIZE_STLSUPPORT_SET_H_
#define INCLUDE_DESERIALIZE_STLSUPPORT_SET_H_

#include <jsmincpp/deserialize/STLSupport/STLContiners.h>
#include <set>

namespace jsmincpp {

namespace deserialize {

template < typename T, typename C, typename A >
struct SetTraits {
  typedef T value_type;

  static void Push( std::set < T, C, A > &a, value_type &d ) {
    a.insert( d );
  }
};

template < typename T, typename C, typename A >
struct MultiSetTraits {
  typedef T value_type;

  static void Push( std::multiset < T, C, A > &a, T &d ) {
    a.insert( d );
  }
};

template < uint32_t Hash, typename T, typename C, typename A >
STLContinerParam < Hash, std::set < T, C, A >, SetTraits < T, C, A > > MakeParam(
    std::set < T, C, A > &param ) {
  return STLContinerParam < Hash, std::set < T, C, A >, SetTraits < T, C, A > >(
      param );
}

template < uint32_t Hash, typename T, typename C, typename A >
STLContinerParam < Hash, std::multiset < T, C, A >, MultiSetTraits < T, C, A > > MakeParam(
    std::multiset < T, C, A > &param ) {
  return STLContinerParam < Hash, std::multiset < T, C, A >,
      MultiSetTraits < T, C, A > >( param );
}

}          //namespace deserialize

}          // namespace jsmincpp

#endif /* INCLUDE_DESERIALIZE_STLSUPPORT_SET_H_ */
