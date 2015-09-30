#undef GTEST_LANG_CXX11

#include "MockSerializeHandler.h"

#include <jsmincpp/serialize/JSONSerializer.h>

#include <jsmincpp/serialize/STLSupport/Vector.h>
#include <jsmincpp/serialize/STLSupport/Deque.h>
#include <jsmincpp/serialize/STLSupport/List.h>
#include <jsmincpp/serialize/STLSupport/ForwardList.h>
#include <jsmincpp/serialize/STLSupport/Set.h>
#include <jsmincpp/serialize/STLSupport/Map.h>

#include <jsmincpp/serialize/STLSupport/String.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>

using namespace std;
using namespace jsmincpp;
using namespace jsmincpp::serialize;
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

struct InternalClass : public Serialized {
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

  template < typename S >
  bool Serialize( S &serializer ) const {
    SERIALIZE( One );
    SERIALIZE( Two );
    return true;
  }
};

template < typename Continer >
struct ContinerTest : public Serialized {
  Continer Array;

  template < typename S >
  bool Serialize( S &serializer ) const {
    SERIALIZE( Array );
    return true;
  }
};

TEST (STLContainersSerialiseTest, Vector) {
  InSequence dummy0;

  MockSerializeHandler mockHandler;
  Serializer_t serializer( mockHandler );
  ContinerTest < vector < float > > obj;

  obj.Array.push_back( 10.01f );
  obj.Array.push_back( 20.02f );
  obj.Array.push_back( 30.03f );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "Array" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "[" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "10.010000" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "20.020000" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "30.030001" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "]" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( ) ).WillOnce( Return( true ) );

  ASSERT_TRUE( serializer.Serialize( obj ) );
}

TEST (STLContainersSerialiseTest, Deque) {
  InSequence dummy1;

  MockSerializeHandler mockHandler;
  Serializer_t serializer( mockHandler );
  ContinerTest < deque < InternalClass > > obj;

  obj.Array.push_back( InternalClass( -10, 10 ) );
  obj.Array.push_back( InternalClass( -20, 20 ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "Array" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "[" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "One" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "-10" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "Two" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "10" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "One" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "-20" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "Two" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "20" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "]" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( ) ).WillOnce( Return( true ) );

  ASSERT_TRUE( serializer.Serialize( obj ) );
}

TEST (STLContainersSerialiseTest, List) {
  InSequence dummy0;

  MockSerializeHandler mockHandler;
  Serializer_t serializer( mockHandler );
  ContinerTest < list < float > > obj;

  obj.Array.push_back( 10.01f );
  obj.Array.push_back( 20.02f );
  obj.Array.push_back( 30.03f );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "Array" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "[" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "10.010000" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "20.020000" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "30.030001" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "]" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( ) ).WillOnce( Return( true ) );

  ASSERT_TRUE( serializer.Serialize( obj ) );
}

TEST (STLContainersSerialiseTest, String) {
  InSequence dummy0;

  MockSerializeHandler mockHandler;
  Serializer_t serializer( mockHandler );
  ContinerTest < string > obj;

  obj.Array.assign( "It's work!" );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "Array" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "It's work!" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( ) )
      .WillOnce( Return( true ) );

  ASSERT_TRUE( serializer.Serialize( obj ) );
}

TEST (STLContainersSerialiseTest, Map) {
  InSequence dummy0;

  MockSerializeHandler mockHandler;
  Serializer_t serializer( mockHandler );
  ContinerTest < map < string, uint8_t > > obj;

  obj.Array.insert( make_pair( "A", 1 ) );
  obj.Array.insert( make_pair( "B", 2 ) );
  obj.Array.insert( make_pair( "C", 3 ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "Array" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "[" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "key" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "A" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "value" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "1" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "key" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "B" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "value" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "2" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "key" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "C" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "value" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "3" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "]" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( ) ).WillOnce( Return( true ) );

  ASSERT_TRUE( serializer.Serialize( obj ) );
}

