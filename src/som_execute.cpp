#include <unistd.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "ModularArm.h"
#include "PSOM.h"
#include "SOMBracoModular.h"
#include "Vision.h"

using namespace std;

#define qtdTestes 4

int main() {
  Vision vision;
  vision.start();
  // TODO: removem /// comments
  //ModularArm arm;
  //arm.start("/dev/ttyUSB0");

  std::cerr << "entrando 180\n";
  //arm.sendMove(195, 0);

  std::cout << "Criando a PSOM...\n";

  PSOM som(15);
  std::cout << "Treinando a PSOM...\n";
  std::string input_file = "data/braco_modular_arco.txt";
  std::string output_file = "output/braco_modular_arco2_";

  som.train(input_file, output_file, 10000);
  // Treina uma som com dados em input file e salva em output file
  // Treina com 10000 iterações e maxFeatureInitialValue = 0.01
  std::cout << "PSOM Treinada\n Iniciando validação...\n";

  cv::Mat image;

  int alvo[qtdTestes][2] = {{450, 265}, {440, 300}, {395, 400}, {470, 320}};
  int joint[2] = {1, 2};
  double input[4];
  input[0] = 0;
  input[1] = 0;
  std::vector<double> output;
  int x[qtdTestes], y[qtdTestes];
  for (int i = 0; i < qtdTestes; i++) {
    input[2] = (double)alvo[i][0];
    input[3] = (double)alvo[i][1];
    std::cout << i + 1 << ": Alvo (em pixels):  " << input[2] << " " << input[3]
              << std::endl;
    // int xMax, yMax;
    // double norma[4];
    // vision.getFrameSize(xMax, yMax);
    // som.normalize(input, xMax, yMax);
    // normalize(input, norma);

    som.bestResponse(input, output, 2, 3);
    std::cout << i + 1 << ": Angulos recuperados da SOM: " << output[0] << " "
              << output[1] << " X: " << output[4] << " y: " << output[5]
              << std::endl;

    double sendMove[4];
    sendMove[0] = output[0];
    sendMove[1] = output[1];
    //arm.sendMoveMulti(sendMove, joint, 2);
    std::cerr << "Terminei a Posicao 1\n";

    std::cerr << "Vamos começar a interpolação\n";
    // std::vector<double> outputInterpolado;
    som.lagrangeInterpolation(output[4], output[5], output);

    int contador = 0;
    bool keep = true;
    do {
      keep = vision.getVisualPosition(x[i], y[i]);
    } while (!keep);

    std::cout << "Terminei os while contador: " << contador;
    std::cout << i + 1
              << ": Posição após movimento com os angulos acima: " << x[i]
              << " " << y[i] << std::endl;

    std::cout << i + 1 << ": Erro relativo: X: "
              << (abs(input[2] - x[i]) / input[2]) * 100.0
              << "% Y:  " << (abs(input[3] - y[i]) / input[3]) * 100.0 << "%"
              << std::endl
              << std::endl;
  }

  for (int i = 0; i < 5; i++) {
    vision.inputVideo.grab();
    vision.inputVideo.retrieve(image);
  }
  for (int i = 0; i < qtdTestes; i++) {
    cv::circle(image, cv::Point(alvo[i][0], alvo[i][1]), 4,
               cv::Scalar(0, 0, 255), 2);  // <-- ALVO (Vermelho)
    cv::circle(image, cv::Point(x[i], y[i]), 4, cv::Scalar(255, 0, 0),
               4);  // <-- TIRO (Azul)

    // cv::putText(image, std::to_string(i), cv::Point(alvo[i][0], alvo[i][1]),
    // CV_FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(255, 0, 0));
  }
  cv::imshow("Windown", image);
  cv::waitKey(0);
  cv::String diretorioImag = cv::String("coleta2.jpg");
  std::cout << "Salvando...\n" << cv::imwrite(diretorioImag, image);
  std::cout << "Terminei...\n";
  return 0;
}