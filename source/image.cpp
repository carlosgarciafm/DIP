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
                                               _histogram(width * height, 0),
                                               _plot(width * height, 0) {
  _width = width;
  _height = height;
  _max = max;
}

Image::Image(const Image& other) : _pixels(other._pixels),
                                   _histogram(other._histogram),
                                   _plot(other._plot) {
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
    int c = 0;
    if(j1 < 0) { j1 = 0; c++; }
    if(j2 > width) { j2 = width; c++; }
    if(i1 < 0) { i1 = 0; c++; }
    if(i2 > height) { i2 = height; c++; }
    if(c != 0) cout << "At least one of the given coordinates is out of the image range" << endl;
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

Image Image::zoom(int j1, int i1, int j2, int i2, int factor) {
  Image B;
  B = chunk(j1, i1, j2, i2);
  int width = (j2 - j1) * factor;
  int height = (i2 - i1) * factor;
  Image Z(width, height, _max);
  for(int m = 0; m < B.height(); m++) {
    for(int n = 0; n < B.width(); n++) {
      for(int i = m * factor; i < m * factor + factor; i++) {
        for(int j = n * factor; j < n * factor + factor; j++) {
          Z.setPixel(j, i, getPixel(n, m));
        }
      }
    }
  }
  return Z;
}

void Image::rotate(int degree) {
  Image A(_width, _height, _max);
  for(int n = 0; n < _pixels.size(); n++) {
    A._pixels[n] = _pixels[n];
  }
  switch (degree) {
    case 90:
      _width = A.height(), _height = A.width();
      for(int j = 0; j < _width; j++) {
        for(int i = _height - 1; i >= 0; i--) {
          setPixel(j,i, A.getPixel(A.width() - i - 1, j));
        }
      }
      break;
    case 180:
      for(int i = _height - 1; i >= 0; i--) {
        for(int j = _width - 1; j >= 0; j--) {
          setPixel(j,i, A.getPixel(_width - j - 1, _height - i - 1));
        }
      }
      break;
    case 270:
      _width = A.height(), _height = A.width();
      for(int j = _width - 1; j >= 0 ; j--) {
        for(int i = 0; i < _height; i++) {
          setPixel(j,i, A.getPixel(i, A.height() - j - 1));
        }
      }
      break;
    default:
      cout << "NO VALID ROTATION VALUE" << endl <<
              "THE ORIGINAL IMAGE WILL BE GIVEN BACK" << endl;
  }
}

void Image::histogram(int ceiling, string plot_name) {
  int top = 0;
  _histogram.resize(_max + 1);
  for(int i = 0; i < _pixels.size(); i++) {
    int value = _pixels[i];
    _histogram[value] += 1;
    if(_histogram[value] > top) top = _histogram[value];
  }
  histogramPlot(top, ceiling, plot_name);
}
void Image::histogramPlot(int top, int ceiling, string plot_name) {
  int height = ceiling;
  _plot.resize(height * (_max + 1));
  for(int j = 0; j < (_max + 1); j++) {
    _histogram[j] = ceil((double(height) / top) * _histogram[j]);
    for(int i = height - 1; i >= 0 ; i--) {
      if(i >= height - _histogram[j]) {
        setPlot(j, i, j);
      }else setPlot(j, i, (255 - j));
    }
  }
  for(int i = 0; i < _histogram.size(); i++) {
    cout << i << " = " << _histogram[i] << endl;
  }
  ofstream F(plot_name.c_str());
  F << "P2" << endl;
  F << "# This file was written by CarlosGarcia" << endl;
  F << _max + 1 << ' ' << height << endl;
  F << _max << endl;
  for(int m = 0; m < _plot.size(); m++) {
    F << _plot[m] << endl;
  }
}
