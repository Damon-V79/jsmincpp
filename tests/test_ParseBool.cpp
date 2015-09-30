#undef GTEST_LANG_CXX11

#include "SymbolStream.h"

#include <jsmincpp/deserialize/ParseBool.h>

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

TEST (ParseBoolTest, test1) {
  const char *str = "true,\"value\":";
  SymbolStream s( str );
  bool data = false;

  ASSERT_TRUE( ParseBool( data, s ) );
  ASSERT_TRUE( data );
  ASSERT_EQ( *s, ',' );
}

TEST (ParseBoolTest, test2) {
  const char *str = "true],\"Second\":";
  SymbolStream s( str );
  bool data = false;

  ASSERT_TRUE( ParseBool( data, s ) );
  ASSERT_TRUE( data );
  ASSERT_EQ( *s, ']' );
}

TEST (ParseBoolTest, test3) {
  const char *str = "true}";
  SymbolStream s( str );
  bool data = false;

  ASSERT_TRUE( ParseBool( data, s ) );
  ASSERT_TRUE( data );
  ASSERT_EQ( *s, '}' );
}
