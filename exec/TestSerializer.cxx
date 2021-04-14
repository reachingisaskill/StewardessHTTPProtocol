
#include "StewardessHTTP.h"

#include <iostream>
#include <cassert>

using namespace HTTP;


int main( int, char** )
{
  {
    Serializer serialSender;
    Serializer serialReceiver;

    std::cout << "Creating test payload" << std::endl;
    Payload* test_payload = new Payload( Payload::Ok, "Hello" );
    test_payload->setHeader( "Host", "www.example.com" );
    test_payload->addSetCookie( "name", "value" );

    std::cout << '\n' << test_payload->print() << '\n' << std::endl;

    std::cout << "Serializing" << std::endl;
    serialSender.serialize( test_payload );

    assert( serialSender.bufferEmpty() == false );
    assert( serialSender.errorEmpty() == true );

    std::cout << "Pop buffer" << std::endl;
    Stewardess::Buffer* temp_buffer = serialSender.getBuffer();

    std::cout << "Raw Buffer : " << temp_buffer->getString() << std::endl;

    std::cout << "Deserializing" << std::endl;
    serialReceiver.deserialize( temp_buffer );

    assert( serialReceiver.payloadEmpty() == false );
    assert( serialReceiver.errorEmpty() == true );

    std::cout << "Recovered payload:" << std::endl;

    Payload* new_payload = (Payload*)serialReceiver.getPayload();
    std::cout << '\n' << new_payload->print() << '\n' << std::endl;

    delete test_payload;
    delete temp_buffer;
    delete new_payload;
  }

  std::cout << "\n----------------------------------------------------------------------------------------------------\n" << std::endl;

  {
    Serializer serialSender;
    Serializer serialReceiver;

    std::cout << "Creating test payload" << std::endl;
    Payload* test_payload = new Payload( Payload::NotImplemented, "Oh balls... \n\n\nShould fix that really..." );
    test_payload->setHeader( "Host", "www.example.com" );

    std::cout << '\n' << test_payload->print() << '\n' << std::endl;

    std::cout << "Serializing" << std::endl;
    serialSender.serialize( test_payload );

    assert( serialSender.bufferEmpty() == false );
    assert( serialSender.errorEmpty() == true );

    std::cout << "Pop buffer" << std::endl;
    Stewardess::Buffer* temp_buffer = serialSender.getBuffer();

    std::cout << "Deserializing" << std::endl;
    serialReceiver.deserialize( temp_buffer );

    assert( serialReceiver.payloadEmpty() == false );
    assert( serialReceiver.errorEmpty() == true );

    std::cout << "Recovered payload:" << std::endl;

    Payload* new_payload = (Payload*)serialReceiver.getPayload();
    std::cout << '\n' << new_payload->print() << '\n' << std::endl;

    delete test_payload;
    delete temp_buffer;
    delete new_payload;
  }

  return 0;
}


