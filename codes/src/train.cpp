#include <unistd.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "ModularArm.h"
#include "PSOM.h"
#include "SOMBracoModular.h"
//#include "Vision.h"

#define qtdTestes 4

int main() {
  // Vision vision;
  // vision.start();
  // TODO: removem /// comments
  // ModularArm arm;
  // arm.start("/dev/ttyUSB0");

  std::cerr << "entrando 180\n";
  // arm.sendMove(200, 0);

  std::cout << "Criando a PSOM...\n";

  PSOM som(15);
  std::cout << "Lendo a PSOM...\n";
  std::string input_file = "data/braco_3d_11dez.txt";
  std::string output_file = "codes/output/braco_3d_11dez_";

  som.train(input_file, output_file, 10000);
  // som.load(output_file);
  // Treina uma som com dados em input file e salva em output file
  // Treina com 10000 iterações e maxFeatureInitialValue = 0.01
  std::cout << "PSOM Treinada\n ";

  return 0;
}