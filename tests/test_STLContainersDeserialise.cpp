#undef GTEST_LANG_CXX11

#include "SymbolStream.h"

#include <jsmincpp/deserialize/Deserializer.h>
#include <jsmincpp/deserialize/STLSupport/SharedPrtCreator.h>

#include <jsmincpp/deserialize/STLSupport/Vector.h>
#include <jsmincpp/deserialize/STLSupport/Deque.h>
#include <jsmincpp/deserialize/STLSupport/List.h>
#include <jsmincpp/deserialize/STLSupport/ForwardList.h>
#include <jsmincpp/deserialize/STLSupport/Set.h>
#include <jsmincpp/deserialize/STLSupport/Map.h>

#include <jsmincpp/deserialize/STLSupport/String.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>

using namespace jsmincpp::deserialize;
using namespace std;
using ::testing::ElementsAreArray;
using ::testing::ElementsAre;
using ::testing::ContainerEq;
using ::testing::InSequence;
using ::testing::TypedEq;
using ::testing::StrEq;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;
using ::testing::An;

struct InternalClass {
  int8_t One;
  uint8_t Two;

  InternalClass( )
      :
          One( 0 ),
          Two( 0 ) {
  }

  InternalClass( int8_t one, uint8_t two )
      :
          One( one ),
          Two( two ) {
  }

  template < typename D >
  bool Deserialize( D &deserializer ) {
    return deserializer(
        DESERIALIZE( One ),
        DESERIALIZE( Two )
            );
  }
};

bool operator==( const InternalClass &a, const InternalClass &b ) {
  return ( a.One == b.One ) && ( a.Two == b.Two );
}

template< typename Continer >
struct ContinerTest {
  Continer Array;

  template < typename D >
  bool Deserialize( D &deserializer ) {
    return deserializer(
        DESERIALIZE( Array )
            );
  }
};


TEST (STLContainersDeserialiseTest, Vector) {
  const char *json =
      "{\"Array\":[1.0e10,2.0e10,3.0e10,4.0e10,5.0e10]}";
  SymbolStream s( json );

  typedef ObjectsList <
  DESERIALIZEOBJ(NullObj)
      > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t
  > d( s );

  ContinerTest< vector < float > > data;
  ASSERT_TRUE( d.Deserialize( &data ) );

  vector < float > check = { 1.0e10f, 2.0e10f, 3.0e10f, 4.0e10f, 5.0e10f };
  EXPECT_THAT( data.Array, check );
}

TEST (STLContainersDeserialiseTest, Deque) {
  const char *json =
      "{\"Array\":[{\"One\":-10,\"Two\":10},{\"One\":-30,\"Two\":40}]}";
  SymbolStream s( json );

  typedef ObjectsList <
  DESERIALIZEOBJ(NullObj)
      > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t
  > d( s );

  ContinerTest< deque < InternalClass > > data;
  ASSERT_TRUE( d.Deserialize( &data ) );

  deque < InternalClass > check = { InternalClass( -10, 10 ), InternalClass( -30, 40 ) };
  EXPECT_THAT( data.Array, check );
}

TEST (STLContainersDeserialiseTest, Map) {
  const char *json =
      "{\"Array\":[{\"key\":1,\"value\":10},{\"key\":30,\"value\":40}]}";
  SymbolStream s( json );

  typedef ObjectsList <
  DESERIALIZEOBJ(NullObj)
      > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t
  > d( s );

  ContinerTest< map < uint8_t, uint8_t > > data;
  ASSERT_TRUE( d.Deserialize( &data ) );

  map < uint8_t, uint8_t > check = {
      make_pair< uint8_t, uint8_t >( 1, 10 ),
      make_pair< uint8_t, uint8_t >( 30, 40 )
  };
  EXPECT_THAT( data.Array, check );
}

TEST (STLContainersDeserialiseTest, String) {
  const char *json =
      "{\"Array\":\"It's work!\"}";
  SymbolStream s( json );

  typedef ObjectsList <
  DESERIALIZEOBJ(NullObj)
      > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t
  > d( s );

  ContinerTest< string > data;
  ASSERT_TRUE( d.Deserialize( &data ) );

  string check( "It's work!" );
  EXPECT_THAT( data.Array, check );
}

