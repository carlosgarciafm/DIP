#include "image.h"

#include <iostream>
using namespace std;

int main() {
  PPM Z;
  Z.read("ppm/wc.ppm");
  Z.write("ppm/wc_copy.ppm");
  PGM I;
  I.read("pgm/wc.pgm");
  I.write("pgm/wc_copy.pgm");
  // PGM H;
  // H.read("pgm/bc.pgm");
  // PGM J(I);
  // PGM K(H);
  // // H.negative();
  // H.substraction(I);
  // H.write("pgm/wc_subs2.pgm");
  // J.addition(K);
  // J.write("pgm/wc_add.pgm");
  return 0;
}
