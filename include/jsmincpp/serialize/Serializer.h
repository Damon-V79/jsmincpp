#ifndef INCLUDE_SERIALIZE_SERIALIZER_H_
#define INCLUDE_SERIALIZE_SERIALIZER_H_

#include <jsmincpp/TypesUtilities.h>

#define SERIALIZE( x ) ( { \
  const char name[ ] = { #x }; \
  if ( !serializer.Serialize( name, x ) ) return false; \
  } )

namespace jsmincpp {

namespace serialize {

class Serialized {
};

template < typename S >
class AbstractSerialized : public Serialized {
public:
  virtual ~AbstractSerialized( ) {
  }
  virtual bool Serialize( S & ) const = 0;
};

template < typename S >
class Serializer : public S {
public:
  template < typename H >
  Serializer( H &handler )
      :
          S( handler ) {
  }

  template < typename T >
  bool Serialize( const T &data ) {
    return Serialize( data,
        Int2Type < IsRelated < Serialized, T >::value >( ) );
  }
  template < typename T >
  bool Serialize( const T &data, const Int2Type < false > & ) {
    return *this << data;
  }
  template < typename T >
  bool Serialize( const T &data, const Int2Type < true > & ) {
    return ( this->ObjectStart( ) )
        && ( data.Serialize( *this ) )
        && ( this->ObjectEnd( ) );
  }
  bool Serialize( AbstractSerialized < Serializer < S > > *data ) {
    return ( this->ObjectStart( ) )
        && ( data->Serialize( *this ) )
        && ( this->ObjectEnd( ) );
  }
  template < typename T, uint32_t Nums >
  bool Serialize( const char (&name) [ Nums ], const T &data ) {
    return ( this->ParamName( name, Nums - 1 ) )
        && ( Serialize( data,
            Int2Type < IsRelated < Serialized, T >::value >( ) ) );
  }
  template < typename T, uint32_t Nums1, uint32_t Nums2 >
  bool Serialize( const char (&name) [ Nums1 ], T (&data) [ Nums2 ] ) {
    if ( ( !this->ParamName( name, Nums1 - 1 ) )
        || ( !this->ArrayStart( ) ) )
      return false;
    for ( uint32_t i = 0; i < Nums2; ++i ) {
      if ( ( !this->ArrayItem( ) )
          || ( !Serialize( data [ i ],
              Int2Type < IsRelated < Serialized, T >::value >( ) ) ) )
        return false;
    }
    return this->ArrayEnd( );
  }

private:

};

}          // namespace serialize

}          // namespace jsmincpp

#endif          // INCLUDE_SERIALIZE_SERIALIZER_H_
