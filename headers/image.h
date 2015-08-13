#include <vector>
#include <string>

class Image {
  std::vector<int> _pixels;
  int _width, _height;

public:
  Image();
  Image(int width, int height);
  Image(const Image& other);

  int getPixel(int i, int j) const {
    return _pixels[(i * _width) + j];
  }
  int setPixel(int i, int j, int value) {
    _pixels[(i * _width) + j] = value;
  }
  void read(std::string file_name);
};
