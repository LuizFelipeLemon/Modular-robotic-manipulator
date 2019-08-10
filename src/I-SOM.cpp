/*
 * File:   I-SOM.cpp
 * Author: luizfelipelemon
 * basede on oriva SOM code
 *
 * Created on 09 de Agosto de 2019, 17:43
 *
 */

#include "I-SOM.h"
#include <cmath>
#include "utils.h"

I_SOM::~I_SOM() {}

void I_SOM::best6(double features[], int inputMinIndex, int inputMaxIndex,
                  std::vector<Tuple> &final) {
  vector<Tuple> dist;
  for (int i = 0; i < getSizeNetwork(); i++) {
    for (int j = 0; j < getSizeNetwork(); j++) {
      float d = parcialDistance(features, i, j, inputMinIndex, inputMaxIndex);
      dist.push_back(Tuple{d, i, j});
    }
  }
  sort(dist.begin(), dist.end(),
       [&](const Tuple &A, const Tuple &B) { return A.dist < B.dist; });

  for (int i = 0; i < 6; i++) {
    final.push_back(dist[i]);
  }
  for (int i = 0; i < final.size(); i++) {
    cout << final[i].dist << "  " << final[i].i << " " << final[i].j << '\n';
  }
}

void I_SOM::coef(double x, double y, double coef[]) {
  // double s[6];
  coef[0] = pow(x, 2);
  coef[1] = x * y;
  coef[2] = pow(y, 2);
  coef[3] = x;
  coef[4] = y;
  coef[5] = 1;
  // cout << "Coef: " << coef[0] << "  " << coef[1] << "  " << coef[2] << "  "
  //     << coef[3] << "  " << coef[4] << "  " << coef[5] << "  " << '\n';
}
void I_SOM::populateM(std::vector<Tuple> output) {
  for (int lin = 0; lin < output.size(); lin++) {
    std::vector<double> w;
    getNodeFeatures(output[lin].i, output[lin].j, w);
    cout << "X: " << w[0] << "  Y: " << w[1] << "  "
         << "teta1: " << w[2] << "  teta2: " << w[3] << "  " << lin << "\n";
    double alfas[6];
    // cerr << "put1 \n";
    b1.put(lin, 0, w[2]);
    // cerr << "put2\n";
    b2.put(lin, 0, w[3]);
    // cerr << "put2\n";
    coef(w[0], w[1], alfas);  //    calcula os coeficientes da função do
                              //    paraboloide para o ponto w[0],w[1]

    for (int col = 0; col < 6; col++) {
      A.put(lin, col, alfas[col]);
    };
  }
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      cout << A.get(i, j) << " , ";
    }
    cout << " * " << b1.get(i, 0) << " * " << b2.get(i, 0);

    cout << ";\n";
  }
}

void I_SOM::invert() {
  cout << "\n\n";
  A.invert();
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      cout << A.get(i, j) << " , ";
    }
    cout << '\n';
  }
}

double I_SOM::z(double x, double y, Matrix<double> &a) {
  double z = a.get(0, 0) * pow(x, 2) + a.get(1, 0) * x * y +
             a.get(2, 0) * pow(y, 2) + a.get(3, 0) * x + a.get(4, 0) * y +
             a.get(5, 0);
  return z;
}

double I_SOM::interpolate(double features[], std::vector<Tuple> &final) {
  std::vector<Tuple> output;
  best6(features, 2, 3, output);  // Pega os 6 pontos mais próximos
  populateM(output);              // Popula a matrix M de coeficientes
  invert();
  a1 = A * (b1 * -1);
  a2 = A * (b2 * -1);
  cout << "COEFICIENTS:\n";
  for (int i = 0; i < 6; i++)
    cout << a1.get(i, 0) << " | " << a2.get(i, 0) << '\n';

  cout << "Vamos calcular para o ponto : (" << features[2] << " , "
       << features[3] << ")\n";
  double teta1 = z(features[2], features[3], a1);
  double teta2 = z(features[2], features[3], a2);

  cout << "Teta1: " << teta1 << " Teta2: " << teta2 << '\n';

  /*

  */
}