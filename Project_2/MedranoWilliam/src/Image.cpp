#include "Image.hpp"

Image::Image()
  :data_(NULL), width_(0), height_(0)
{
}

Image::Image(const Image &src)
  :data_(NULL), width_(0), height_(0)
{
  *this = src;
}

Image::~Image()
{
  clear();
}

Image& Image::operator=(const Image &rhs)
{
  unsigned int i, buffer_size;

  // Clear self
  clear();
  // Set dimensions
  width_ = rhs.width_;
  height_ = rhs.height_;
  buffer_size = width_ * height_;

  // Allocate memory if needed
  if (buffer_size > 0)
  {
    data_ = new float[buffer_size];
  }

  // Copy over data
  for (i = 0; i < buffer_size; i++)
  {
    data_[i] = rhs.data_[i];
  }

  return *this;
}


void Image::clear()
{
  if (data_ != NULL)
  {
    delete []data_;
    data_ = NULL;
    width_ = 0;
    height_ = 0;
  }
}

Image Image::transformByInverse(const Matrix &matrix) const
{
  Image new_image(*this);
  unsigned int x_dest, y_dest, x_src, y_src;

  for (y_dest = 0; y_dest < height_; y_dest++)
  {
    for (x_dest = 0; x_dest < width_; x_dest++)
    {
      x_src = x_dest * matrix.get(1, 1) +
	      y_dest * matrix.get(1, 2) +
	      matrix.get(1, 3);
      y_src = x_dest * matrix.get(2, 1) +
	      y_dest * matrix.get(2, 2) +
	      matrix.get(2, 3);
      if (x_src >= 0 && x_src < width_ && y_src >= 0 && y_src < height_)
      {
	new_image.at(x_dest, y_dest) = get(x_src, y_src);
      }
      else
      {
	new_image.at(x_dest, y_dest) = 0.f;
      }
    }
  }

  return new_image;
}

Image Image::crop(unsigned int x,
		  unsigned int y,
		  unsigned int width,
		  unsigned int height) const
{
  unsigned int i, j;
  Image cropped;

  // Set cropped parameters
  cropped.width_ = width;
  cropped.height_ = height;
  cropped.data_ = new float[width * height];

  // Copy over data
  for (j = 0; j < height; j++)
  {
    for (i = 0; i < width; i++)
    {
      cropped.at(i, j) = get(i + x, j + y);
    }
  }

  // Done
  return cropped;
}
		    

float& Image::at(unsigned int x, unsigned int y) throw(std::out_of_range)
{
  if (x >= width_ || y >= height_)
  {
    throw std::out_of_range("at(): coordinates are too large.");
  }
  return data_[x + (y*width_)];
}

float Image::get(unsigned int x, unsigned int y) const throw(std::out_of_range)
{
  if (x >= width_ || y >= height_)
  {
    throw std::out_of_range("at(): coordinates are too large.");
  }
  return data_[x + (y*width_)];
}

unsigned int Image::getHeight() const
{
  return height_;
}

unsigned int Image::getWidth() const
{
  return width_;
}

unsigned int Image::getArea() const
{
  return width_ * height_;
}

void Image::read8BitPGM(const char* file_name) throw(std::runtime_error)
{
  std::ifstream file;
  char temp_buffer[128];
  unsigned int i, size, max_val;
  float conversion_factor;

  // Clear this image
  clear();

  // Open file
  file.open(file_name);
  if (!file.good())
  {
    throw std::runtime_error("read8BitPGM(): Failed to open file.");
  }

  // Get P5 header
  file.getline(temp_buffer, 128);
  if (temp_buffer[0] != 'P' || temp_buffer[1] != '5')
  {
    file.close();
    throw std::runtime_error("read8BitPGM(): File has wrong header.");
  }

  // Skip comments
  for (temp_buffer[0] = '#';
       temp_buffer[0] == '#';
       file.getline(temp_buffer, 128))
    {
    }

  // Get dimensions
  sscanf(temp_buffer, "%i %i", &width_, &height_);

  // Exit if size 0
  size = width_ * height_;
  if (size == 0)
  {
    width_ = 0;
    height_ = 0;
    file.close();
    return;
  }

  // Allocate data buffer
  data_ = new float[size];

  // Get bits per pixel
  file.getline(temp_buffer, 128);
  sscanf(temp_buffer, "%i", &max_val);
  {
    if (max_val != 255)
    {
      clear();
      throw std::runtime_error("read8BitPGM(): File is not 8bit PGM.");
    }
  }
  conversion_factor = 1.f / static_cast<float>(max_val);

  // Read in data
  for (i = 0; i < size; i++)
  {
    // Read byte
    file.read(temp_buffer, 1);
    data_[i] = *(reinterpret_cast<unsigned char*>(temp_buffer));
    data_[i] *= conversion_factor;
    // Exit if bad file
    if (!file.good())
    {
      clear();
      throw std::runtime_error("read8BitPGM(): Error while reading file.");
    }
  }

  // Done, close file
  file.close();
}

void Image::write8BitPGM(const char* file_name) const throw(std::runtime_error)
{
  std::ofstream file;
  unsigned char buffer[1];
  unsigned int i, size;

  // Open file
  file.open(file_name);
  if (!file.good())
  {
    throw std::runtime_error("write8BitPGM(): Failed to open file for writing.");
  }

  // Write the header
  file << "P5\n"
       << width_ << ' ' << height_ << '\n'
       << 255 << '\n';

  // Write data
  size = getArea();
  for (i = 0; i < size; i++)
  {
    *buffer = static_cast<unsigned char>(std::min(1.f, std::max(0.f, data_[i]))
					 * 255.f);
    file.write(reinterpret_cast<char*>(buffer), 1);
    if (!file.good())
    {
      throw std::runtime_error("write8BitPGM(): Failed to write data to file.");
    }
  }

  // Done, close file
  file.close();
}
