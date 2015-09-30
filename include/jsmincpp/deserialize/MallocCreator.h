#ifndef INCLUDE_DESERIALIZE_MALLOCCREATOR_H_
#define INCLUDE_DESERIALIZE_MALLOCCREATOR_H_

#include <stdlib.h>

namespace jsmincpp {

namespace deserialize {

struct MallocCreator {
  static int32_t m_allocateCounter;

  template< typename T >
  static T * Create( const T & ) {
    void *buff = ::malloc( sizeof( T ) );
    if( !buff )
      return nullptr;
    ++m_allocateCounter;
    return new( buff ) T;
  }

  static void Delete( void *ptr ) {
    ::free( ptr );
    --m_allocateCounter;
  }
};

}          // namespace deserialize

}          // namespace jsmincpp

#endif         // INCLUDE_DESERIALIZE_MALLOCCREATOR_H_
