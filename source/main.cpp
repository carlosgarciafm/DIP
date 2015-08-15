#include "image.h"

#include <iostream>
using namespace std;

int main() {
  Image I;
  I.read("pgm/bc.pgm");

  Image A;
  int j1 = 0, i1 = 0, j2 = 0, i2 = 0;
  cout << "Please input the coordinates of the start and end points, use (j1,i1) and (j2,i2): ";
  cin >> j1 >> i1 >> j2 >> i2;
  A = I.chunk(j1, i1, j2, i2);

  Image P(800, 800, 255);
  int j3 = 0, i3 = 0;
  cout << "Please input the coordinates where you want to paste the chunk, use (j3, i3): ";
  cin >> j3 >> i3;
  P.paste(j3, i3, A);
  P.write("pgm/output_paste.pgm");

  // int widht, height;
  // cin >> widht >> height;
  // cout << I.getPixel(widht, height) << endl;
}
