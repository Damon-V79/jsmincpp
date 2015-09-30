#ifndef INCLUDE_DESERIALIZE_PARAMS_H_
#define INCLUDE_DESERIALIZE_PARAMS_H_

#include <jsmincpp/deserialize/ParseInt.h>
#include <jsmincpp/deserialize/ParseUInt.h>
#include <jsmincpp/deserialize/ParseBool.h>
#include <jsmincpp/deserialize/ParseFloat.h>

namespace jsmincpp {

namespace deserialize {

template < uint32_t Hash, typename T >
class IntParam {
public:
  enum {
    HASH = Hash
  };

  IntParam( T &param )
      :
          _param( param ) {
  }

  template < typename D >
  bool Parse( D &deserializer ) {
    return ParseInt( _param, deserializer.GetStream( ) );
  }

private:
  T &_param;
};

template < uint32_t Hash, typename T >
class UIntParam {
public:
  enum {
    HASH = Hash
  };

  UIntParam( T &param )
      :
          _param( param ) {
  }

  template < typename D >
  bool Parse( D &deserializer ) {
    return ParseUInt( _param, deserializer.GetStream( ) );
  }

private:
  T &_param;
};

template < uint32_t Hash >
class BoolParam {
public:
  enum {
    HASH = Hash
  };

  BoolParam( bool &param )
      :
          _param( param ) {
  }

  template < typename D >
  bool Parse( D &deserializer ) {
    return ParseBool( _param, deserializer.GetStream( ) );
  }

private:
  bool &_param;
};

template < uint32_t Hash, typename T >
class FloatParam {
public:
  enum {
    HASH = Hash
  };

  FloatParam( T &param )
      :
          _param( param ) {
  }

  template < typename D >
  bool Parse( D &deserializer ) {
    return ParseFloat( _param, deserializer.GetStream( ) );
  }

private:
  T &_param;
};

template < uint32_t Hash, typename T >
class ObjectParam {
public:
  typedef T Object_t;

  enum {
    HASH = Hash
  };

  ObjectParam( T &param )
      :
          _param( param ) {
  }

  template < typename D >
  bool Parse( D &deserializer ) {
    return _param.Deserialize( deserializer );
  }

private:
  T &_param;
};

template < uint32_t Hash >
IntParam < Hash, int8_t > MakeParam( int8_t & );
template < uint32_t Hash >
IntParam < Hash, int16_t > MakeParam( int16_t & );
template < uint32_t Hash >
IntParam < Hash, int32_t > MakeParam( int32_t & );

template < uint32_t Hash >
UIntParam < Hash, uint8_t > MakeParam( uint8_t & );
template < uint32_t Hash >
UIntParam < Hash, uint16_t > MakeParam( uint16_t & );
template < uint32_t Hash >
UIntParam < Hash, uint32_t > MakeParam( uint32_t & );

template < uint32_t Hash >
BoolParam < Hash > MakeParam( bool & );

template < uint32_t Hash >
FloatParam < Hash, float > MakeParam( float & );
template < uint32_t Hash >
FloatParam < Hash, double > MakeParam( double & );

template < uint32_t Hash, typename T >
ObjectParam < Hash, T > MakeParam( T & );


template < uint32_t Hash, typename T, uint32_t Num >
class ArrayParam {
public:
  typedef T Object_t;

  enum {
    HASH = Hash
  };

  ArrayParam( T ( &param )[ Num ] )
      :
          _param( param ) {
  }

  template < typename D >
  bool Parse( D &deserializer ) {
    auto &stream = deserializer.GetStream( );

    if ( '[' != *stream )
      return false;
    ++stream;

    for ( uint32_t i = 0; i < Num - 1; ++i ) {
      auto param = MakeParam< 0 >( _param[ i ] );
      if ( !param.Parse( deserializer ) )
        return false;

      if ( ',' == *stream )
        ++stream;
      else
        return false;
    }

    auto param = MakeParam< 0 >( _param[ Num - 1 ] );
    if ( !param.Parse( deserializer ) )
      return false;

    if ( ']' != *stream )
      return false;
    ++stream;

    return true;
  }

private:
  T ( &_param )[ Num ];
};

template < uint32_t Hash >
IntParam < Hash, int8_t > MakeParam( int8_t &param ) {
  return IntParam < Hash, int8_t >( param );
}

template < uint32_t Hash >
IntParam < Hash, int16_t > MakeParam( int16_t &param ) {
  return IntParam < Hash, int16_t >( param );
}

template < uint32_t Hash >
IntParam < Hash, int32_t > MakeParam( int32_t &param ) {
  return IntParam < Hash, int32_t >( param );
}

template < uint32_t Hash >
UIntParam < Hash, uint8_t > MakeParam( uint8_t &param ) {
  return UIntParam < Hash, uint8_t >( param );
}

template < uint32_t Hash >
UIntParam < Hash, uint16_t > MakeParam( uint16_t &param ) {
  return UIntParam < Hash, uint16_t >( param );
}

template < uint32_t Hash >
UIntParam < Hash, uint32_t > MakeParam( uint32_t &param ) {
  return UIntParam < Hash, uint32_t >( param );
}

template < uint32_t Hash >
BoolParam < Hash > MakeParam( bool &param ) {
  return BoolParam < Hash >( param );
}

template < uint32_t Hash >
FloatParam < Hash, float > MakeParam( float &param ) {
  return FloatParam < Hash, float >( param );
}

template < uint32_t Hash >
FloatParam < Hash, double > MakeParam( double &param ) {
  return FloatParam < Hash, double >( param );
}

template < uint32_t Hash, typename T >
ObjectParam < Hash, T > MakeParam( T &param ) {
  return ObjectParam < Hash, T >( param );
}

template < uint32_t Hash, typename T, uint32_t Num >
ArrayParam < Hash, T, Num > MakeParam( T ( &param )[ Num ] ) {
  return ArrayParam < Hash, T, Num >( param );
}

}          //namespace deserialize

}          // namespace jsmincpp

#endif          // INCLUDE_DESERIALIZE_PARAMS_H_
