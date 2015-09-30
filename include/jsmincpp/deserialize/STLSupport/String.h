#ifndef INCLUDE_DESERIALIZE_STLSUPPORT_STRING_H_
#define INCLUDE_DESERIALIZE_STLSUPPORT_STRING_H_

#include <jsmincpp/deserialize/STLSupport/ParseStdString.h>
#include <string>

namespace jsmincpp {

namespace deserialize {

template < uint32_t Hash, typename _CharT, typename _Traits, typename _Alloc >
class StringParam {
public:
  enum {
    HASH = Hash
  };

  StringParam( std::basic_string < _CharT, _Traits, _Alloc > &param )
      :
          _param( param ) {
  }

  template < typename D >
  bool Parse( D &deserializer ) {
    return ParseStdString( _param, deserializer.GetStream( ) );
  }

private:
  std::basic_string < _CharT, _Traits, _Alloc > &_param;

};

template < uint32_t Hash, typename _CharT, typename _Traits, typename _Alloc >
StringParam < Hash, _CharT, _Traits, _Alloc > MakeParam(
    std::basic_string < _CharT, _Traits, _Alloc > &param ) {
  return StringParam < Hash, _CharT, _Traits, _Alloc >( param );
}

}          //namespace deserialize

}          // namespace jsmincpp

#endif /* INCLUDE_DESERIALIZE_STLSUPPORT_STRING_H_ */
