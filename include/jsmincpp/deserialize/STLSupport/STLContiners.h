#ifndef INCLUDE_DESERIALIZE_STLSUPPORT_STLCONTINERS_H_
#define INCLUDE_DESERIALIZE_STLSUPPORT_STLCONTINERS_H_

#include <jsmincpp/deserialize/Params.h>

namespace jsmincpp {

namespace deserialize {

template < uint32_t Hash, typename Continer, typename Traits >
class STLContinerParam {
public:
  enum {
    HASH = Hash
  };

  STLContinerParam( Continer &param )
      :
          _param( param ) {
  }

  template < typename D >
  bool Parse( D &deserializer ) {
    auto &stream = deserializer.GetStream( );

    if ( '[' != *stream )
      return false;
    ++stream;

    while ( true ) {
      typename Traits::value_type tmp;
      auto param = MakeParam< 0 >( tmp );
      if ( !param.Parse( deserializer ) )
        return false;
      Traits::Push( _param, tmp );

      if ( ',' == *stream ) {
        ++stream;
        continue;
      } else if ( ']' == *stream ) {
        ++stream;
        break;
      } else
        return false;
    }
    return true;
  }

private:
  Continer &_param;
};

}          //namespace deserialize

}          // namespace jsmincpp

#endif /* INCLUDE_DESERIALIZE_STLSUPPORT_STLCONTINERS_H_ */
