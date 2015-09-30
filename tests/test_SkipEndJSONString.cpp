#undef GTEST_LANG_CXX11

#include "SymbolStream.h"

#include <jsmincpp/deserialize/SkipEndJSONString.h>

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

TEST (SkipEndJSONStringTest, test1) {
  const char *json =
      "-20.02,\"Fourth\":false}!";
  SymbolStream s( json );

  SkipEndJSONString( s );

  ASSERT_EQ( *s, '!' );
}

TEST (SkipEndJSONStringTest, test2) {
  const char *json =
      "ond\":true,\"Include\":{\"Third\":-20.02,\"Fourth\":false}}!";
  SymbolStream s( json );

  SkipEndJSONString( s );

  ASSERT_EQ( *s, '!' );
}

TEST (SkipEndJSONStringTest, test3) {
  const char *json =
      ":{\"Object\":{\"First\":20.01,\"Second\":true,\"Include\":{\"Third\":-20.02,\"Fourth\":false}}}}!";
  SymbolStream s( json );

  SkipEndJSONString( s );

  ASSERT_EQ( *s, '!' );
}

