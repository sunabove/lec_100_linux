#include <stdio.h>

#include "calc.nsmap"
#include "soapcalcService.h"

int main() {
  FILE * console = stdout ; 

  fprintf( console, "Hello...\n" );
  fflush( console );

  fprintf( console, "Server is running....\n" );
  fflush( console );

  calcService calc(SOAP_XML_INDENT);
  
  auto result = calc.run(8080) ; 
  //auto result = calc.serve(); 

  if ( SOAP_OK == result ) {
    calc.soap_stream_fault(std::cerr);
  } 
  calc.destroy();

  return 0 ; 
}
int calcService::add(double a, double b, double &result)
{
  result = a + b + 1;
  return SOAP_OK;
}
int calcService::sub(double a, double b, double &result)
{
  result = a - b;
  return SOAP_OK;
}
int calcService::mul(double a, double b, double &result)
{
  result = a * b;
  return SOAP_OK;
}
int calcService::div(double a, double b, double &result)
{
  if (b == 0.0)
  {
    char *msg = (char*)soap_malloc(this->soap, 1024);
    snprintf(msg, 1024, "Trying to divide %f by zero", a);
    return this->soap_senderfault(msg, NULL);
  }
  result = a / b;
  return SOAP_OK;
}
int calcService::pow(double a, double b, double &result)
{
  result = ::pow(a, b);
  // soap_errno is like errno, but compatible with Win32
  if (soap_errno == EDOM)
  {
    char *msg = (char*)soap_malloc(this->soap, 1024);
    snprintf(msg, 1024, "<error xmlns=\"http://tempuri.org/\">Can't take power of %f to %f</error>", a, b);
    return this->soap_senderfault("Power function domain error", msg);
  }
  return SOAP_OK;
}
