#undef GTEST_LANG_CXX11

#include "SymbolStream.h"

#include <jsmincpp/deserialize/Deserializer.h>
#include <jsmincpp/deserialize/MallocCreator.h>
#include <jsmincpp/deserialize/STLSupport/SharedPrtCreator.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>

using namespace std;
using namespace jsmincpp::deserialize;
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

struct NullObject {
  template < typename D >
  bool Deserialize( D &deserializer ) {
    return deserializer( );
  }
};

struct NullObjectHandler {
  bool _recvData;

  NullObjectHandler( )
      :
          _recvData( false ) {
  }

  bool operator()( NullObject *param ) {
    _recvData = true;
//    cout << "Receive \"Object\"" << endl;
    return true;
  }
};

struct Include_t {
  float Third;
  bool Fourth;

  Include_t( )
      :
          Third( 10.01 ),
          Fourth( true ) {
  }

  template < typename D >
  bool Deserialize( D &deserializer ) {
    return deserializer(
        DESERIALIZE( Third ),
        DESERIALIZE( Fourth )
            );
  }
};

struct Object {
  float First;
  bool Second;
  Include_t Include;

  Object( )
      :
          First( 0.01 ),
          Second( false ) {
  }

  template < typename D >
  bool Deserialize( D &deserializer ) {
    return deserializer(
        DESERIALIZE( First ),
        DESERIALIZE( Second ),
        DESERIALIZE( Include )
            );
  }
};

struct OtherObject {
  float One [ 5 ];
  bool Two [ 5 ];

  OtherObject( )
      :
          One { 110.01e-5f, 110.01e5f, 110.01e-5f, 110.01e5f, 110.01e-5f },
          Two { true, false, true, false, true } {
  }

  template < typename D >
  bool Deserialize( D &deserializer ) {
    return deserializer(
        DESERIALIZE( One ),
        DESERIALIZE( Two )
            );
  }
};

struct Handler {
  bool m_recvData1;
  bool m_recvData2;
  Object &p_obj1;
  OtherObject &p_obj2;

  Handler( Object &obj1, OtherObject &obj2 )
      :
          m_recvData1( false ),
          m_recvData2( false ),
          p_obj1( obj1 ),
          p_obj2( obj2 ) {
  }

  bool operator()( Object *param ) {
    m_recvData1 = true;
    p_obj1 = *param;
//    cout << "Receive \"Object\"" << endl;
    return true;
  }

  bool operator()( OtherObject *param ) {
    m_recvData2 = true;
    p_obj2 = *param;
//    cout << "Receive \"OtherObject\"" << endl;
    return true;
  }
};

struct SharedPrtHandler {
  bool m_recvData1;
  bool m_recvData2;
  Object &p_obj1;
  OtherObject &p_obj2;

  SharedPrtHandler( Object &obj1, OtherObject &obj2 )
      :
          m_recvData1( false ),
          m_recvData2( false ),
          p_obj1( obj1 ),
          p_obj2( obj2 ) {
  }

  bool operator()( shared_ptr < Object > param ) {
    m_recvData1 = true;
    p_obj1 = *param;
//    cout << "Receive \"Object\"" << endl;
    return true;
  }

  bool operator()( shared_ptr < OtherObject > param ) {
    m_recvData2 = true;
    p_obj2 = *param;
//    cout << "Receive \"OtherObject\"" << endl;
    return true;
  }
};

int32_t MallocCreator::m_allocateCounter = 0;

TEST (JSONParserTest, NullObject) {
  const char *json =
      "{\"NullObject\":null}";
  SymbolStream s( json );

  NullObjectHandler h;

  typedef ObjectsList <
  DESERIALIZEOBJ( NullObject )
  > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t
  > d( s );

  // Deserialization message
  ASSERT_TRUE( d.Deserialize( h ) );
  ASSERT_TRUE( h._recvData );
}

