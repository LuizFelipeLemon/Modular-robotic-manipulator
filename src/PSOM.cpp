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

double PSOM::lagrangeFactorx(double xi, double x, double axesStart,
                             double axesEnd, double actualI1, double actualI2) {
  double prod = 1;
  std::vector<double> w;
  std::cout << "Interpolacao em X!\n";
  for (double xj = axesStart; xj <= axesEnd; xj = xj + 1) {
    if (actualI1 != xj) {
      getNodeFeatures(xj, actualI2, w);  // retira de elementos na Horizontal
      prod = prod * ((x - w[2]) /
                     (xi - w[2]));  // Termos do produtorio estao em funcao de X
      std::cout << x << " - " << w[2] << " / " << xi << " - " << w[2]
                << std::endl;
    }
  }
  std::cout << "Prod: " << prod << '\n';
  return prod;
}

double PSOM::lagrangeFactory(double xi, double x, double axesStart,
                             double axesEnd, double actualI1, double actualI2) {
  double prod = 1;
  std::vector<double> w;

  std::cout << "Interpolacao em Y!\n";
  for (double xj = axesStart; xj <= axesEnd; xj = xj + 1) {
    if (actualI2 != xj) {
      getNodeFeatures(actualI1, xj, w);  // retira de elementos na vertical
      prod = prod * ((x - w[3]) /
                     (xi - w[3]));  // Termos do produtorio estao em funcao de Y
      std::cout << x << " - " << w[3] << " / " << xi << " - " << w[3]
                << std::endl;
    }
  }
  std::cout << "Prod: " << prod << '\n';
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
             << lagrangeFactor(i2, s2, axesStartI2, axesEndI2) << "\n";
      }
    }
  }
  for (int wi = 0; wi < wDim; wi++) cout << " " << outVec[wi];
  cout << endl;
  return 0;
}

// Recebe o ponto desejado na imagem,
// e interpola baseando apenas nas coordenadas do Knot
double PSOM::lagrangeInterpolationAxis(double s1, double s2,
                                       std::vector<double>& outVec) {
  // std::vector<double> output;
  double input[4];
  input[0] = 0;
  input[1] = 0;
  input[2] = s1;
  input[3] = s2;

  bestResponse(input, outVec, 2, 3);
  std::cout << input[2] << "," << input[3] << " ~ " << outVec[2] << ","
            << outVec[3] << "\n";

  int wDim = outVec.size() - 2;
  std::cout << "wDIm:" << wDim << '\n';

  // std::cout << "S1: " << s1 << " s2: " << s2 << "\n";
  std::vector<double> w;
  std::cout << "Center:" << outVec[4] << "," << outVec[5] << "\n";
  int center1 = validateBorderLines(outVec[4]);
  int center2 = validateBorderColums(outVec[5]);
  int axesStartI1 = center1 - halfSizeLocalPsom;
  int axesEndI1 = center1 + halfSizeLocalPsom;
  int axesStartI2 = center2 - halfSizeLocalPsom;
  int axesEndI2 = center2 + halfSizeLocalPsom;
  // zera vetor
  std::cout << "Zerando...\n";
  for (int i = 0; i < outVec.size(); i++) {
    outVec[i] = 0;
    // std::cout<<outVec[i];
  }

  for (int i1 = axesStartI1; i1 <= axesEndI1; i1++) {
    for (int i2 = axesStartI2; i2 <= axesEndI2; i2++) {
      getNodeFeatures(i1, i2, w);
      cout << "#####################################################" << w[0]
           << " " << w[1] << " " << w[2] << " " << w[3] << '\n';
      for (int wi = 0; wi < wDim; wi++) {
        double a = lagrangeFactorx(w[2], s1, axesStartI1, axesEndI1, i1, i2);
        double b = lagrangeFactory(w[3], s2, axesStartI2, axesEndI2, i1, i2);
        std::cout << "\n[" << outVec[wi] << " + " << w[wi] << "*" << a << "*"
                  << b << "]\n";  //

        outVec[wi] = outVec[wi] + w[wi] * a * b;

        /*
        cout << " " << outVec[wi] << " + " << w[wi] << " * "
             << lagrangeFactor(i1, s1, axesStartI1, axesEndI1) << " * "
             << lagrangeFactor(i2, s2, axesStartI2, axesEndI2)
        << "\n";*/
      }

      std::cout << std::endl;
      cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << outVec[0]
           << " " << outVec[1] << " " << outVec[2] << " " << outVec[3] << '\n';
    }
  }

  std::cout << "**********************************************\n";
  std::cout << "Start: " << outVec[2] << "," << outVec[3] << "(" << outVec[4]
            << "," << outVec[5] << ")"
            << " Goal:" << s1 << "," << s2 << '\n';
  for (int wi = 0; wi < 6; wi++) {
    std::cout << "1 " << outVec[wi];
    std::cout << endl;
  }

  return 0;
}

