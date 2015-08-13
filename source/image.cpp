#include "image.h"

#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Image::Image()
// pixels default's contructor is called
{
  _height = 0;
  _weight = 0;
}

Image::Image(int weight, int height) : _pixels(weight * height, 0) {
  _weight = weight;
  _height = height;
}

// Image copy constructor
Image::Image(const Image& other) : _pixels(other._pixels) {
  _weight = other._weight;
  _height = other._height;
}

// void Image::read(string file_name) {
//   ifstream F(file_name.c_str());
//   if(!F.is_open()) {
//     cout << "CANNOT OPEN THE GIVEN '" << file_name << "' FILE" << endl;
//     return;
//   }
//   cout << "open";       // ojdfjapsdjifasdf
//   string line;
//   getline(F, line);
//   cout << "line read";  //ojfojsdpf asdf
//   if(line != "P2") {
//     cout << "CANNOT READ THE GIVEN FORMAT" << endl;
//     return;
//   }
//   cout << "correct format"; //jsdfjpsdifjposdjf
//   getline(F, line);   // looking for comentaries
//   while(line[0] == '#') {
//     getline(F, line);   // got out of the loop with the needed info: _weight and _height
//   }
//   istringstream S(line);
//   S >> _weight >> _height;
//   int max;
//   F >> max;
//   _pixels.resize(_weight * _height);
//   for(int i = 0; i < _pixels.size(); i++) {
//     F >> _pixels[i];
//   }
// }
