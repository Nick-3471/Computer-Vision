#ifndef MATRIX_HPP_
#define MATRIX_HPP_
#include <iostream>
#include <stdexcept>
extern "C" void solve_system(int, int, float**, float*, float*);

class Matrix
{
public:
  static Matrix solveWithSVD(const Matrix &A, const Matrix &b)
    throw(std::logic_error);

  Matrix();
  Matrix(const Matrix &src);
  ~Matrix();

  Matrix& operator=(const Matrix &rhs);
  unsigned int getM() const;
  unsigned int getN() const;
  void resize(unsigned int m, unsigned int n, float fill);
  float& at(unsigned int row_num, unsigned int col_num)
                                                  throw(std::out_of_range);
  float get(unsigned int row_num, unsigned int col_num) const
                                                    throw(std::out_of_range);
  void print() const;
private:
  void dealloc();
  unsigned int m_, n_;
  float **data_;
};

#endif // MATRIX_HPP_
