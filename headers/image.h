#include <vector>
#include <string>

class Image {
  std::vector<int> _pixels;
  int _width, _height;
  int _max;

public:
  Image();
  Image(int width, int height, int max);
  Image(const Image& other);

  int width() const { return _width; }
  int height() const { return _height; }
  int getPixel(int i, int j) const {
    return _pixels[(j * _width) + i];
  }
  int setPixel(int i, int j, int value) {
    _pixels[(j * _width) + i] = value;
  }
  void read(std::string file_name);
  void write(std::string file_name) const;
};
