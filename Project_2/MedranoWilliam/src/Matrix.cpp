#include "Matrix.hpp"

Matrix Matrix::solveWithSVD(const Matrix &A, const Matrix &b)
  throw(std::logic_error)
{
  Matrix x;
  float *x_ptr, *b_ptr;
  unsigned int i;

  // Check dimensions
  if (A.getN() != b.getM() || b.getN() != 1)
  {
    throw
      std::logic_error("solveWithSVD(): Can't solve system with given dimensions.");
  }

  // Format b and x arrays
  b_ptr = new float[b.getM()+1];
  b_ptr[0] = 0.f;
  for (i = 1; i <= b.getM(); i++)
  {
    b_ptr[i] = b.get(i, 1);
  }
  x_ptr = new float[b.getM()+1];

  // Solve
  solve_system(A.m_, A.n_, A.data_, x_ptr, b_ptr);

  // Delete b
  delete []b_ptr;

  // Format x
  x.resize(b.getM(), 1, 0.f);
  for (i = 1; i <= b.getM(); i++)
  {
    x.at(i, 1) = x_ptr[i];
  }
  delete []x_ptr;

  return x;
}

Matrix::Matrix()
  : m_(0), n_(0), data_(NULL)
{
  unsigned int i;

  data_ = new float*[m_+1];
  for (i = 0; i < m_+1; i++)
  {
    data_[i] = new float[n_+1];
  }
}

Matrix::Matrix(const Matrix &src)
  : m_(0), n_(0), data_(NULL)
{
  *this = src;
}

Matrix::~Matrix()
{
  dealloc();
}

Matrix& Matrix::operator=(const Matrix &rhs)
{
  unsigned int i, j, size;

  // Check reference
  if (this == &rhs)
  {
    return *this;
  }

  // Reallocate memory
  dealloc();
  m_ = rhs.m_;
  n_ = rhs.n_;
  data_ = new float*[m_+1];
  for (j = 0; j < m_+1; j++)
  {
    data_[j] = new float[n_+1];
  }

  // Copy over memory
  for (j = 1; j <= m_; j++)
  {
    for (i = 1; i <= n_; i++)
    {
      at(j, i) = rhs.get(j, i);
    }
  }

  // Done
  return *this;
}

unsigned int Matrix::getM() const
{
  return m_;
}

unsigned int Matrix::getN() const
{
  return n_;
}

void Matrix::resize(unsigned int m, unsigned int n, float fill)
{
  unsigned int i, j;

  // Reallocate memory
  dealloc();
  m_ = m;
  n_ = n;
  data_ = new float*[m_+1];
  for (j = 0; j < m_+1; j++)
  {
    data_[j] = new float[n_+1];
    for (i = 0; i < n_+1; i++)
    {
      if (i > 0 && j > 0)
      {
	at(j, i) = fill;
      }
    }
  }
}

float& Matrix::at(unsigned int row_num, unsigned int col_num)
  throw(std::out_of_range)
{
  // Check range
  if (row_num == 0 || col_num == 0 || row_num > m_ || col_num > n_)
  {
    throw std::out_of_range("at(): row and col are not in range.");
  }

  // Return value
  return (data_[row_num])[col_num];
}

float Matrix::get(unsigned int row_num, unsigned int col_num)
  const throw(std::out_of_range)
{
  // Check range
  if (row_num == 0 || col_num == 0 || row_num > m_ || col_num > n_)
  {
    throw std::out_of_range("get(): row and col are not in range.");
  }

  // Get value
  return (data_[row_num])[col_num];
}

void Matrix::dealloc()
{
  unsigned int i;
  for (i = 0; i < m_+1; i++)
  {
    delete [](data_[i]);
  }
  delete []data_;
}

void Matrix::print() const
{
  unsigned int i, j;
  for (j = 1; j <= m_; j++)
  {
    for (i = 1; i <= n_; i++)
    {
      std::cout << get(j, i) << "    ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
