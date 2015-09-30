#ifndef TESTS_SYMBOLSTREAM_H_
#define TESTS_SYMBOLSTREAM_H_

#include <string.h>
#include <iostream>

class SymbolStream {
public:
  SymbolStream( const char *str )
      :
          m_eof( false ),
          m_counter( 0 ),
          p_str( str ),
          m_len( ::strlen( p_str ) ) {
  }

  SymbolStream End( ) {
    SymbolStream end( nullptr );
    end.m_eof = true;
    return end;
  }

  char operator*( ) {
    char sym = p_str [ m_counter ];
//    std::cout
//        << "Pos: " << m_counter << ", MaxPos: "
//        << m_len - 1 << ", Get symbol: " << sym << std::endl;
    return sym;
  }

  SymbolStream & operator++( ) {
    if ( m_counter++ == m_len - 1 )
      m_eof = true;
    return *this;
  }

  bool operator==( const SymbolStream &other ) {
    bool res = m_eof == other.m_eof;
    return res;
  }

private:
  bool m_eof;
  uint32_t m_counter;
  const char *p_str;
  uint32_t m_len;

};

#endif /* TESTS_SYMBOLSTREAM_H_ */
