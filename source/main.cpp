#include "image.h"

#include <iostream>
using namespace std;

int main() {
  // Image I(20,10,255);
  // for(int i = 0; i < I.height(); i++) {
  //   for(int j = 0; j < I.width(); j++) {
  //     if((j + i) % 2 == 0)  I.setPixel(i,j,255);
  //   }
  // }

  Image I;
  I.read("pbm/bc.pgm");
  // I.write("pbm/original.pgm");

  // Image A;
  // A = I.chunk(100,100,300,500);
  // A.write("pbm/chunk.pgm");

  // I.stamp(300,100,A);
  // I.write("pbm/stamp.pgm");

  // I.negative();
  // I.write("pbm/negative.pgm");

  // I.posterize(4);
  // I.write("pbm/posterize.pgm");

  // Image A;
  // A = I.zoom(100,100,200,300,3);
  // A.write("pbm/zoom.pgm");

  I.rotate(270);
  I.write("pbm/rotate270.pgm");

  // I.histogram(500,"pbm/histogram.pgm");
  return 0;
}
