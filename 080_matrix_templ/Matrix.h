#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>


//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> >  rows;
 public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix & rhs);
  ~Matrix();
  Matrix & operator=(const Matrix & rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix & rhs) const;
  Matrix operator+(const Matrix & rhs) const;

  template<typename U>
    friend std::ostream & operator<<(std::ostream & s, const Matrix<U> & rhs);
};

template<typename T>
Matrix<T>::Matrix(): numRows(0), numColumns(0), rows(0){}

template<typename T>
Matrix<T>::Matrix(int r, int c): numRows(r), numColumns(c), rows(r){
  typename std::vector<std::vector<T> >::iterator it = rows.begin();
  while(it != rows.end()){
    (*it).resize(c);
    ++it;
  }
}

template<typename T>
Matrix<T>::Matrix(const Matrix & rhs): numRows(rhs.numRows),
                                       numColumns(rhs.numColumns),
                                       rows(rhs.rows){}
template<typename T>
Matrix<T>::~Matrix(){}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs){
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = rhs.rows;
  return *this;
}

template<typename T>
int Matrix<T>::getRows() const{
  return numRows;
}

template<typename T>
int Matrix<T>::getColumns() const{
  return numColumns;
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index){
  assert(index >= 0 && index < numRows);
  return rows[index];
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const{
  assert(index >= 0 && index < numRows);
  return rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const{
  if(numRows != rhs.numRows){
    return false;
  }
  if(numColumns != rhs.numColumns){
    return false;
  }
  if(rows != rhs.rows){
    return false;
  }
  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const{
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  Matrix<T> ans(rhs);
  //typename std::vector<std::vector<T> >::const_iterator rhs_it = rhs.rows.begin();
  typename std::vector<std::vector<T> >::const_iterator this_it = rows.begin();
  typename std::vector<std::vector<T> >::iterator ans_it = ans.rows.begin();
  while(ans_it != ans.rows.end()){
    typename std::vector<T>::const_iterator this_it_it = (*this_it).begin();
    typename std::vector<T>::iterator ans_it_it = (*ans_it).begin();
    // typename std::vector<T>::const_iterator rhs_it_it = (*rhs_it).begin();
    while(ans_it_it != (*ans_it).end()){
      *ans_it_it = *ans_it_it + *this_it_it;
      ++ans_it_it;
      ++this_it_it;
      //++rhs_it_it;
    }
    ++ans_it;
    ++this_it;
    //++rhs_it;
  }
  return ans;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> &rhs){
  s << "[ ";
  typename std::vector<std::vector<T> >::const_iterator it;
  for(it = rhs.rows.begin(); it != rhs.rows.end(); ++it){
    if(it != rhs.rows.begin()){
      s << ",\n";
    }
    s << "{";
    typename std::vector<T>::const_iterator it_it;
    for(it_it = (*it).begin();it_it != (*it).end(); ++it_it){
      if(it_it != (*it).begin()){
	s << ", ";
      }
      s << *it_it;
    }
    s << "}";
  }
  s << " ]";
  return s;
}
#endif
