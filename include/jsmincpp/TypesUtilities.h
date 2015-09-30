#ifndef INCLUDE_TYPESUTILITIES_H_
#define INCLUDE_TYPESUTILITIES_H_

#include <cstdint>
#include <cstddef>

namespace jsmincpp {

template < typename ... Args >
struct MaxSizeTypes;

template < typename Head, typename ... Tail >
struct MaxSizeTypes < Head, Tail... > : MaxSizeTypes < Tail... > {
  typedef MaxSizeTypes < Tail... > Base_t;
  enum {
    Size = ( sizeof(Head) > ( size_t ) Base_t::Size ) ?
        sizeof(Head) : ( size_t ) Base_t::Size
  };
};

template < >
struct MaxSizeTypes < > {
  enum {
    Size = 0
  };
};

/*
 *
 */

template < typename H, typename ... T >
struct FirstType {
  typedef H Type_t;
};

/*
 *
 */

template < int v >
struct Int2Type
{
  enum {
    value = v
  };
};

/*
 *  From http://www.dreamincode.net/forums/topic/140936-determining-the-base-class-from-a-derived-class/
 */

template < typename BaseT, typename DerivedT >
struct IsRelated {
  static DerivedT derived( );
  static char test( const BaseT& );          // sizeof(test()) == sizeof(char)
  static char (&test( ...))[ 2 ];          // sizeof(test()) == sizeof(char[2])
  enum {
    value = ( sizeof( test( derived( ) ) ) == sizeof(char) )
  };
};

template < typename BaseT, typename DerivedT >
constexpr bool isRelated( const DerivedT& )
    {
  return IsRelated < BaseT, DerivedT >::value;
}

template < typename BaseT, typename DerivedT >
constexpr bool isRelated( DerivedT& )
    {
  return IsRelated < BaseT, DerivedT >::value;
}

}          // namespace jsmincpp

#endif          // INCLUDE_TYPESUTILITIES_H_
