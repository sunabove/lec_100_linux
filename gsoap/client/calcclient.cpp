#include "calc.nsmap"
#include "soapcalcProxy.h" 

int main()
{
  calcProxy calc;
  double sum;
  if (calc.add(1.23, 4.56, sum) == SOAP_OK)
    std::cout << "Sum = " << sum << std::endl;
  else
    calc.soap_stream_fault(std::cerr);
  calc.destroy();
}
