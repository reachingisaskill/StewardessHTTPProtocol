
#ifndef HTTP_PROTOCOL_LIBRARY_TEST_H_
#define HTTP_PROTOCOL_LIBRARY_TEST_H_

#include "Stewardess.h"
#include "StewardessHTTP.h"


namespace HTTP
{

  namespace Test
  {
    class TestServer : public Stewardess::CallbackInterface
    {
      private:

      public:
        // Return a new'd serializer object to implement the transfer protocol
        virtual Stewardess::Serializer* buildSerializer() const override { return new Serializer(); }


        // Called when a read event is triggered.
        virtual void onRead( Stewardess::Handle, Stewardess::Payload* ) override;


        // Called when a write event is triggered.
        virtual void onWrite( Stewardess::Handle ) override;


        // Called when a connection event occurs
        virtual void onConnectionEvent( Stewardess::Handle, Stewardess::ConnectionEvent, const char* ) override;


        // Called every server 'tick' with the elapsed time
        virtual void onTick( Stewardess::Milliseconds ) override;
    };
  }
}

#endif // HTTP_PROTOCOL_LIBRARY_TEST_H_

