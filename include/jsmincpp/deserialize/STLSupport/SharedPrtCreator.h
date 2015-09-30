#ifndef INCLUDE_DESERIALIZE_SHAREDPRTCREATOR_H_
#define INCLUDE_DESERIALIZE_SHAREDPRTCREATOR_H_

#include <memory>

namespace jsmincpp {

namespace deserialize {

struct SharedPrtCreator {
  template< typename T >
  static std::shared_ptr< T > Create( const T & ) {
    return std::make_shared< T >( );
  }

  template< typename T >
  static void Delete( std::shared_ptr< T > ) {
  }

};

}          // namespace deserialize

}          // namespace jsmincpp

#endif /* INCLUDE_DESERIALIZE_SHAREDPRTCREATOR_H_ */
