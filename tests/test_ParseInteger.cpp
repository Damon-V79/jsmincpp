#undef GTEST_LANG_CXX11

#include "SymbolStream.h"

#include <jsmincpp/deserialize/ParseInt.h>
#include <jsmincpp/deserialize/ParseUInt.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>
#include <vector>
#include <string>

using namespace jsmincpp::deserialize;
using namespace std;
using ::testing::ElementsAreArray;
using ::testing::ElementsAre;
using ::testing::InSequence;
using ::testing::TypedEq;
using ::testing::StrEq;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;
using ::testing::An;

TEST (ParseIntegerTest, int8) {
  const char *str = "127,-128,";
  SymbolStream s( str );
  int8_t data = 0;

  ASSERT_TRUE( ParseInt( data, s ) );
  ASSERT_EQ( data, 127 );
  ASSERT_EQ( *s, ',' );

  ++s;
  data = 0;
  ASSERT_TRUE( ParseInt( data, s ) );
  ASSERT_EQ( data, -128 );
  ASSERT_EQ( *s, ',' );
}

TEST (ParseIntegerTest, int8_positive_overflow) {
  const char *str = "128,\"value\":";
  SymbolStream s( str );
  int8_t data = 0;

  ASSERT_FALSE( ParseInt( data, s ) );
}

TEST (ParseIntegerTest, int8_negative_overflow) {
  const char *str = "-129,\"value\":";
  SymbolStream s( str );
  int8_t data = 0;

  ASSERT_FALSE( ParseInt( data, s ) );
}

TEST (ParseIntegerTest, int32) {
  const char *str = "2147483647,-2147483648,";
  SymbolStream s( str );
  int32_t data = 0;

  ASSERT_TRUE( ParseInt( data, s ) );
  ASSERT_EQ( data, 2147483647 );
  ASSERT_EQ( *s, ',' );

  ++s;
  data = 0;
  ASSERT_TRUE( ParseInt( data, s ) );
  ASSERT_EQ( data, -2147483648 );
  ASSERT_EQ( *s, ',' );
}

TEST (ParseIntegerTest, int32_positive_overflow) {
  const char *str = "2147483648,\"value\":";
  SymbolStream s( str );
  int32_t data = 0;

  ASSERT_FALSE( ParseInt( data, s ) );
}

TEST (ParseIntegerTest, int32_negative_overflow) {
  const char *str = "-2147483649,\"value\":";
  SymbolStream s( str );
  int32_t data = 0;

  ASSERT_FALSE( ParseInt( data, s ) );
}

TEST (ParseIntegerTest, uint8) {
  const char *str = "255,\"value\":";
  SymbolStream s( str );
  uint8_t data = 0;

  ASSERT_TRUE( ParseInt( data, s ) );
  ASSERT_EQ( data, 255 );
  ASSERT_EQ( *s, ',' );
}

TEST (ParseIntegerTest, uint8_overflow) {
  const char *str = "256,\"value\":";
  SymbolStream s( str );
  uint8_t data = 0;

  ASSERT_FALSE( ParseInt( data, s ) );
}

TEST (ParseIntegerTest, uint32) {
  const char *str = "4294967295,\"value\":";
  SymbolStream s( str );
  uint32_t data = 0;

  ASSERT_TRUE( ParseInt( data, s ) );
  ASSERT_EQ( data, 4294967295U );
  ASSERT_EQ( *s, ',' );
}

TEST (ParseIntegerTest, uint32_overflow) {
  const char *str = "4294967296,\"value\":";
  SymbolStream s( str );
  uint32_t data = 0;

  ASSERT_FALSE( ParseInt( data, s ) );
}

