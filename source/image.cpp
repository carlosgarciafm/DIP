#include "image.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

PGM::PGM() {
  _width = 0;
  _height = 0;
  _max = 255;
  _type = "NULL";
}

PGM::PGM(int height, int width, int max, string type) : _pixels((width * height), 0),
                                               _histogram((width * height), 0),
                                               _plot((width * height), 0) {
  _width = width;
  _height = height;
  _max = max;
  _type = type;
}

PGM::PGM(const PGM& other) : _pixels(other._pixels),
                                   _histogram(other._histogram),
                                   _plot(other._plot) {
  _width = other._width;
  _height = other._height;
  _max = other._max;
  _type = other._type;
}

void PGM::read(string file_name) {
  ifstream F(file_name.c_str());
  if(!F.is_open()) {
    cout << "COULD NOT OPEN GIVEN FILE" << endl;
    return;
  }
  string line;
  getline(F, line);
  _type = line;
  // cout << _type << endl;
  // if(line != "P2") {
  //   cout << "WRONG FORMAT" << endl;
  //   return;
  // }
  getline(F, line);
  while(line[0] == '#') {
    getline(F, line);
  }
  istringstream S(line);
  S >> _width >> _height;
  F >> _max;
  _pixels.resize(_width * _height);
  for(int n = 0; n < _pixels.size(); n++) {
    F >> _pixels[n];
  }
}

void PGM::write(string file_name) const {
  ofstream F(file_name.c_str());
  F << _type << endl;
  F << "# This file was written by CarlosGarcia" << endl;
  F << _width << ' ' << _height << endl;
  F << _max << endl;
  for(int n = 0; n < _pixels.size(); n++) {
    F << _pixels[n] << endl;
    // if((n % _width) == (_width - 1)) {
    //   F << endl;
    // }
  }
}

void checkUp(int &i1, int &j1, int &i2, int &j2, int height, int width) {
    int c = 0;
    if(j1 < 0) { j1 = 0; c++; }
    if(j2 > width) { j2 = width; c++; }
    if(i1 < 0) { i1 = 0; c++; }
    if(i2 > height) { i2 = height; c++; }
    if(c != 0) cout << "At least one of the given coordinates is out of the PGM range" << endl;
}
PGM PGM::chunk(int i1, int j1, int i2, int j2) const {
  checkUp(i1, j1, i2, j2, _height, _width);
  PGM A((i2 - i1), (j2 - j1), _max, _type);
  for(int m = i1; m < i2; m++) {
    for(int n = j1; n < j2; n++) {
      int ip = m - i1;
      int jp = n - j1;
      A.setPixel(ip, jp, getPixel(m, n));
    }
  }
  return A;
}

void PGM::stamp(int i, int j, const PGM& P) {
  int i2 = i + (P.height() - 1);
  int j2 = j + (P.width() - 1);
  checkUp(i, j, i2, j2, _height, _width);
  for(int m = i; m <= i2; m++) {
    for(int n = j; n <= j2; n++) {
      int x = m - i;
      int y = n - j;
      setPixel(m, n, P.getPixel(x, y));
    }
  }
}

void PGM::negative() {
  for(int n = 0; n < _pixels.size(); n++) {
    _pixels[n] = _max - _pixels[n];
  }
}

void PGM::posterize(int levels) {
  for(int n = 0; n < _pixels.size(); n++) {
    double value = (double(_pixels[n]) / _max) * (levels - 1);
    value = round(value);
    _pixels[n] = int((value * _max) / (levels - 1));
  }
}

PGM PGM::zoom(int i1, int j1, int i2, int j2, int factor) {
  PGM B;
  B = chunk(i1, j1, i2, j2);
  int width = (j2 - j1) * factor;
  int height = (i2 - i1) * factor;
  PGM Z(height, width, _max, _type);
  for(int m = 0; m < B.height(); m++) {
    for(int n = 0; n < B.width(); n++) {
      for(int i = m * factor; i < ((m * factor) + factor); i++) {
        for(int j = n * factor; j < ((n * factor) + factor); j++) {
          Z.setPixel(i, j, getPixel(m, n));
        }
      }
    }
  }
  return Z;
}

