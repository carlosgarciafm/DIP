#include "image.h"

#include <iostream>
using namespace std;

int main() {
  Image I;
  I.read("bc.pgm");

  Image A;
  int j1 = 0, i1 = 0, j2 = 0, i2 = 0;
  cout << "Please input the coordinates of the start and end points, use (j1,i1) and (j2,i2): ";
  cin >> j1 >> i1 >> j2 >> i2;
  A = I.chunk(j1, i1, j2, i2);
  A.write("output_chunk.pgm");
  // int widht, height;
  // cin >> widht >> height;
  // cout << I.getPixel(widht, height) << endl;
}
