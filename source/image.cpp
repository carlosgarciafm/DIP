#include "image.h"

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Image::Image() {
  _width = 0;
  _height = 0;
}

Image::Image(int width, int height) : _pixels(width * height, 0) {
  _width = width;
  _height = height;
}

Image::Image(const Image& other) : _pixels(other._pixels) {
  _width = other._width;
  _height = other._height;
}

void Image::read(string file_name) {
  ifstream F(file_name.c_str());
  if(!F.is_open()) {
    cout << "COULD NOT OPEN GIVEN FILE" << endl;
    return;
  }

  string line;
  getline(F, line);
  if(line != "P2") {
    cout << "WRONG FORMAT" << endl;
    return;
  }

  getline(F, line);
  while(line[0] == '#') {
    getline(F, line);
  }

  istringstream S(line);
  S >> _width >> _height;

  int max;
  F >> max;
  _pixels.resize(_width * _height);
  for(int i = 0; i < _pixels.size(); i++) {
    F >> _pixels[i];
  }
}
