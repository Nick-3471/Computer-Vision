#ifndef IMAGE_HPP_
#define IMAGE_HPP_
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include "Matrix.hpp"

class Image
{
public:
  Image();
  Image(const Image &src);
  ~Image();

  Image& operator=(const Image &rhs);
  void clear();
  Image transformByInverse(const Matrix &matrix) const;
  Image crop(unsigned int x,
	     unsigned int y,
	     unsigned int width,
	     unsigned int height) const;

  float& at(unsigned int x, unsigned int y) throw(std::out_of_range);
  float get(unsigned int x, unsigned int y) const throw(std::out_of_range);
  unsigned int getHeight() const;
  unsigned int getWidth() const;
  unsigned int getArea() const;

  void read8BitPGM(const char* file_name) throw(std::runtime_error);
  void write8BitPGM(const char* file_name) const throw(std::runtime_error);
private:
  float* data_;
  unsigned int width_, height_;
};

#endif // IMAGE_HPP_
