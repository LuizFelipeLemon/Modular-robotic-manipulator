/*
 * File:   Sample.h
 * Author: oriva
 *
 * Created on 10 de Outubro de 2014, 14:20
 */

#include <sstream>
#include <string>
#include <vector>

#ifndef SAMPLE_H
#define SAMPLE_H

class Sample {
  friend class Node;

 public:
  Sample();
  Sample(int s);
  Sample(std::vector<double> &info);
  Sample(std::vector<double> &info, std::string l);
  Sample(const Sample &orig);
  virtual ~Sample();

  Sample operator+(Sample &sIn);
  Sample operator-(Sample &sIn);
  Sample operator/(double d);

  double distance(Sample &sIn);
  std::string getClass();
  int getSize();
  void getFeatures(std::vector<double> &info);
  void getFeaturesRange(int iStart, int iEnd, std::vector<double> &info);
  double getFeature(int index);

  void putNormalNoise(double s);
  void print();

  void setFeatures(std::vector<double> &info);
  std::string toString();
  std::string toShortString();

 protected:
  std::vector<double> information;
  std::string label;
};

#endif /* SAMPLE_H */
