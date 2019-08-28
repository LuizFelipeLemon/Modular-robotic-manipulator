/*
 * File:   SOM.h
 * Author: oriva
 *
 * Created on 15 de Março de 2014, 12:21
 */

#ifndef SOM_H
#define SOM_H

#include <string>
#include "DataSet.h"
#include "Node.h"

#define SOM_MAX_SIZE 100

class SOM {
 public:
  SOM(int _sn = 12);

  ~SOM();

  double compareRange(int x, int y, int iStart, int iEnd,
                      std::vector<double> &info);

  double distancePos(int aX, int aY, int bX, int bY);
  double distanceVector(std::vector<double> &infoA, std::vector<double> &infoB);
  void executeOneIt();
  void execute();

  void enableNodes();
  double findWinner(Sample *s, int &i, int &j);
  void getNodeFeatures(int i, int j, std::vector<double> &info);
  int getSizeNetwork() const;

  void labelingPhase();
  void labelingPhaseII();
  void labelingPhaseWithNeighbor();

  void printMitrixFormat();
  void printLabelsMitrixFormat();
  void printNodes(bool showTerminal = false);
  void saveNodes(std::string fileName, std::string fileHeader,
                 bool showTerminal);
  void saveToTxtFile(std::string fileName, bool showTerminal = true);

  void setDataSet(DataSet *dataSet);
  void setSizeNetwork(int sizeNetwork);
  void showLabels();
  void showWinnerDistances();

  void initializeNodes(int sizeNodes = 2, bool positivesValues = false,
                       double intensity = 20);

  void load(std::string fileName);                    
                       
  int updateWeight(Sample *s, int iWin, int jWin);
  void updateLabel(std::string l, int iWin, int jWin);
  void updateLabels(Sample *s);

  // Alterações de Luiz

  Node getNode(int i, int j);
  void train(std::string input_file, std::string output_file,
             int iterations = 10000, float maxFeatureInitialValue = 0.01);

  // Encontra o neurônio vencedor a partir de distância Euclidiana.
  // O intervalo de coordenadads que será verificado pode ser alterado mudando
  // inputMinIndex ou inputMaxIndex
  void bestResponse(double features[], std::vector<double> &responseFeatures,
                    int inputMinIndex = 0, int inputMaxIndex = -1);

  // \\Alterações de Luiz

 private:
  int validatePos(int pos);
  // armazena os nodos da rede
  Node nodes[SOM_MAX_SIZE][SOM_MAX_SIZE];

  int sizeNetwork;
  int currentIt;
  Sample *currentSample;
  double learningRate;
  double minLearningRate;
  double alpha;  ///< Taxa de aprendizagem atual
  double sigma;  ///< Determinar a largura da função de vizinhaça

  int maxIteration;

  DataSet *dataSet;
  int epoch;
  int maxEpoch;

  bool debug;

  // Alterações de Luiz

  void bestDistance(double features[], int &index_best_l, int &index_best_c,
                    int inputMinIndex = 0, int inputMaxIndex = -1);
  double parcialDistance(double features[], int i, int j, int inputMinIndex = 0,
                         int inputMaxIndex = -1);

  // \\ Alterações de Luiz
};

#endif /* SOM_H */
