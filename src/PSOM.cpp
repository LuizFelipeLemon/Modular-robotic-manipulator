/*
 * File:   PSOM.cpp
 * Author: oriva
 *
 * Created on 25 de Fevereiro de 2015, 17:43
 */

#include "PSOM.h"

#include "utils.h"

PSOM::PSOM() {
  halfSizeLocalPsom = 1;
  outputFileName = "/tmp/trajectory_hex_psom.dat";
}

PSOM::PSOM(const PSOM& orig) {}

double PSOM::lagrangeFactor(double ai, double sv, double axesStart,
                            double axesEnd) {
  double prod = 1;
  for (double aj = axesStart; aj <= axesEnd; aj = aj + 1) {
    if (ai != aj) prod = prod * ((sv - aj) / (ai - aj));
  }
  return prod;
}

int PSOM::validateBorderLines(int center) {
  if (center + halfSizeLocalPsom > getSizeNetwork() - 1)
    center = getSizeNetwork() - 1 - halfSizeLocalPsom;
  if (center - halfSizeLocalPsom < 0) center = halfSizeLocalPsom;
  return center;
}

int PSOM::validateBorderColums(int center) {
  if (center + halfSizeLocalPsom > getSizeNetwork() - 1)
    center = getSizeNetwork() - 1 - halfSizeLocalPsom;
  if (center - halfSizeLocalPsom < 0) center = halfSizeLocalPsom;
  return center;
}
/**
 * Interpolaçao local do metodo de Lagrange para duas dimensoes
 * @param s1 posição na dimensão 1 da superficie manifold S
 * @param s2 posição na dimensão 2 da superficie manifold S
 * @param wDim dimensao do dos pesos da rede (saída da interpolação)
 * @return
 */
// TODO colocar uma validaçao para o acesso das posiçoes i j da grade SOM
double PSOM::lagrangeInterpolation(double s1, double s2,
                                   std::vector<double>& outVec) {
  int wDim = outVec.size() - 2;
  // zera vetor
  for (int i = 0; i < wDim; i++) outVec[i] = 0;
  // std::cout << "S1: " << s1 << " s2: " << s2 << "\n";
  std::vector<double> w;

  int center1 = validateBorderLines(int(s1));
  int center2 = validateBorderColums(int(s2));
  int axesStartI1 = center1 - halfSizeLocalPsom;
  int axesEndI1 = center1 + halfSizeLocalPsom;
  int axesStartI2 = center2 - halfSizeLocalPsom;
  int axesEndI2 = center2 + halfSizeLocalPsom;

  for (int i1 = axesStartI1; i1 <= axesEndI1; i1++) {
    for (int i2 = axesStartI2; i2 <= axesEndI2; i2++) {
      getNodeFeatures(i1, i2, w);
      // cout << " " << w[0] << " " <<w[1]<< " " <<w[2] << " "<<w[3]<<'\n';
      for (int wi = 0; wi < wDim; wi++) {
        outVec[wi] = outVec[wi] +
                     w[wi] * lagrangeFactor(i1, s1, axesStartI1, axesEndI1) *
                         lagrangeFactor(i2, s2, axesStartI2, axesEndI2);
        cout << " " << outVec[wi] << " + " << w[wi] << " * "
             << lagrangeFactor(i1, s1, axesStartI1, axesEndI1) << " * "
             << lagrangeFactor(i2, s2, axesStartI2, axesEndI2)
        << "\n";
      }
    }
  }
  for (int wi = 0; wi < wDim; wi++) cout << " " << outVec[wi];
  cout << endl;
  return 0;
}

void PSOM::saveTrajectory(double sj, int nOutStates) {
  int sizeState = 12;
  std::vector<double> outVec(sizeState, 0);
  lagrangeInterpolation(0, sj, outVec);

  ofstream file(outputFileName.c_str());
  file << "# name: data" << endl;
  file << "# type: matrix " << endl;
  file << "# rows: " << nOutStates << endl;
  file << "# columns: " << sizeState << endl;

  double incSi = double(getSizeNetwork()) / double(nOutStates);
  for (double si = 0; si < getSizeNetwork(); si = si + incSi) {
    lagrangeInterpolation(si, sj, outVec);
    for (int j = 0; j < sizeState; j++) {
      file << outVec[j] << " ";
    }
    file << endl;
  }

  file.close();
}

PSOM::~PSOM() {}