void PGM::rotate(int degree) {
  PGM A(_height, _width, _max, _type);
  for(int n = 0; n < _pixels.size(); n++) {
    A._pixels[n] = _pixels[n];
  }
  switch (degree) {
    case 90:
      _width = A.height(), _height = A.width();
      for(int j = 0; j < _width; j++) {
        for(int i = _height - 1; i >= 0; i--) {
          setPixel(i, j, A.getPixel(j, ((A.width() - i) - 1)));
        }
      }
      break;
    case 180:
      for(int i = _height - 1; i >= 0; i--) {
        for(int j = _width - 1; j >= 0; j--) {
          setPixel(i, j, A.getPixel(((_height - i) - 1), ((_width - j) - 1)));
        }
      }
      break;
    case 270:
      _width = A.height(), _height = A.width();
      for(int j = _width - 1; j >= 0 ; j--) {
        for(int i = 0; i < _height; i++) {
          setPixel(i, j, A.getPixel(((A.height() - j) - 1), i));
        }
      }
      break;
    default:
      cout << "NO VALID ROTATION VALUE" << endl <<
              "THE ORIGINAL PGM WILL BE GIVEN BACK" << endl;
  }
}

void PGM::substraction(PGM& S) {
  int top = 0, low = _max;
  for(int i = 0; i < _height; i++) {
    for(int j = 0; j < _width; j++) {
      int sub = abs(getPixel(i, j) - S.getPixel(i, j));
      setPixel(i, j, sub);
    }
  }
  topLow(top, low);
  normalize(top, low);
}
void PGM::addition(PGM& A) {
  int top = 0, low = _max;
  for(int i = 0; i < A._height; i++) {
    for(int j = 0; j < _width; j++) {
      int sub = getPixel(i, j) + A.getPixel(i, j);
      setPixel(i, j, sub);
    }
  }
  topLow(top, low);
  normalize(top, low);
}

void PGM::topLow(int& top, int& low) {
  for(int n = 0; n < _pixels.size(); n++) {
    if(_pixels[n] > top) top = _pixels[n];
    if(_pixels[n] < low) low = _pixels[n];
  }
}
void PGM::normalize(int top, int low) {
  for(int n = 0; n < _pixels.size(); n++) {
    int value = floor((float(_max) / (top)) * (_pixels[n]));
    _pixels[n] = value;
  }
}

void PGM::histogram(int ceiling, string plot_name) {
  int top = 0;
  _histogram.resize(_max + 1);
  for(int n = 0; n < _pixels.size(); n++) {
    int value = _pixels[n];
    _histogram[value] += 1;
    if(_histogram[value] > top) top = _histogram[value];
  }
  if(plot_name != "null") {
    histogramPlot(top, ceiling, plot_name);
  }
}
void PGM::histogramPlot(int top, int ceiling, string plot_name) {
  int height = ceiling;
  _plot.resize(height * (_max + 1));
  for(int j = 0; j < (_max + 1); j++) {
    _histogram[j] = ceil((double(height) / top) * _histogram[j]);
    for(int i = height - 1; i >= 0 ; i--) {
      if(i >= height - _histogram[j]) {
        setPlot(i, j, j);
      }else setPlot(i, j, (255 - j));
    }
  }
  ofstream F(plot_name.c_str());
  F << _type << endl;
  F << "# This file was written by CarlosGarcia" << endl;
  F << _max + 1 << ' ' << height << endl;
  F << _max << endl;
  for(int n = 0; n < _plot.size(); n++) {
    F << _plot[n] << endl;
  }
}


Pixel::Pixel() {
  _r = 0;
  _g = 0;
  _b = 0;
}

Pixel::Pixel(int r, int g, int b) {
  _r = r;
  _g = g;
  _b = b;
}

PPM::PPM() {
  _width = 0;
  _height = 0;
  _max = 255;
  _type = "NULL";
}

PPM::PPM(int height, int width, int max, string type) : _pixels((width * height), Pixel(0, 0, 0)) {
  _width = width;
  _height = height;
  _max = max;
  _type = type;
}

PPM::PPM(const PPM& other) : _pixels(other._pixels) {
  _width = other._width;
  _height = other._height;
  _max = other._max;
  _type = other._type;
}

