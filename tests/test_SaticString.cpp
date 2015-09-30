#undef GTEST_LANG_CXX11

#include "SymbolStream.h"

#include <jsmincpp/deserialize/Deserializer.h>

#include <jsmincpp/StaticString.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>

using namespace jsmincpp;
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

struct TestStaticString {
  StaticString< 20 > String;

  template < typename D >
  bool Deserialize( D &deserializer ) {
    return deserializer(
        DESERIALIZE( String )
            );
  }
};

TEST (StaticString, test) {
  StaticString < 20 > str( "StaticString" );
  ASSERT_STREQ( str.GetString( ), "StaticString" );

  str.Assign( "New value" );
  ASSERT_STREQ( str.GetString( ), "New value" );

  str.Add( '!' );
  ASSERT_STREQ( str.GetString( ), "New value!" );
}

TEST (StaticString, Deserialize) {
  const char *json =
      "{\"String\":\"It's work!\"}";
  SymbolStream s( json );

  typedef ObjectsList <
  DESERIALIZEOBJ(NullObj)
      > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t
  > d( s );

  TestStaticString data;
  ASSERT_TRUE( d.Deserialize( &data ) );
  ASSERT_STREQ( data.String.GetString( ), "It's work!" );
}

TEST (StaticString, LongStringError) {
  const char *json =
      "{\"String\":\"It's lo-o-o-o-ong string!\"}";
  SymbolStream s( json );

  typedef ObjectsList <
  DESERIALIZEOBJ(NullObj)
      > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t
  > d( s );

  TestStaticString data;
  ASSERT_FALSE( d.Deserialize( &data ) );
  ASSERT_EQ( data.String.GetLength( ), 20 );
}
