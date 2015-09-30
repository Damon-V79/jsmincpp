#ifndef TESTS_MOCKSERIALIZEHANDLER_H_
#define TESTS_MOCKSERIALIZEHANDLER_H_

#include <jsmincpp/serialize/JSONSerializer.h>
#include <gmock/gmock.h>

#include <iostream>

class MockSerializeHandler {
public:
  bool operator()( const char *str, uint32_t len ) {
    std::cout << str;
    return handle( str );
  }
  MOCK_METHOD1(handle, bool( const char * ));

  bool SerializeEnd( ) {
    std::cout << std::endl;
    return handle( );
  }
  MOCK_METHOD0(handle, bool( ));
};

typedef jsmincpp::serialize::Serializer <
    jsmincpp::serialize::JSONSerializer < MockSerializeHandler >
> Serializer_t;

#endif /* TESTS_MOCKSERIALIZEHANDLER_H_ */
