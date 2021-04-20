
#ifndef HTTP_PROTOCOL_LIBRARY_H_
#define HTTP_PROTOCOL_LIBRARY_H_

#include "Stewardess.h"


namespace HTTP
{

////////////////////////////////////////////////////////////////////////////////
  // Forward declarations
  class Payload;


////////////////////////////////////////////////////////////////////////////////
  // Tokeninzing class

  class TokenDictionary
  {
    private:
      typedef std::map< std::string, std::string > TokenMap;

    public:
      typedef TokenMap::iterator iterator;
      typedef TokenMap::const_iterator const_iterator;

    private:
      // The delimeters
      const char _delimKey;
      const char _delimValue;

      // Flag to omit trailing delimeter
      bool _flagTrailingDelimeterRequired;

      // The map of keys and values
      TokenMap _dictionary;


    public:
      // Specify the delimiters to construct
      TokenDictionary( char, char );

      void setTrailingDelimeterRequired( bool v ) { _flagTrailingDelimeterRequired = v; }

      // Build dictionary from string
      void decode( const std::string& );

      // Build dictionary from string between the suppled iterators
      void decode( std::string::const_iterator&, std::string::const_iterator );

      // Build a string from the dictionary
      std::string encode() const;

      // Set a value for a dictionary item
      void setValue( std::string, std::string );

      // Return a value for a specific key
      std::string getValue( std::string ) const;

      // Return true if the key exists
      bool getExists( std::string ) const;

      // Clear the dictionary
      void clear() { _dictionary.clear(); }
      
      // Return the number of elements
      size_t size() const { return _dictionary.size(); }

      // Simple iterator interface
      iterator begin() { return _dictionary.begin(); }
      const_iterator begin() const { return _dictionary.begin(); }
      iterator end() { return _dictionary.end(); }
      const_iterator end() const { return _dictionary.end(); }
  };


////////////////////////////////////////////////////////////////////////////////
  // HTTP request object
  class Request
  {
    private:
      typedef std::map< std::string, std::string > QueryMap;
    public:
      typedef QueryMap::iterator QueryIterator;

    private:
      std::string _path;
      std::string _fragment;
      QueryMap _query;
      
    public:
      Request();
      Request( std::string );

      const std::string& getPath() const { return _path; }
      const std::string& getFragment() const { return _fragment; }
      std::string getQuery( std::string ) const;
      size_t size() const { return _query.size(); }


      void decode( std::string );

      std::string encode() const;

      friend std::istream& operator>>( std::istream&, Request& );
      friend std::ostream& operator<<( std::ostream&, const Request& );
  };


  std::istream& operator>>( std::istream&, Request& );
  std::ostream& operator<<( std::ostream&, const Request& );


////////////////////////////////////////////////////////////////////////////////
  // Serialization functions
  class Serializer : public Stewardess::Serializer
  {
    private:

    public:
      // Basic con/destructors
      Serializer() {}
      virtual ~Serializer() {}


      // Serialize a payload
      virtual void serialize( const Stewardess::Payload* ) override;

      // Turn a character buffer into payload
      virtual void deserialize( const Stewardess::Buffer* ) override;

  };


////////////////////////////////////////////////////////////////////////////////
  // The complete payload
  class Payload : public Stewardess::Payload
  {
    friend class Serializer;
    typedef std::map<std::string, std::string> HeaderData;

    public:

      enum MethodType { Response, Get, Head, Post, Put, Delete, Trace, Options, Connect, Patch };

      enum ResponseType
      {
        Null = 0,
        Ok = 200,
        Created = 201,
        Accepted = 202,
        BadRequest = 400,
        Unauthorized = 401,
        PaymentRequired = 402,
        Forbidden = 403,
        NotFound = 404,
        MethodNotAllowed = 405,
        InternalServerError = 500,
        NotImplemented = 501,
        BadGateway = 502,
        ServiceUnavailable = 503,
        GatewayTimeout = 504,
        HTTPVersionNotSupported = 505
      };

    private:
      // Enumeration of the method
      MethodType _method;

      // The request string if it is a request
      Request _request;

      // The version string
      std::string _version;

      // The type of the response if it is a response
      ResponseType _response;

      // The header data
      HeaderData _header;

      // Store the cookie separately
      TokenDictionary _cookie;

      // Store the cookie separately
      TokenDictionary _setCookie;

      // If true, load the body data from the file
      bool _isFile;

      // The body data
      std::string _body;


    public:
      // Empty constructor - defaults to a null response
      Payload();

      // Simple response constructor
      Payload( ResponseType, std::string = "" );


      // Set the flag to indicate it is a file type payload
      void setFile( bool f ) { _isFile = f; }


      // Set a key-value pair in the header replacing one if it already exists
      void setHeader( std::string, std::string );

      // Adds a key-value pair in the header, appending values if it alredy exists
      void addHeader( std::string, std::string );

      // Adds a cookie name and value to the Set-Cookie header
      void addSetCookie( std::string, std::string );


      // Return the method of payload
      MethodType getMethod() const { return _method; }

      // Return a reference to the request string
      const Request& getRequest() const { return _request; }

      // Return a requested header value. Returns an empty string if it doesn't exist
      std::string getHeader( std::string ) const;

      // Return a cookie value from the Cookie header
      std::string getCookie( std::string ) const;


      // Set a new body string
      void setBody( const std::string& b ) { _body = b; }

      // Return the literal body contents
      const std::string& getBody() const { return _body; }

      // For debugging
      std::string print() const;

  };

}

#endif // HTTP_PROTOCOL_LIBRARY_H_

