#undef GTEST_LANG_CXX11

#include "SymbolStream.h"

#include <jsmincpp/deserialize/ParseFloat.h>

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

TEST (ParseFloatTest, test1) {
  const char *str = "10.01,\"First\":";
  SymbolStream s( str );
  float data = 0.0f;

  ASSERT_TRUE( ParseFloat( data, s ) );
  ASSERT_FLOAT_EQ( data, 10.01 );
  ASSERT_EQ( *s, ',' );
}

TEST (ParseFloatTest, test2) {
  const char *str = "-20.02,";
  SymbolStream s( str );
  float data = 0.0f;

  ASSERT_TRUE( ParseFloat( data, s ) );
  ASSERT_FLOAT_EQ( data, -20.02 );
  ASSERT_EQ( *s, ',' );
}
