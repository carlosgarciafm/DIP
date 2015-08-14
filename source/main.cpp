#include <iostream>
using namespace std;

#include "image.h"

int main() {
  Image I;
  I.read("bc.pgm");
  I.write("output.pgm");
  // int widht, height;
  // cin >> widht >> height;
  // cout << I.getPixel(widht, height) << endl;
}
