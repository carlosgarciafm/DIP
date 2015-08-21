#include "image.h"

#include <iostream>
using namespace std;

int main() {
  Image I;
  I.read("pbm/bc.pgm");
  // for(int i = 0; i < I.height(); i++) {
  //   for(int j = 0; j < I.width(); j++) {
  //     if(j < i) I.setPixel(j, i, I.max());
  //   }
  // }
  I.histogram("pbm/plot.pgm");
  return 0;
}
