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
  Image(int width, int height, int max);
  Image(const Image& other);

  int width() const { return _width; }
  int height() const { return _height; }
  int max() const { return _max; }

  int getPixel(int j, int i) const {
    return _pixels[(i * _width) + j];
  }
  int setPixel(int j, int i, int value) {
    _pixels[(i * _width) + j] = value;
  }
  void read(std::string file_name);
  void write(std::string file_name) const;
  Image chunk(int j1, int i1, int j2, int i2) const;
  void stamp(int j, int i, const Image& P);
  void negative();
  void posterize(int levels);

  int getPlot(int j, int i) {
    return _plot[(i * (_max + 1)) + j];
  }
  int setPlot(int j, int i) {
    _plot[(i * (_max + 1)) + j] = _max;
  }
  void histogram(std::string plot_name);
  void histogramPlot(int top, std::string plot_name);
};
