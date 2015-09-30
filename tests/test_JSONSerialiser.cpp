#undef GTEST_LANG_CXX11

#include "MockSerializeHandler.h"

#include <jsmincpp/FloatPoint_3x1.h>
#include <jsmincpp/serialize/JSONSerializer.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace jsmincpp;
using namespace jsmincpp::serialize;
using ::testing::ElementsAreArray;
using ::testing::ElementsAre;
using ::testing::InSequence;
using ::testing::TypedEq;
using ::testing::StrEq;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;
using ::testing::An;

class InsertedObj : public Serialized {
public:
  InsertedObj( )
      :
          oneItem( false ),
          secondItem( 200.002 ) {
  }
  InsertedObj( bool one, float two )
      :
          oneItem( one ),
          secondItem( two ) {
  }

  template < typename S >
  bool Serialize( S &serializer ) const {
    SERIALIZE( oneItem );
    SERIALIZE( secondItem );
    return true;
  }

private:
  bool oneItem;
  float secondItem;
};

class SerializeObj : public AbstractSerialized < Serializer_t > {
public:
  SerializeObj( )
      :
          firstParam( true ),
          secondParam( 100.001f ),
          thirdParam {
              0.123,
              123.012,
              0.000,
              359.012,
              100.000,
              0.000 },
          fourthParam {
              true,
              true,
              false,
              true,
              true,
              false
          },
          sixthParam {
              InsertedObj( true, 111.001 ),
              InsertedObj( false, 222.002 ),
              InsertedObj( true, 333.003 )
          },
          seventhParam {
              FloatPoint_3x1( 111.000 ),
              FloatPoint_3x1( 222.002 ),
              FloatPoint_3x1( 333.103 ),
              FloatPoint_3x1( 444.204 ),
              FloatPoint_3x1( 555.305 ),
              FloatPoint_3x1( 666.406 )
          } {

  }

  virtual bool Serialize( Serializer_t &serializer ) const override {
    SERIALIZE( firstParam );
    SERIALIZE( secondParam );
    SERIALIZE( thirdParam );
    SERIALIZE( fourthParam );
    SERIALIZE( fifthParam );
    SERIALIZE( sixthParam );
    SERIALIZE( seventhParam );
    return true;
  }

private:
  bool firstParam;
  float secondParam;
  float thirdParam [ 6 ];
  bool fourthParam [ 6 ];
  InsertedObj fifthParam;
  InsertedObj sixthParam [ 3 ];
  FloatPoint_3x1 seventhParam [ 6 ];

};

TEST (JSONSerializerTest, StaticObject) {

  InSequence dummy0;

  /*
   * var obj =
   * {
   *   firstParam  : true,
   *   secondParam : 100.001,
   *   thirdParam : [
   *     0.123,
   *     123.012,
   *     0.000,
   *     359.012,
   *     100.000,
   *     0.000
   *   ],
   *   fourthParam : [
   *     true,
   *     true,
   *     false,
   *     true,
   *     true,
   *     false
   *   ],
   *   fifthParam : {
   *      oneItem : false,
   *      secondItem : 200.002
   *   },
   *   sixthParam : [
   *     {
   *       oneItem : true,
   *       secondItem : 111.000999
   *     },
   *     {
   *       oneItem : false,
   *       secondItem : 222.001999
   *     },
   *     {
   *       oneItem : true,
   *       secondItem : 333.002991
   *     }
   *   ],
   *   seventhParam : [
   *     111.0,
   *     222.0,
   *     333.1,
   *     444.2,
   *     555.3,
   *     666.4
   *   ]
   * }
   */

  MockSerializeHandler mockHandler;
  Serializer_t serializer( mockHandler );
  SerializeObj obj;

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "firstParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "secondParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "100.000999" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "thirdParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "[" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "0.123000" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "123.012001" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "0.000000" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "359.011993" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "100.000000" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "0.000000" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "]" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "fourthParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "[" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "false" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "false" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "]" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "fifthParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "oneItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "false" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "secondItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "200.001999" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "sixthParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "[" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "oneItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "secondItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "111.000999" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "oneItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "false" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "secondItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "222.001999" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "oneItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "secondItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "333.002991" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "]" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "seventhParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "[" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "111.0" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "222.0" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "333.1" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "444.2" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "555.3" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "666.4" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "]" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( ) ).WillOnce( Return( true ) );

  ASSERT_TRUE( serializer.Serialize( obj ) );
}

TEST (JSONSerializerTest, DynamicObject) {

  InSequence dummy0;

  MockSerializeHandler mockHandler;
  Serializer_t serializer( mockHandler );
  SerializeObj obj;

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "firstParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "secondParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "100.000999" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "thirdParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "[" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "0.123000" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "123.012001" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "0.000000" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "359.011993" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "100.000000" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "0.000000" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "]" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "fourthParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "[" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "false" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "false" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "]" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "fifthParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "oneItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "false" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "secondItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "200.001999" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "sixthParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "[" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "oneItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "secondItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "111.000999" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "oneItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "false" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "secondItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "222.001999" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "oneItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "secondItem" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "333.002991" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "]" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "seventhParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "[" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "111.0" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "222.0" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "333.1" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "444.2" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "555.3" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "666.4" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "]" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "}" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( ) ).WillOnce( Return( true ) );

  ASSERT_TRUE( serializer.Serialize(
      static_cast < AbstractSerialized < Serializer_t > * >( &obj ) ) );
}

TEST (JSONSerializerTest, ErrorHandlingTest) {

  InSequence dummy0;

  MockSerializeHandler mockHandler;
  Serializer_t serializer( mockHandler );
  SerializeObj obj;

  EXPECT_CALL( mockHandler, handle( StrEq( "{" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "\"" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "firstParam" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "\":" ) ) )
      .WillOnce( Return( true ) );
  EXPECT_CALL( mockHandler, handle( StrEq( "true" ) ) )
      .WillOnce( Return( true ) );

  EXPECT_CALL( mockHandler, handle( StrEq( "," ) ) )
      .WillOnce( Return( false ) );

  ASSERT_FALSE( serializer.Serialize( obj ) );

  cout << endl;
}
