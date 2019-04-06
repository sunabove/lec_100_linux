#include "calc.nsmap"
#include "soapcalcProxy.h" 

int main( int argc, char ** argv ) {
  struct soap soap ;
  soap_init( & soap );
  soap.proxy_host = "127.0.0.1" ;
  soap.proxy_port = 8080 ; 

  calcProxy calc( & soap );

  float a = 3.0 ;
  float b = 4.0 ;

  if( 1 < argc ) {
    sscanf( argv[1], "%f", & a );
  }

  if( 2 < argc ) {
    sscanf( argv[2], "%f", & b );
  }
   
  double sum;
  if (calc.add( a, b, sum) == SOAP_OK)
    std::cout << "Sum = " << sum << std::endl;
  else
    calc.soap_stream_fault(std::cerr);
  calc.destroy();

  return 0 ;
}
