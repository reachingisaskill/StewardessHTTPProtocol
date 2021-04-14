
#include "StewardessHTTP.h"

#include <iostream>
#include <cassert>

using namespace HTTP;


int main( int, char** )
{
  {
    TokenDictionary td( '=', '&' );
    std::string test_string = "fdlhbvf=jkb39b4&sjkdflbd=j2398d";

    std::cout << "Decoding:   " << test_string << std::endl;
    td.decode( test_string );

    for ( TokenDictionary::iterator it = td.begin(); it != td.end(); ++it )
    {
      std::cout << it->first << " = " << it->second << std::endl;
    }
    std::cout << "Re-encoded: " << td.encode() << std::endl;
  }


  {
    TokenDictionary td( ',', ';' );
    td.setTrailingDelimeterRequired( true );

    std::string test_string = "fdlhbvf,jkb39b4;sjkdflbd,j2398d";

    std::cout << "Decoding:   " << test_string << std::endl;
    td.decode( test_string );

    for ( TokenDictionary::iterator it = td.begin(); it != td.end(); ++it )
    {
      std::cout << it->first << " = " << it->second << std::endl;
    }
    std::cout << "Re-encoded: " << td.encode() << std::endl;
  }

  {
    TokenDictionary td( '=', ';' );
    td.setTrailingDelimeterRequired( true );

    std::string test_string = "fdlhbvf,jkb39b423sjkdflbd,j2398d";

    std::cout << "Decoding:   " << test_string << std::endl;
    td.decode( test_string );

    for ( TokenDictionary::iterator it = td.begin(); it != td.end(); ++it )
    {
      std::cout << it->first << " = " << it->second << std::endl;
    }
    std::cout << "Re-encoded: " << td.encode() << std::endl;

  }

  return 0;
}
