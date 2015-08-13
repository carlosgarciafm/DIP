#include <iostream>
using namespace std;

#include "image.h"

int main() {
  Image I;
  I.read("bc.pgm");
  
  int widht, height;
  cin >> widht >> height;
  cout << I.getPixel(widht, height) << endl;
}
