#include <iostream>
using namespace std;

#include "image.h"

int main() {
  Image I(50, 50);
  I.setPixel(25, 25, 100);
  cout << I.getPixel(25, 25) << endl;

  // I.read("bc.pgm");

  // cout << I.getPixel(590, 390) << endl;
}
