#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

class Image {
  std::vector<int> _pixels;
  int _weight, _height;

public:
  Image();
  Image(int weight, int height);
  Image(const Image& other);

  int getPixel(int i, int j) const {
    return _pixels[(i * _weight) + j];
  }
  int setPixel(int i, int j, int value) {
    _pixels[(i * _weight) + j] = value;
  }
  // void read(std::string file_name);
};

#endif //IMAGE_H
