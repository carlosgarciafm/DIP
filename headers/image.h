#include <vector>
#include <string>

class Image {
  std::vector<int> _pixels;
  std::vector<int> _histogram;
  std::vector<int> _plot;
  int _width, _height;
  int _max;

public:
  Image();
  Image(int height, int width, int max);
  Image(const Image& other);

  int width() const { return _width; }
  int height() const { return _height; }
  int max() const { return _max; }

  int getPixel(int i, int j) const {
    return _pixels[(i * _width) + j];
  }
  int setPixel(int i, int j, int value) {
    _pixels[(i * _width) + j] = value;
  }
  void read(std::string file_name);
  void write(std::string file_name) const;
  Image chunk(int i1, int j1, int i2, int j2) const;
  void stamp(int i, int j, const Image& P);
  void negative();
  void posterize(int levels);
  Image zoom(int i1, int j1, int i2, int j2, int factor);
  void rotate(int degree);

  int getPlot(int i, int j) {
    return _plot[(i * (_max + 1)) + j];
  }
  int setPlot(int i, int j, int value) {
    _plot[(i * (_max + 1)) + j] = value;
  }
  void histogram(int ceiling, std::string plot_name);
  void histogramPlot(int top, int ceiling, std::string plot_name);
};
