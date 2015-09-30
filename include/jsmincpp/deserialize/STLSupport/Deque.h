#ifndef INCLUDE_DESERIALIZE_STLSUPPORT_DEQUE_H_
#define INCLUDE_DESERIALIZE_STLSUPPORT_DEQUE_H_

#include <jsmincpp/deserialize/STLSupport/STLContiners.h>
#include <deque>

namespace jsmincpp {

namespace deserialize {

template < typename T, typename A >
struct DequeTraits {
  typedef T value_type;

  static void Push( std::deque < T, A > &a, value_type &d ) {
    a.push_back( d );
  }
};

template < uint32_t Hash, typename T, typename A >
STLContinerParam < Hash, std::deque < T, A >, DequeTraits < T, A > > MakeParam(
    std::deque < T, A > &param ) {
  return STLContinerParam < Hash, std::deque < T, A >, DequeTraits < T, A > >(
      param );
}

}          //namespace deserialize

}          // namespace jsmincpp

#endif /* INCLUDE_DESERIALIZE_STLSUPPORT_DEQUE_H_ */
