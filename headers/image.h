#include <vector>
#include <string>

class PGM {
  std::vector<int> _pixels;
  std::vector<int> _histogram;
  std::vector<int> _plot;
  int _width, _height;
  int _max;
  std::string _type;

public:
  PGM();
  PGM(int height, int width, int max, std::string type);
  PGM(const PGM& other);

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
  PGM chunk(int i1, int j1, int i2, int j2) const;
  void stamp(int i, int j, const PGM& P);
  void negative();
  void posterize(int levels);
  PGM zoom(int i1, int j1, int i2, int j2, int factor);
  void rotate(int degree);
  void substraction(PGM& S);
  void addition(PGM& A);

  void topLow(int& top, int& low);
  void normalize(int top, int low);

  int getPlot(int i, int j) {
    return _plot[(i * (_max + 1)) + j];
  }
  int setPlot(int i, int j, int value) {
    _plot[(i * (_max + 1)) + j] = value;
  }
  void histogram(int ceiling, std::string plot_name);
  void histogramPlot(int top, int ceiling, std::string plot_name);
};


struct Pixel {
  int _r, _g, _b;
  Pixel();
  Pixel(int r, int g, int b);
  void negative(int max);
  void posterize(int levels, int max);
};

class PPM {
  std::vector<Pixel> _pixels;
  int _width, _height;
  int _max;
  std::string _type;

public:
  PPM();
  PPM(int height, int width, int max, std::string type);
  PPM(const PPM& other);

  int width() const { return _width; }
  int height() const { return _height; }
  int max() const { return _max; }

  Pixel getPixel(int i, int j) const {
    return _pixels[(i * _width) + j];
  }
  int setPixel(int i, int j, Pixel value) {
    _pixels[(i * _width) + j] = value;
  }
  void read(std::string file_name);
  void write(std::string file_name) const;
  PPM chunk(int i1, int j1, int i2, int j2) const;
  void stamp(int i, int j, const PPM& P);
  void negative();
  void posterize(int levels);
  PPM zoom(int i1, int j1, int i2, int j2, int factor);
  void rotate(int degree);
};
