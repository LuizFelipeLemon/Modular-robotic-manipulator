#ifndef SOMMODULARARM_h
#define SOMMODULARARM_h

#define SOM_N_MAX 30
#define SOM_F_MAX 10
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

class SOMModulaArm {
 public:
  SOMModulaArm(std::vector<std::vector<std::vector<double> > > inputMatrix,
               int sizeOfSOM, int depthOfSOM, int inputMinIndex,
               int inputMaxIndex);

  SOMModulaArm(int sizeOfSOM, int depthOfSOM, int inputMinIndex,
               int inputMaxIndex, std::string file = "wheights.txt");

  void bestDistance(double features[SOM_F_MAX], int &index_best_l,
                    int &index_best_c);
  double parcialDistance(double features[SOM_F_MAX], int i, int j);
  void bestResponse(double targetFeatures[SOM_F_MAX],
                    double responseFeatures[SOM_F_MAX]);
  void load(std::string file);

 private:
  int som_n;  // Tamanho da matriz
  int som_f;  // Tamanho do vetor de caracteristicas (features)

  int input_min;
  int input_max;

  double neuralMatrix[SOM_N_MAX][SOM_N_MAX][SOM_F_MAX];
};

SOMModulaArm::SOMModulaArm(
    std::vector<std::vector<std::vector<double> > > inputMatrix, int sizeOfSOM,
    int depthOfSOM, int inputMinIndex, int inputMaxIndex) {
  som_n = sizeOfSOM;
  som_f = depthOfSOM;
  input_min = inputMinIndex;
  input_max = inputMaxIndex;
  for (int i = 0; i < som_n; i++) {
    for (int j = 0; j < som_n; j++) {
      for (int k = 0; k < som_f; k++) {
        neuralMatrix[i][j][k] = inputMatrix[i][j][k];
      }
    }
  }
}

SOMModulaArm::SOMModulaArm(int sizeOfSOM, int depthOfSOM, int inputMinIndex,
                           int inputMaxIndex, std::string file) {
  som_n = sizeOfSOM;
  som_f = depthOfSOM;
  input_min = inputMinIndex;
  input_max = inputMaxIndex;
}

double SOMModulaArm::parcialDistance(double features[SOM_F_MAX], int i, int j) {
  double soma = 0;
  for (int f = input_min; f <= input_max; f++) {
    soma += pow(features[f] - neuralMatrix[i][j][f], 2);
  }
  return sqrt(soma);
}

void SOMModulaArm::bestDistance(double features[SOM_F_MAX], int &index_best_l,
                                int &index_best_c) {
  index_best_l = 0;
  index_best_c = 0;
  float bestDistance = parcialDistance(features, index_best_l, index_best_c);
  for (int i = 0; i < som_n; i++) {
    for (int j = 0; j < som_n; j++) {
      float d = parcialDistance(features, i, j);
      // std::cout << "parcialDistance: " << d << " " << i << " " << j<<
      // std::endl;
      if (d < bestDistance) {
        index_best_l = i;
        index_best_c = j;
        bestDistance = d;
      }
    }
  }
  // std::cout << "BestDistance: " << bestDistance << " " << index_best_l << " "
  //<< index_best_c << std::endl;
}

void SOMModulaArm::bestResponse(double features[SOM_F_MAX],
                                double responseFeatures[SOM_F_MAX]) {
  int bestLine = 0;
  int bestColumn = 0;
  bestDistance(features, bestLine, bestColumn);
  // std::cout << "BestDistance: " << bestLine << " " << bestColumn <<
  // std::endl;
  for (int i = 0; i < som_f; i++) {
    responseFeatures[i] = neuralMatrix[bestLine][bestColumn][i];
    // std::cout << "BestDistance: " << responseFeatures[i] << std::endl;
  }
}

void SOMModulaArm::load(std::string file) {
  std::ifstream myfile(file);

  if (myfile.is_open()) {
    // myfile >> som_nr;
    // myfile >> som_fr;
    std::string line;
    std::getline(myfile, line);
    std::cout << line << '\n';
    int a;
    for (int i = 0; i < som_n; i++) {
      for (int j = 0; j < som_n; j++) {
        myfile >> a;
        myfile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        myfile >> a;

        for (int k = 0; k < som_f; k++) {
          myfile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
          myfile >> neuralMatrix[i][j][k];
          // std::cout << neuralMatrix[i][j][k] << " ";
        }
        // std::cout << "\n";
      }
      // std::cout << "\n";
    }
    // std::cout << "Carregado\n";

    myfile.close();
  }

  else
    std::cout << "Unable to open file";
}

#endif
