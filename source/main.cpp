#include "image.h"

#include <iostream>
#include <cmath>
using namespace std;

int main() {
  Image I(500,500,255);
  // cout << I.max();
  for(int i = 0; i < I.height(); i++) {
    for(int j = 0; j < I.width(); j++) {
      if(j > i) I.setPixel(j, i, abs(I.max() - i));
      else I.setPixel(j, i, abs(I.max() - j));
    }
  }
  I.histogram();
  I.histogramDisplay();
  I.write("pbm/test.pgm");
  return 0;
}
