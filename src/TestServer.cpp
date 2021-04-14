
#include "TestServer.h"

using Stewardess::Handle;
using Stewardess::ConnectionEvent;
using Stewardess::Milliseconds;


namespace HTTP
{
  namespace Test
  {

    namespace
    {
      const std::string HTMLHello = "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<title>Hello World</title>\n</head>\n<body>Hello World</body>\n</html>";
    }


    void TestServer::onRead( Handle handle, Stewardess::Payload* p )
    {
      Payload* payload = (Payload*)p;
      std::cout << "RECEIVED: From connection: " << handle.getConnectionID() << '\n' << payload->print() << std::endl;

      std::cout << "COOKIE = " << payload->getCookie( "hello" ) << std::endl;
      Payload response( Payload::Ok, HTMLHello );
      if ( payload->getCookie( "hello" ).size() == 0 )
      {
        response.addSetCookie( "hello", "world" );
      }
      std::cout << "RESPONSE: " << '\n' << response.print() << std::endl;
      handle.write( &response );
      delete p;
    }


    void TestServer::onWrite( Handle handle )
    {
      std::cout << "Write complete. Closing connection: " << handle.getConnectionID() << std::endl;
      handle.close();
    }


    void TestServer::onConnectionEvent( Handle /*handle*/, ConnectionEvent event, const char* error )
    {
      switch( event )
      {
        case ConnectionEvent::Connect :
        {
          std::cout << "Connection Event" << std::endl;
        }
        break;

        case ConnectionEvent::Disconnect :
        {
          std::cout << "Disconnection Event" << std::endl;
        }
        break;

        case ConnectionEvent::DisconnectError :
        {
          std::cout << "Unexpected Disconnection Event: " << error << std::endl;
        }
        break;

        default:
        break;
      }
    }


    void TestServer::onTick( Milliseconds /*time*/ )
    {
      std::cout << std::endl;
    }

  }

}

