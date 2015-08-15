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
  int getPixel(int j, int i) const {
    return _pixels[(i * _width) + j];
  }
  int setPixel(int j, int i, int value) {
    _pixels[(i * _width) + j] = value;
  }
  void read(std::string file_name);
  void write(std::string file_name) const;
  Image chunk(int j1, int i1, int j2, int i2) const;     // j are  width; i are height
  void stamp(int j, int i, const Image& P);
  void negative();
};
