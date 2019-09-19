#include <unistd.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "I-SOM.h"
#include "ModularArm.h"
#include "SOMBracoModular.h"
#include "Vision.h"

using namespace std;

#define qtdTestes 20

int main() {
  Vision vision;
  vision.start();
  // TODO: removem /// comments
  ModularArm arm;
  arm.start("/dev/ttyUSB0");

  std::cerr << "entrando 180\n";
  arm.sendMove(200, 0);

  std::cout << "Criando a PSOM...\n";

  I_SOM som(6);
  std::cout << "Lendo a PSOM...\n";
  std::string input_file = "data/braco_modular_arco.txt";
  std::string output_file = "output/braco_modular_arco_6_10000.csv";
  std::cout << "Criando a PSOM..." << output_file << "\n";

  // som.train(input_file, output_file, 10000);
  som.load(output_file);
  // Treina uma som com dados em input file e salva em output file
  // Treina com 10000 iterações e maxFeatureInitialValue = 0.01
  std::cout << "PSOM Carregada\n Iniciando validação...\n";

  cv::Mat image;

  int alvo[qtdTestes][2] = {{314, 176}, {300, 207}, {325, 207}, {286, 237},
                            {310, 235}, {333, 239}, {266, 262}, {294, 260},
                            {321, 264}, {274, 288}, {311, 289}, {336, 291},
                            {267, 319}, {308, 317}, {337, 326}, {262, 357},
                            {302, 356}, {249, 392}, {290, 380}, {321, 372}};
  int joint[2] = {1, 2};
  double input[4];
  input[0] = 0;
  input[1] = 0;
  std::vector<double> output;
  int x[qtdTestes], y[qtdTestes];
  for (int i = 0; i < qtdTestes; i++) {
    input[2] = (double)alvo[i][0];
    input[3] = (double)alvo[i][1];

    som.bestResponse(input, output, 2, 3);

    // som.interpolate(input, output);

    // cout << "FIM\n";

    // std::cout << i + 1 << ": Angulos recuperados da SOM: " << output[0] << "
    // "
    //         << output[1] << std::endl;

    double sendMove[4];
    sendMove[0] = output[0];
    sendMove[1] = output[1];
    arm.sendMoveMulti(sendMove, joint, 2);
    // std::cerr << "Terminei a Posicao\n";

    int contador = 0;

    bool keep = true;
    do {
      keep = vision.getVisualPosition(x[i], y[i]);
    } while (!keep);

    std::cout << i + 1 << ": Alvo (em pixels):  " << input[2] << " " << input[3]
              << std::endl;
    std::cout << i + 1
              << ": Posição após movimento com os angulos acima: " << x[i]
              << " " << y[i] << std::endl;

    std::cout << i + 1 << ": Erro relativo: X: "
              << (abs(input[2] - x[i]) / input[2]) * 100.0
              << "% Y:  " << (abs(input[3] - y[i]) / input[3]) * 100.0 << "%"
              << std::endl;
  }

  for (int i = 0; i < 5; i++) {
    vision.inputVideo.grab();
    vision.inputVideo.retrieve(image);
  }
  for (int i = 0; i < qtdTestes; i++) {
    cv::circle(image, cv::Point(alvo[i][0], alvo[i][1]), 4,
               cv::Scalar(0, 0, 255), -1);  // <-- ALVO (Vermelho)
    cv::circle(image, cv::Point(x[i], y[i]), 4, cv::Scalar(255, 0, 0),
               -1);  // <-- TIRO (Azul)

    // cv::putText(image, std::to_string(i), cv::Point(alvo[i][0], alvo[i][1]),
    // CV_FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(255, 0, 0));
  }

  for (int i = 0; i < som.getSizeNetwork(); i++) {
    for (int j = 0; j < som.getSizeNetwork(); j++) {
      std::vector<double> w;
      som.getNodeFeatures(j, i, w);
      cv::circle(image, cv::Point(w[2], w[3]), 1, cv::Scalar(0, 255, 0), -1);

      // std::cout << w[2] << "," << w[3] << '\n';
      cv::imshow("Windown", image);
      // cv::waitKey(0);
    }
  }

  cv::imshow("Windown", image);
  cv::waitKey(0);
  cv::String diretorioImag = cv::String("coleta2.png");
  std::cout << "Salvando...\n" << cv::imwrite(diretorioImag, image);
  std::cout << "Terminei...\n";
  return 0;
}