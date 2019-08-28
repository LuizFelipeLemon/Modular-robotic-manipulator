/*
 * File:   PSOM.h
 * Author: oriva
 *
 * Created on 25 de Fevereiro de 2015, 17:43
 */

#ifndef PSOM_H
#define PSOM_H

#include "SOM.h"

class PSOM : public SOM {
 public:
  PSOM();
  PSOM(const PSOM& orig);
  inline PSOM(int _sn) : SOM(_sn), halfSizeLocalPsom(1) {}
  // void initializeGuassianBell();
  // void initializeSimHexGaits();
  double lagrangeInterpolation(double si, double sj,
                               std::vector<double>& outVec);

  double lagrangeInterpolationAxis(double si, double sj,
                                   std::vector<double>& outVec);
  double luizInterpolation(double s1, double s2, std::vector<double>& outVec);

  void saveTrajectory(double sj, int nOutStates);

  virtual ~PSOM();

 private:
  double lagrangeFactor(double i, double x, double axesStart, double axesEnd);
  double lagrangeFactorx(double ai, double sv, double axesStart, double axesEnd,
                         double actualI1, double actualI2);
  double lagrangeFactory(double ai, double sv, double axesStart, double axesEnd,
                         double actualI1, double actualI2);

  int validateBorderLines(int center);
  int validateBorderColums(int center);

  double halfSizeLocalPsom;
  std::string outputFileName;
};

#endif /* PSOM_H */
