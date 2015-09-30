#ifndef INCLUDE_DESERIALIZE_STLSUPPORT_VECTOR_H_
#define INCLUDE_DESERIALIZE_STLSUPPORT_VECTOR_H_

#include <jsmincpp/deserialize/STLSupport/STLContiners.h>
#include <vector>

namespace jsmincpp {

namespace deserialize {

template < typename T, typename A >
struct VectorTraits {
  typedef T value_type;

  static void Push( std::vector < T, A > &a, value_type &d ) {
    a.push_back( d );
  }
};

template < uint32_t Hash, typename T, typename A >
STLContinerParam < Hash, std::vector < T, A >, VectorTraits < T, A > > MakeParam(
    std::vector < T, A > &param ) {
  return STLContinerParam < Hash, std::vector < T, A >, VectorTraits < T, A > >(
      param );
}

}          //namespace deserialize

}          // namespace jsmincpp

#endif /* INCLUDE_DESERIALIZE_STLSUPPORT_VECTOR_H_ */
