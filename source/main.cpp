#include "image.h"

#include <iostream>
using namespace std;

int main() {
  // Image I(300,300,255);
  // for(int i = 0; i < I.height(); i++) {
  //   for(int j = 0; j < I.width(); j++) {
  //     if(i < j)  I.setPixel(j,i,255);
  //   }
  // }
  // I.write("pbm/original.pgm");
  Image I;
  I.read("pbm/rotate.pgm");
  I.histogram(600,"pbm/h_rotate.pgm");
  // Image I;
  // I.read("pbm/bc.pgm");
  // I.rotate(90);
  // I.write("pbm/rotate.pgm");
  return 0;
}
