#include "image.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

Image::Image() {
  _width = 0;
  _height = 0;
  _max = 255;
}

Image::Image(int width, int height, int max) : _pixels(width * height, 0),
                                               _histogram(width * height, 0) {
  _width = width;
  _height = height;
  _max = max;
}

Image::Image(const Image& other) : _pixels(other._pixels),
                                   _histogram(other._histogram) {
  _width = other._width;
  _height = other._height;
  _max = other._max;
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
  F >> _max;
  _pixels.resize(_width * _height);
  for(int i = 0; i < _pixels.size(); i++) {
    F >> _pixels[i];
  }
}

void Image::write(string file_name) const {
  ofstream F(file_name.c_str());
  F << "P2" << endl;
  F << "# This file was written by CarlosGarcia" << endl;
  F << _width << ' ' << _height << endl;
  F << _max << endl;
  for(int i = 0; i < _pixels.size(); i++) {
    F << _pixels[i] << ' ';
    if(i % _width == (_width - 1)) {
      F << endl;
    }
  }
}

void checkUp(int &j1, int &i1, int &j2, int &i2, int width, int height) {
    if(j1 < 0) j1 = 0;
    if(j2 > width) j2 = width;
    if(i1 < 0) i1 = 0;
    if(i2 > height) i2 = height;
}
Image Image::chunk(int j1, int i1, int j2, int i2) const {
  checkUp(j1, i1, j2, i2, _width, _height);
  Image A((j2 - j1), (i2 - i1), _max);
  for(int m = i1; m < i2; m++) {
    for(int n = j1; n < j2; n++) {
      int ip = m - i1;
      int jp = n - j1;
      A.setPixel(jp, ip, getPixel(n, m));
    }
  }
  return A;
}

void Image::stamp(int j, int i, const Image& P) {
  for(int m = i; m < (i + P.height()); m++) {
    for(int n = j; n < (j + P.width()); n++) {
      int x = m - i;
      int y = n - j;
      setPixel(n, m, P.getPixel(y, x));
    }
  }
}

void Image::negative() {
  for(int i = 0; i < _pixels.size(); i++) {
    _pixels[i] = _max - _pixels[i];
  }
}

void Image::posterize(int levels) {
  for(int i = 0; i < _pixels.size(); i++) {
    double value = double(_pixels[i]) / _max * (levels - 1);
    value = round(value);
    _pixels[i] = int(value * _max / (levels - 1));
  }
}

void Image::histogram() {
  _histogram.resize(_max + 1);
  for(int i = 0; i < _pixels.size(); i++) {
    int value = _pixels[i];
    _histogram[value] += 1;
  }
}

// ToDo: implement a way to plot the results
