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
struct Tuple {
  float x, y;
};

vector<Tuple> points;

int Tx, Ty;

void CallBackFunc(int event, int x, int y, int flags, void* userdata) {
  if (event == cv::EVENT_LBUTTONDOWN) {
    cout << " {" << x << ", " << y << "}" << endl;
    Tx = x;
    Ty = y;
    Tuple temp;
    temp.x = x;
    temp.y = y;
    points.push_back(temp);
  }
}

int main() {
  Vision vision;
  vision.start();
  // TODO: removem /// comments
  ModularArm arm;
  // arm.start("/dev/ttyUSB0");

  std::cerr << "entrando 180\n";
  // arm.sendMove(200, 0);

  // std::cout << "Criando a PSOM...\n";

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
    vision.inputVideo.grab();
    vision.inputVideo.retrieve(image);
    for (int i = 0; i < points.size(); i++) {
      cv::circle(image, cv::Point(points[i].x, points[i].y), 4,
                 cv::Scalar(0, 0, 255), 4);
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
    cv::waitKey(1);
  }
  return 0;
}