TEST (JSONParserTest, StaticAllocateMemmory) {
  const char *json =
      // First message
      "{\"Object\":{\"First\":20.01,\"Second\":true,\"Include\":{\"Third\":-20.02,\"Fourth\":false}}}"
      // Second message
          "{\"OtherObject\":{\"One\":[1.0e10,2.0e10,3.0e10,4.0e10,5.0e10],\"Two\":[false,true,false,true,false]}}";
  SymbolStream s( json );

  Object obj1;
  OtherObject obj2;
  Handler h( obj1, obj2 );

  typedef ObjectsList <
  DESERIALIZEOBJ( Object ),
  DESERIALIZEOBJ( OtherObject )
  > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t
  > d( s );

  // Deserialization first message
  ASSERT_TRUE( d.Deserialize( h ) );

  ASSERT_TRUE( h.m_recvData1 );
  ASSERT_FALSE( h.m_recvData2 );

  ASSERT_FLOAT_EQ( h.p_obj1.First, 20.01 );
  ASSERT_TRUE( h.p_obj1.Second );
  ASSERT_FLOAT_EQ( h.p_obj1.Include.Third, -20.02 );
  ASSERT_FALSE( h.p_obj1.Include.Fourth );

  // Deserialization second message
  ASSERT_TRUE( d.Deserialize( h ) );

  ASSERT_TRUE( h.m_recvData1 );
  ASSERT_TRUE( h.m_recvData2 );

  float checkOne [ ] = { 1.0e10f, 2.0e10f, 3.0e10f, 4.0e10f, 5.0e10f };
  bool checkTwo [ ] = { false, true, false, true, false };
  ASSERT_THAT( h.p_obj2.One, ContainerEq( checkOne ) );
  ASSERT_THAT( h.p_obj2.Two, ContainerEq( checkTwo ) );
}

TEST (JSONParserTest, DynamicAllocateMemmory) {
  const char *json =
      // First message
      "{\"Object\":{\"First\":20.01,\"Second\":true,\"Include\":{\"Third\":-20.02,\"Fourth\":false}}}"
      // Second message
          "{\"OtherObject\":{\"One\":[1.0e10,2.0e10,3.0e10,4.0e10,5.0e10],\"Two\":[false,true,false,true,false]}}";
  SymbolStream s( json );

  Object obj1;
  OtherObject obj2;
  SharedPrtHandler h( obj1, obj2 );

  typedef ObjectsList <
  DESERIALIZEOBJ( Object ),
  DESERIALIZEOBJ( OtherObject )
  > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t,
      SharedPrtCreator
  > d( s );

  // Deserialization first message
  ASSERT_TRUE( d.Deserialize( h ) );

  ASSERT_TRUE( h.m_recvData1 );
  ASSERT_FALSE( h.m_recvData2 );

  ASSERT_FLOAT_EQ( h.p_obj1.First, 20.01 );
  ASSERT_TRUE( h.p_obj1.Second );
  ASSERT_FLOAT_EQ( h.p_obj1.Include.Third, -20.02 );
  ASSERT_FALSE( h.p_obj1.Include.Fourth );

  // Deserialization second message
  ASSERT_TRUE( d.Deserialize( h ) );

  ASSERT_TRUE( h.m_recvData1 );
  ASSERT_TRUE( h.m_recvData2 );

  float checkOne [ ] = { 1.0e10f, 2.0e10f, 3.0e10f, 4.0e10f, 5.0e10f };
  bool checkTwo [ ] = { false, true, false, true, false };
  ASSERT_THAT( h.p_obj2.One, ContainerEq( checkOne ) );
  ASSERT_THAT( h.p_obj2.Two, ContainerEq( checkTwo ) );
}

TEST (JSONParserTest, DeserializeToStaticObject) {
  const char *json =
      "{\"Second\":true,\"First\":20.01,\"Include\":{\"Third\":-20.02,\"Fourth\":false}}";
  SymbolStream s( json );

  typedef ObjectsList <
  DESERIALIZEOBJ(NullObj)
      > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t
  > d( s );

  Object obj;
  ASSERT_TRUE( d.Deserialize( &obj ) );

  ASSERT_FLOAT_EQ( obj.First, 20.01 );
  ASSERT_TRUE( obj.Second );
  ASSERT_FLOAT_EQ( obj.Include.Third, -20.02 );
  ASSERT_FALSE( obj.Include.Fourth );
}

