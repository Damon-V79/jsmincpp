#ifndef INCLUDE_DESERIALIZE_STLSUPPORT_LIST_H_
#define INCLUDE_DESERIALIZE_STLSUPPORT_LIST_H_

#include <jsmincpp/deserialize/STLSupport/STLContiners.h>
#include <list>

namespace jsmincpp {

namespace deserialize {

template < typename T, typename A >
struct ListTraits {
  typedef T value_type;

  static void Push( std::list < T, A > &a, value_type &d ) {
    a.push_back( d );
  }
};

template < uint32_t Hash, typename T, typename A >
STLContinerParam < Hash, std::list < T, A >, ListTraits < T, A > > MakeParam(
    std::list < T, A > &param ) {
  return STLContinerParam < Hash, std::list < T, A >, ListTraits < T, A > >(
      param );
}

}          //namespace deserialize

}          // namespace jsmincpp

#endif /* INCLUDE_DESERIALIZE_STLSUPPORT_LIST_H_ */