/**
 * Interpolaçao local do metodo de Lagrange para duas dimensoes
 * @param s1 posição X desejada na imagem
 * @param s2 posição Y desejada na imagem
 * @param wDim dimensao do dos pesos da rede (saída da interpolação)
 * @return
 */
// TODO colocar uma validaçao para o acesso das posiçoes i j da grade SOM
double PSOM::luizInterpolation(double s1, double s2,
                               std::vector<double>& output) {
  double input[4];
  input[0] = 0;
  input[1] = 0;
  input[2] = s1;
  input[3] = s2;

  // std::vector<double> output;
  bestResponse(input, output, 2, 3);
  cout << "Vencedor: (" << output[4] << "," << output[5] << ") <-> (" << s1
       << "," << s2 << ")\n";

  int wDim = output.size() - 2;

  // std::cout << "S1: " << s1 << " s2: " << s2 << "\n";
  std::vector<double> w;

  int center1 = validateBorderLines(output[4]);
  int center2 = validateBorderColums(output[5]);
  int axesStartI1 = center1 - halfSizeLocalPsom;
  int axesEndI1 = center1 + halfSizeLocalPsom;
  int axesStartI2 = center2 - halfSizeLocalPsom;
  int axesEndI2 = center2 + halfSizeLocalPsom;

  // zera vetor
  for (int i = 0; i < wDim; i++) output[i] = 0;

  cout << axesStartI1 << " ~ " << center1 << " ~ " << axesEndI1 << '\n';
  cout << axesStartI2 << " ~ " << center2 << " ~ " << axesEndI2 << '\n';

  for (int i1 = axesStartI1; i1 <= axesEndI1; i1++) {
    for (int i2 = axesStartI2; i2 <= axesEndI2; i2++) {
      // cout << "\n___________________________________\n";
      // cout << "             " << i1 << " | " << i2 << "";
      // << "\n___________________________________  \n";

      getNodeFeatures(i1, i2, w);
      // cerr << " " << w[0] << " " << w[1] << " " << w[2] << " " << w[3];

      double Lx = 1;
      for (int in1 = axesStartI1; in1 <= axesEndI1; in1++) {
        for (int in2 = axesStartI2; in2 <= axesEndI2; in2++) {
          std::vector<double> feat;
          getNodeFeatures(in1, in2, feat);
          if (!(in1 == i1 && in2 == i2)) {
            // cout << i1 << " " << in1 << " | " << i2 << " " << in2 << '\n';
            // cout << "Lx => " << Lx << " = ((" << s1 << " - " << feat[2]
            //     << " ) / (" << w[2] << " - " << feat[2] << " ))";
            Lx = Lx * ((s1 - feat[2]) / (w[2] - feat[2]));
            // cout << " = " << Lx << '\n';
          }
        }
      }
      // cout << "\n\n********************************\n\n";
      double Ly = 1;
      for (int in1 = axesStartI1; in1 <= axesEndI1; in1++) {
        for (int in2 = axesStartI2; in2 <= axesEndI2; in2++) {
          std::vector<double> feat;
          getNodeFeatures(in1, in2, feat);
          if (!(in1 == i1 && in2 == i2)) {
            // cout << i1 << " " << in1 << " | " << i2 << " " << in2 << '\n';

            // cout << "Ly => " << Ly << " = ((" << s2 << " - " << feat[3]
            //     << " ) / (" << w[3] << " - " << feat[3] << " ))";
            Ly = Ly * ((s2 - feat[3]) / (w[3] - feat[3]));
            // cout << " = " << Ly << '\n';
          }
        }
      }
      cerr << "\n\n " << output[0] << " + " << w[0] << " * " << Lx << " * "
           << Ly << "\n\n";
      output[0] = output[0] + w[0] * Lx * Ly;
    }
  }

  cout << "Terminei a interpolação:\n";

  cout << " " << output[0];
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
