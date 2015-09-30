#undef GTEST_LANG_CXX11

#include "SymbolStream.h"

#include <jsmincpp/deserialize/CRC32Hash.h>
#include <jsmincpp/deserialize/GetNameHash.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace jsmincpp::deserialize;
using ::testing::ElementsAreArray;
using ::testing::ElementsAre;
using ::testing::InSequence;
using ::testing::TypedEq;
using ::testing::StrEq;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;
using ::testing::An;

TEST (GetNameHashTest, test1) {
  const char *name = "\"Object\":{\"First\":";
  SymbolStream s( name );
  CRC32Hash h;

  ASSERT_TRUE( GetNameHash( s, h ) );
  ASSERT_EQ( Crc32( "Object" ), h.operator unsigned int( ) );
}

TEST (GetNameHashTest, test2) {
  const char *name = "\"First\":20.01,\"Second\"";
  SymbolStream s( name );
  CRC32Hash h;

  ASSERT_TRUE( GetNameHash( s, h ) );
  ASSERT_EQ( Crc32( "First" ), h.operator unsigned int( ) );
}

TEST (GetNameHashTest, test3) {
  const char *name = "Object\":{";
  SymbolStream s( name );
  CRC32Hash h;

  ASSERT_FALSE( GetNameHash( s, h ) );
}

TEST (GetNameHashTest, test4) {
  const char *name = "\"Fi-rst\":20.01,\"Second\"";
  SymbolStream s( name );
  CRC32Hash h;

  ASSERT_FALSE( GetNameHash( s, h ) );
}