TEST (JSONParserTest, DeserializeToDynamicObject) {
  const char *json =
      "{\"Second\":true,\"First\":20.01,\"Include\":{\"Third\":-20.02,\"Fourth\":false}}";
  SymbolStream s( json );

  typedef ObjectsList <
  DESERIALIZEOBJ(NullObj)
      > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t
  > d( s );

  auto obj = make_shared < Object >( );

  ASSERT_TRUE( d.Deserialize( obj.get( ) ) );

  ASSERT_FLOAT_EQ( obj->First, 20.01 );
  ASSERT_TRUE( obj->Second );
  ASSERT_FLOAT_EQ( obj->Include.Third, -20.02 );
  ASSERT_FALSE( obj->Include.Fourth );
}

TEST (JSONParserTest, ErrorHandlingTest1) {
  const char *json =
      "{\"Object\":{\"First\":20.01,\"Second\";true,\"Include\":{\"Third\":-20.02,\"Fourth\":false}}}!";
  //                                          ^ -- error symbol.
  SymbolStream s( json );

  Object obj1;
  OtherObject obj2;
  Handler h( obj1, obj2 );

  typedef ObjectsList <
  DESERIALIZEOBJ( Object ),
  DESERIALIZEOBJ( OtherObject )
  > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t,
      MallocCreator
  > d( s );

  ASSERT_FALSE( d.Deserialize( h ) );
  ASSERT_FALSE( h.m_recvData1 );
  ASSERT_FALSE( h.m_recvData2 );
  ASSERT_EQ( MallocCreator::m_allocateCounter, 0 );
  ASSERT_EQ( *s, '!' );
}

TEST (JSONParserTest, ErrorHandlingTest2) {
  const char *json =
      "{\"Object\":{\"First\":true,\"Second\":20.01,\"Include\":{\"Third\":-20.02,\"Fourth\":false}}}!";
  //                           ^ ------------- ^ -- error parameters type.
  SymbolStream s( json );

  Object obj1;
  OtherObject obj2;
  Handler h( obj1, obj2 );

  typedef ObjectsList <
  DESERIALIZEOBJ( Object ),
  DESERIALIZEOBJ( OtherObject )
  > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t,
      MallocCreator
  > d( s );

  ASSERT_FALSE( d.Deserialize( h ) );
  ASSERT_FALSE( h.m_recvData1 );
  ASSERT_FALSE( h.m_recvData2 );
  ASSERT_EQ( MallocCreator::m_allocateCounter, 0 );
  ASSERT_EQ( *s, '!' );
}

TEST (JSONParserTest, ErrorHandlingTest3) {
  const char *json =
      "{\"Object\":{\"First\":20.01,\"Second\":true,\"Include\":{\"Third\":-20.02,\"Fourth\":\"red\"}}}!";
  //                                                                   error parameter type. -- ^
  SymbolStream s( json );

  Object obj1;
  OtherObject obj2;
  Handler h( obj1, obj2 );

  typedef ObjectsList <
  DESERIALIZEOBJ( Object ),
  DESERIALIZEOBJ( OtherObject )
  > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t,
      MallocCreator
  > d( s );

  ASSERT_FALSE( d.Deserialize( h ) );
  ASSERT_FALSE( h.m_recvData1 );
  ASSERT_FALSE( h.m_recvData2 );
  ASSERT_EQ( MallocCreator::m_allocateCounter, 0 );
  ASSERT_EQ( *s, '!' );
}

TEST (JSONParserTest, ErrorHandlingTest4) {
  const char *json =
      // Bad message
      "{\"Object\":{\"First\":20.01,\"Second\":true,\"Include\":{\"Third\":-20.02,\"Four\":\"red";
  SymbolStream s( json );

  Object obj1;
  OtherObject obj2;
  Handler h( obj1, obj2 );

  typedef ObjectsList <
  DESERIALIZEOBJ( Object ),
  DESERIALIZEOBJ( OtherObject )
  > SerializeList_t;

  Deserializer <
      SymbolStream,
      SerializeList_t,
      MallocCreator
  > d( s );

  ASSERT_FALSE( d.Deserialize( h ) );
  ASSERT_FALSE( h.m_recvData1 );
  ASSERT_FALSE( h.m_recvData2 );
  ASSERT_EQ( MallocCreator::m_allocateCounter, 0 );
}
