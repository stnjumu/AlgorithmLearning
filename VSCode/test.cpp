#include <iostream>
#include <algorithm>
using namespace std;
class Complex {
   public:
      int real;
      int imag;
      Complex(): real(0), imag(0){}
      Complex operator + (Complex const &obj) {
         Complex res;
         res.real = real + obj.real;
         res.imag = imag + obj.imag;
         return res;
      }
      Complex operator + (int const &obj) {
         Complex res;
         res.real = real + obj;
         res.imag = imag;
         return res;
      }
};
Complex operator + (int &a, Complex &b) {
    b.real += a;
    return b;
}
int main()
{
    int a=2;
    Complex b;
    auto c = a+b;
    cout<< c.real <<"+ i"<<c.imag<<endl;
    
    
    return 0;
}
