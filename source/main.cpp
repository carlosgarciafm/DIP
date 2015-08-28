#include "image.h"

#include <iostream>
using namespace std;

int main() {
  Image I(10,10,255);
  for(int i = 0; i < I.height(); i++) {
    for(int j = 0; j < I.width(); j++) {
      if((i + j) % 2 == 0) I.setPixel(j, i, I.max());
    }
  }
  // cout << "image created" << endl;
  Image Z;
  // cout << "image created" << endl;
  Z = I.zoom(9);
  // cout << "zoom method applied" << endl;
  Z.write("pbm/zoom.pgm");
  // cout << "file written" << endl;
  return 0;
}
