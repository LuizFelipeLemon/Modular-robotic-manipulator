/*
 * File:   I-SOM.h
 * Author: luizfelipelemon
 * basede on oriva SOM code
 *
 * Created on 09 de Agosto de 2019, 17:43
 */

#ifndef I_SOMH
#define I_SOMH

#include "SOM.h"
#include "matrix.h"

struct Tuple {
  double dist;
  int i, j;
};

class I_SOM : public SOM {
 public:
  I_SOM() : A(6, 6), b1(6, 1), b2(6, 1), a1(6, 1), a2(6, 1) {}
  I_SOM(const I_SOM& orig) : A(6, 6), b1(6, 1), b2(6, 1), a1(6, 1), a2(6, 1) {}
  inline I_SOM(int _sn)
      : SOM(_sn), A(6, 6), b1(6, 1), b2(6, 1), a1(6, 1), a2(6, 1) {}

  void best6(double features[], int inputMinIndex, int inputMaxIndex,
             std::vector<Tuple>& final);
  virtual ~I_SOM();

  void invert();
  void populateM(std::vector<Tuple> output);
  void coef(double x, double y, double coef[]);
  double interpolate(double features[], std::vector<Tuple>& final);
  double z(double x, double y, Matrix<double>& a);

 private:
  double M[6][6];
  Matrix<double> A, b1, b2, a1, a2;
};

#endif /* I_SOM */