void PPM::read(string file_name) {
  ifstream F(file_name.c_str());
  if(!F.is_open()) {
    cout << "COULD NOT OPEN GIVEN FILE" << endl;
    return;
  }
  string line;
  getline(F, line);
  _type = line;
  // if(line != "P3") {
  //   cout << "WRONG FORMAT" << endl;
  //   return;
  // }
  getline(F, line);
  while(line[0] == '#') {
    getline(F, line);
  }
  istringstream S(line);
  S >> _width >> _height;
  F >> _max;
  _pixels.resize(_width * _height);
  for(int n = 0; n < _pixels.size(); n++) {
    F >> _pixels[n]._r;
    F >> _pixels[n]._g;
    F >> _pixels[n]._b;
  }
}

void PPM::write(string file_name) const {
  ofstream F(file_name.c_str());
  F << _type << endl;
  F << "# This file was written by CarlosGarcia" << endl;
  F << _width << ' ' << _height << endl;
  F << _max << endl;
  for(int n = 0; n < _pixels.size(); n++) {
    F << _pixels[n]._r << ' ';
    F << _pixels[n]._g << ' ';
    F << _pixels[n]._b << ' ';
    F << endl;
  }
}

PPM PPM::chunk(int i1, int j1, int i2, int j2) const {
  checkUp(i1, j1, i2, j2, _height, _width);
  PPM A((i2 - i1), (j2 - j1), _max, _type);
  for(int m = i1; m < i2; m++) {
    for(int n = j1; n < j2; n++) {
      int ip = m - i1;
      int jp = n - j1;
      A.setPixel(ip, jp, getPixel(m, n));
    }
  }
  return A;
}

void PPM::stamp(int i, int j, const PPM& P) {
  int i2 = i + (P.height() - 1);
  int j2 = j + (P.width() - 1);
  checkUp(i, j, i2, j2, _height, _width);
  for(int m = i; m <= i2; m++) {
    for(int n = j; n <= j2; n++) {
      int x = m - i;
      int y = n - j;
      setPixel(m, n, P.getPixel(x, y));
    }
  }
}

void Pixel::negative(int max) {
  _r = max - _r;
  _g = max - _g;
  _b = max - _b;
}
void PPM::negative() {
  for(int n = 0; n < _pixels.size(); n++) {
    _pixels[n].negative(_max);
  }
}

int post(double x, int levels, int max) {
  double value = (x / max) * (levels - 1);
  value = round(value);
  return int((value * max) / (levels - 1));
}
void Pixel::posterize(int levels, int max) {
  _r = post(_r, levels, max);
  _g = post(_g, levels, max);
  _b = post(_b, levels, max);
}
void PPM::posterize(int levels) {
  for(int n = 0; n < _pixels.size(); n++) {
    _pixels[n].posterize(levels, _max);
  }
}

PPM PPM::zoom(int i1, int j1, int i2, int j2, int factor) {
  PPM B;
  checkUp(i1,j1,i2,j2,_height,_width);
  B = chunk(i1, j1, i2, j2);
  int width = (j2 - j1) * factor;
  int height = (i2 - i1) * factor;
  PPM Z(height, width, _max, _type);
  for(int m = 0; m < B.height(); m++) {
    for(int n = 0; n < B.width(); n++) {
      for(int i = m * factor; i < ((m * factor) + factor); i++) {
        for(int j = n * factor; j < ((n * factor) + factor); j++) {
          Z.setPixel(i, j, B.getPixel(m, n));
        }
      }
    }
  }
  return Z;
}

void PPM::rotate(int degree) {
  PPM A(_height, _width, _max, _type);
  for(int n = 0; n < _pixels.size(); n++) {
    A._pixels[n] = _pixels[n];
  }
  switch (degree) {
    case 90:
      _width = A.height(), _height = A.width();
      for(int j = 0; j < _width; j++) {
        for(int i = _height - 1; i >= 0; i--) {
          setPixel(i, j, A.getPixel(j, ((A.width() - i) - 1)));
        }
      }
      break;
    case 180:
      for(int i = _height - 1; i >= 0; i--) {
        for(int j = _width - 1; j >= 0; j--) {
          setPixel(i, j, A.getPixel(((_height - i) - 1), ((_width - j) - 1)));
        }
      }
      break;
    case 270:
      _width = A.height(), _height = A.width();
      for(int j = _width - 1; j >= 0 ; j--) {
        for(int i = 0; i < _height; i++) {
          setPixel(i, j, A.getPixel(((A.height() - j) - 1), i));
        }
      }
      break;
    default:
      cout << "NO VALID ROTATION VALUE" << endl <<
              "THE ORIGINAL IMAGE WILL BE GIVEN BACK" << endl;
  }
}
