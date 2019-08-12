#include <unistd.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "I-SOM.h"
#include "ModularArm.h"
#include "SOMBracoModular.h"
#include "Vision.h"

#define qtdTestes 4

int main() {
  Vision vision;
  vision.start();
  // TODO: removem /// comments
  ModularArm arm;
  arm.start("/dev/ttyUSB0");

  std::cerr << "entrando 180\n";
  // arm.sendMove(200, 0);

  std::cout << "Criando a PSOM...\n";

  I_SOM som(4);
  std::cout << "Lendo a PSOM...\n";
  std::string input_file = "data/braco_modular_arco_12_08.txt";
  std::string output_file = "output/braco_modular_arco_4_";

  som.train(input_file, output_file, 10000);
  // som.load(output_file);
  // Treina uma som com dados em input file e salva em output file
  // Treina com 10000 iterações e maxFeatureInitialValue = 0.01
  std::cout << "PSOM Treinada\n Iniciando validação...\n";

  return 0;
}