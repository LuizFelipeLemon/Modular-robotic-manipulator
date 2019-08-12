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

int Tx, Ty;

void CallBackFunc(int event, int x, int y, int flags, void* userdata) {
  if (event == cv::EVENT_LBUTTONDOWN) {
    cout << "Left button of the mouse is clicked - position {" << x << ", " << y
         << "}" << endl;
    Tx = x;
    Ty = y;
  }
}

int main() {
  Vision vision;
  vision.start();
  // TODO: removem /// comments
  ModularArm arm;
  arm.start("/dev/ttyUSB0");

  std::cerr << "entrando 180\n";
  arm.sendMove(200, 0);

  std::cout << "Criando a PSOM...\n";

  PSOM som(10);
  std::cout << "Treinando a PSOM...\n";
  std::string input_file = "data/braco_modular_arco.txt";
  std::string output_file = "output/braco_modular_arco_10_10000.csv";

  // som.train(input_file, output_file, 10000);
  som.load(output_file);
  // Treina uma som com dados em input file e salva em output file
  // Treina com 10000 iterações e maxFeatureInitialValue = 0.01
  std::cout << "PSOM Treinada\n Iniciando validação...\n";

  cv::Mat image;

  // std::vector<std::vector<int>> alvo;
  int joint[2] = {1, 2};
  double input[4];
  input[0] = 0;
  input[1] = 0;
  std::vector<double> output;
  int x[qtdTestes], y[qtdTestes];

  cv::namedWindow("Windown", 1);
  cv::setMouseCallback("Windown", CallBackFunc, NULL);

  while (true) {
    while (Tx == 0) {
      std::cout << "Waiting unitl point is set...\n";
      vision.inputVideo.grab();
      vision.inputVideo.retrieve(image);
      cv::imshow("Windown", image);
      cv::waitKey(100);
    }

    input[2] = Tx;
    input[3] = Ty;

    std::cout << ": Alvo (em pixels):  " << input[2] << " " << input[3]
              << std::endl;
    cv::circle(image, cv::Point(input[2], input[3]), 4, cv::Scalar(0, 0, 255),
               -1);  // <-- ALVO (Vermelho)
    // cv::imshow("window", image);
    // cv::waitKey(0);
    // int xMax, yMax;
    // double norma[4];
    // vision.getFrameSize(xMax, yMax);
    // som.normalize(input, xMax, yMax);
    // normalize(input, norma);

    som.bestResponse(input, output, 2, 3);
    std::cout << ": Angulos recuperados da SOM: " << output[0] << " "
              << output[1] << " X: " << output[2] << " y: " << output[3]
              << std::endl;

    cv::circle(image, cv::Point(output[2], output[3]), 4, cv::Scalar(255, 0, 0),
               2);  // <-- Ponto do mapa SOM(AZUL)
    // cv::imshow("Windown", image);
    // cv::waitKey(1);

    double sendMove[4];
    sendMove[0] = output[0];
    sendMove[1] = output[1];
    arm.sendMoveMulti(sendMove, joint, 2);
    std::cerr << "Terminei a Posicao 1\n";

    std::cerr << "Vamos começar a interpolação\n";
    // std::vector<double> outputInterpolado;
    // som.lagrangeInterpolation(output[4], output[5], output);
    /*
    int contador = 0;
    bool keep = true;
    do {
      keep = vision.getVisualPosition(Tx, Ty);
    } while (!keep);
    cv::waitKey(1);
    */

    // std::cout << "Terminei os while contador: " << contador;
    std::cout << ": Posição após movimento com os angulos acima: " << Tx << " "
              << Ty << std::endl;

    std::cout << ": Erro relativo: X: "
              << (abs(input[2] - Tx) / input[2]) * 100.0
              << "% Y:  " << (abs(input[3] - Ty) / input[3]) * 100.0 << "%"
              << std::endl;

    Tx = 0;
  }  // até aqui

  for (int i = 0; i < 5; i++) {
    vision.inputVideo.grab();
    vision.inputVideo.retrieve(image);
  }
  for (int i = 0; i < qtdTestes; i++) {
    // cv::circle(image, cv::Point(alvo[i][0], alvo[i][1]), 4,
    //           cv::Scalar(0, 0, 255), 2);  // <-- ALVO (Vermelho)
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