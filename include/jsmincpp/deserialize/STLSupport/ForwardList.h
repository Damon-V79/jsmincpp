#ifndef INCLUDE_DESERIALIZE_STLSUPPORT_FORWARDLIST_H_
#define INCLUDE_DESERIALIZE_STLSUPPORT_FORWARDLIST_H_

#include <jsmincpp/deserialize/STLSupport/STLContiners.h>
#include <forward_list>

namespace jsmincpp {

namespace deserialize {

template < typename T, typename A >
struct ForwardListTraits {
  typedef T value_type;

  static void Push( std::forward_list < T, A > &a, value_type &d ) {
    a.push_front( d );
  }
};

template < uint32_t Hash, typename T, typename A >
STLContinerParam < Hash, std::forward_list < T, A >, ForwardListTraits < T, A > > MakeParam(
    std::forward_list < T, A > &param ) {
  return STLContinerParam < Hash, std::forward_list < T, A >,
      ForwardListTraits < T, A > >( param );
}

}          //namespace deserialize

}          // namespace jsmincpp

#endif /* INCLUDE_DESERIALIZE_STLSUPPORT_FORWARDLIST_H_ */
