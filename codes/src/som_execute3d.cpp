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
  arm.sendMove(0, 0);

  std::cout << "Criando a PSOM...\n";

  I_SOM som(15);
  std::cout << "Lendo a PSOM...\n";
  std::string input_file = "data/braco_modular_arco.txt";
  std::string output_file = "codes/output/braco_3d_11dez_10000.csv";
  std::cout << "Criando a PSOM..." << output_file << "\n";

  // som.train(input_file, output_file, 10000);
  som.load(output_file);
  // Treina uma som com dados em input file e salva em output file
  // Treina com 10000 iterações e maxFeatureInitialValue = 0.01
  std::cout << "PSOM Carregada\n Iniciando validação...\n";

  cv::Mat image;

  double alvo[qtdTestes][3] = {
      {0.1038211, -0.1008457, 0.4446939}, {0.1722064, 0.0853333, 0.7636762},
      {0.1481388, -0.051793, 0.5839989},  {0.131215, 0.0850139, 0.052961},
      {0.0873725, -0.2903105, 0.4761036}, {0.1824287, -0.0120831, 0.2737403},
      {0.1229295, -0.1467716, 0.2344627}, {0.2572403, -0.0678864, 0.5014562},
      {0.0283443, 0.0300868, 0.1338054},  {0.1429883, -0.2846453, 0.4917227},
      {0.0859707, 0.0195264, 0.5398545},  {0.1254455, 0.0586913, 0.2898789},
      {0.0903392, -0.0845087, 0.0689486}, {0.0503962, -0.0827391, 0.423703},
      {0.2205646, 0.0147875, 0.3329464},  {0.0723499, -0.2875817, 0.2244556},
      {0.0462433, -0.0873477, 0.4157622}, {0.1963275, -0.2604797, 0.3559841},
      {0.0569684, -0.0202997, 0.2591093}, {0.1993094, -0.2035832, 0.1143575}};

  int joint[3] = {1, 2, 3};
  double input[6];
  input[0] = 0;
  input[1] = 0;
  input[2] = 0;

  std::vector<double> output;
  double x[qtdTestes], y[qtdTestes], z[qtdTestes];
  for (int i = 0; i < qtdTestes; i++) {
    input[3] = alvo[i][0];
    input[4] = alvo[i][1];
    input[5] = alvo[i][2];

    std::cout << " best response\n";

    som.bestResponse(input, output, 3, 5);
    std::cout << " best response\n";

    // som.interpolate(input, output);

    // cout << "FIM\n";

    // std::cout << i + 1 << ": Angulos recuperados da SOM: " << output[0] << "
    // "
    //         << output[1] << std::endl;

    double sendMove[4];
    sendMove[0] = output[0];
    sendMove[1] = output[1];
    sendMove[2] = output[2];
    std::cout << " Posicao\n";
    arm.sendMoveMulti(sendMove, joint, 3);
    std::cerr << "Terminei a Posicao\n";

    int contador = 0;

    bool keep = true;
    do {
      keep = vision.get3dPosition(x[i], y[i], z[i]);
    } while (!keep);

    std::cout << i + 1 << ": Alvo (em pixels):  (" << input[3] << " , "
              << input[4] << " , " << input[5] << ')' << std::endl;
    std::cout << i + 1
              << ": Posição após movimento com os angulos acima: " << x[i]
              << " " << y[i] << ' ' << z[i] << std::endl;

    std::cout << i + 1 << ": Erro relativo: X: "
              << (abs(input[3] - x[i]) / input[3]) * 100.0
              << "% Y:  " << (abs(input[4] - y[i]) / input[4]) * 100.0 << "%"
              << "% Z:  " << (abs(input[5] - z[i]) / input[5]) * 100.0 << "%"
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