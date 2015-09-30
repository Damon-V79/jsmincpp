#ifndef INCLUDE_FLOATPOINT_3X1_H_
#define INCLUDE_FLOATPOINT_3X1_H_

#include <cmath>
#include <cstdint>
#include <cstdio>

namespace jsmincpp {

class FloatPoint_3x1 {
public:
  FloatPoint_3x1( )
      :
          _val( 0.0f ) {
  }

  FloatPoint_3x1( float val )
      :
          _val( val ) {
  }

  float GetValue( ) const {
    return _val;
  }

private:
  float _val;

};

namespace serialize {

template < typename S >
bool operator <<( S &serializer, const FloatPoint_3x1 &data ) {
  const char f [ ] = "%3.1f";
  char buffer [ 10 ];
  uint32_t len = ::sprintf( buffer, f, data.GetValue( ) );
  return ( len > 0 ) && serializer.GetHandler( )( buffer, len );
}

}          // namespace serialize

}          // namespace jsmincpp

#endif          // INCLUDE_SERIALIZE_FLOATPOINT_3X1_H_
