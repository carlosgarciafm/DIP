#include "image.h"

#include <iostream>
using namespace std;

int main() {
  Image I;
  I.read("pgm/wc.pgm");
  I.write("pgm/wc_copy.pgm");
  // Image H;
  // H.read("pgm/bc.pgm");
  // Image J(I);
  // Image K(H);
  // // H.negative();
  // H.substraction(I);
  // H.write("pgm/wc_subs2.pgm");
  // J.addition(K);
  // J.write("pgm/wc_add.pgm");
  return 0;
}
