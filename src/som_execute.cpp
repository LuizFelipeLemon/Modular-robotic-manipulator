#include <unistd.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "I-SOM.h"
#include "ModularArm.h"
#include "SOMBracoModular.h"
#include "Vision.h"

using namespace std;

#define qtdTestes 4

int main() {
  Vision vision;
  vision.start();
  // TODO: removem /// comments
  /// ModularArm arm;
  /// arm.start("/dev/ttyUSB0");

  std::cerr << "entrando 180\n";
  /// arm.sendMove(200, 0);

  std::cout << "Criando a PSOM...\n";

  I_SOM som(15);
  std::cout << "Lendo a PSOM...\n";
  std::string input_file = "data/braco_modular_arco_182.txt";
  std::string output_file = "output/braco_modular_arco_15_10000.csv";

  // som.train(input_file, output_file, 10000);
  som.load(output_file);
  // Treina uma som com dados em input file e salva em output file
  // Treina com 10000 iterações e maxFeatureInitialValue = 0.01
  std::cout << "PSOM Treinada\n Iniciando validação...\n";

  cv::Mat image;

  int alvo[qtdTestes][2] = {{210, 300}, {260, 280}, {200, 205}, {230, 125}};
  int joint[2] = {1, 2};
  double input[4];
  input[0] = 0;
  input[1] = 0;
  std::vector<Tuple> output;
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
    som.interpolate(input, output);
    // som.best6(input, 2, 3, output);
    // som.populateM(output);
    cout << "FIM\n";
    /*
    std::cout << i + 1 << ": Angulos recuperados da SOM: " << output[0] << " "
              << output[1] << " X: " << output[2] << " y: " << output[3]
              << std::endl;

    double sendMove[4];
    sendMove[0] = output[0];
    sendMove[1] = output[1];
    // arm.sendMoveMulti(sendMove, joint, 2);
    std::cerr << "Terminei a Posicao 1\n";

    std::cerr << "Vamos começar a interpolação\n";
    std::vector<double> outputInterpolado;

    // som.luizInterpolation(input[2], input[3], outputInterpolado);
    std::cout << i + 1 << ": Alvo (em pixels):  " << input[2] << " " << input[3]
              << std::endl;
    std::cout << i + 1 << ": Angulos recuperados da SOM: " << output[0] << " "
              << output[1] << " X: " << output[2] << " y: " << output[3]
              << std::endl;
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
              */
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

      std::cout << w[2] << "," << w[3] << '\n';
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