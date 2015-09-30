#ifndef INCLUDE_INTEGEROVERFLOWCONTROL_H_
#define INCLUDE_INTEGEROVERFLOWCONTROL_H_

#include <cstdint>

namespace jsmincpp {

template< typename T >
struct MaxValues;

template< >
struct MaxValues< int8_t > {
  static const int8_t maxVal = INT8_MAX;
};

template< >
struct MaxValues< int16_t > {
  static const int16_t maxVal = INT16_MAX;
};

template< >
struct MaxValues< int32_t > {
  static const int32_t maxVal = INT32_MAX;
};

template< >
struct MaxValues< int64_t > {
  static const int64_t maxVal = INT64_MAX;
};

template< >
struct MaxValues< uint8_t > {
  static const uint8_t maxVal = UINT8_MAX;
};

template< >
struct MaxValues< uint16_t > {
  static const uint16_t maxVal = UINT16_MAX;
};

template< >
struct MaxValues< uint32_t > {
  static const uint32_t maxVal = UINT32_MAX;
};

template< >
struct MaxValues< uint64_t > {
  static const uint64_t maxVal = UINT64_MAX;
};

  /*
   *  From http://dxdy.ru/topic6934.html
   */

template< typename T >
struct IntegerOverflowControl {
  static T Summ ( T &res, const T a )
  {
    if( MaxValues< T >::maxVal - a < res )
      return false;

    res += a;
    return true;
  }

  static T Mult ( T &res, const T a )
  {
    if( MaxValues< T >::maxVal / a < res )
      return false;

    res *= a;
    return true;
  }
};

}          // namespace jsmincpp

#endif /* INCLUDE_INTEGEROVERFLOWCONTROL_H_ */
