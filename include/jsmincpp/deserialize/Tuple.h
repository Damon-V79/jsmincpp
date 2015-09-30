#ifndef INCLUDE_DESERIALIZE_TUPLE_H_
#define INCLUDE_DESERIALIZE_TUPLE_H_

#include <cstdint>

namespace jsmincpp {

namespace deserialize {

/*
 * class Tuple
 * From http://habrahabr.ru/post/228031/
 */

template < typename ... Args >
struct Tuple;

template < typename Head, typename ... Tail >
struct Tuple < Head, Tail... > : Tuple < Tail... > {
  typedef Head Value_t;
  typedef Tuple < Tail... > Base_t;
  enum {
    SIZE = sizeof(Head),
    MAX_SIZE = ( ( SIZE > Base_t::SIZE ) ?
        SIZE : Base_t::SIZE )
  };

  Tuple( Head &h, Tail &... tail )
      :
          Tuple < Tail... >( tail... ),
          _head( h )
  {
  }

  Head &_head;

  template < typename D >
  bool operator()( uint32_t hash, D &deserializer ) {
    if ( Head::HASH == hash )
      return _head.Parse( deserializer );
    else
      return Base_t::operator()( hash, deserializer );
  }

};

template < >
struct Tuple < >
{
  enum {
    SIZE = 0,
    MAX_SIZE = 0
  };

  template < typename D >
  bool operator()( uint32_t hash, D &deserializer ) {
    return false;
  }
};

template < typename ... Args >
Tuple < Args ... > MakeTuple( Args &... args ) {
  return Tuple < Args ... >( args ... );
}

template < typename ... Args >
struct ObjectsList;

template < typename Head, typename ... Tail >
struct ObjectsList < Head, Tail... > : ObjectsList < Tail... > {
  typedef ObjectsList < Tail... > Base_t;
  enum {
    SIZE = sizeof(typename Head::Object_t),
    MAX_SIZE = ( ( SIZE > Base_t::SIZE ) ?
        SIZE : Base_t::SIZE )
  };

  ObjectsList( )
      :
          Base_t( )
  {
  }

  template < typename D, typename H >
  bool operator()( uint32_t hash, D &deserializer, H &handler ) {
    if ( Head::HASH == hash ) {
      bool ret = true;
      auto t =
          deserializer.GetCreator( ).Create( typename Head::Object_t( ) );
      if( nullptr == t )
        return false;

      ret &= t->Deserialize( deserializer );
      if ( ret && ( '}' == *( deserializer.GetStream( ) ) ) )
        ret &= handler( t );
      ++deserializer.GetStream( );

      if( !ret )
        deserializer.GetCreator( ).Delete( t );

      return ret;
    } else
      return Base_t::operator()( hash, deserializer, handler );
  }

};

template < >
struct ObjectsList < >
{
  enum {
    SIZE = 0,
    MAX_SIZE = 0
  };

  template < typename D, typename H >
  bool operator()( uint32_t hash, D &deserializer, H &handler ) {
    return false;
  }
};

}          // namespace deserialize

}          // namespace jsmincpp

#endif         // INCLUDE_DESERIALIZE_TUPLE_H_
