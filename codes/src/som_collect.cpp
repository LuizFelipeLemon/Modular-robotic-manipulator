#include <math.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "ModularArm.h"
//#include "Vision.h"

#define QTD_POINTS 10000

void normalize(double vector[4], double& norma) {
  vector[0] = (vector[0]) / 640;
  vector[1] = (vector[1]) / 640;
  vector[2] = (vector[2]) / 640;
  vector[3] = (vector[3]) / 640;
}

int main() {
  ModularArm arm;
  // Vision vision;

  arm.start("/dev/ttyUSB0");

  // arm.sendMove(230, 0);
  // vision.start();

  std::cerr << "vision startou\n";
  // Variaveis:
  double angle[3] = {200, 0, 0};
  int type[3] = {1, 2, 2};
  double pos[3] = {0, 0, 0};
  int joint[3] = {0, 1, 2};
  bool crescente = false;
  int x = 0, y = 0;
  // int passointerno=1;
  // int passoexterno=1;
  int points_x[QTD_POINTS], points_y[QTD_POINTS];
  int angle_1[QTD_POINTS], angle_2[QTD_POINTS];
  int cont = 0;

  std::cout << "Colecting, please wait ....\n" << std::endl;

  for (int i = 145; i >= 80; i -= 5) {
    if (crescente) {
      for (int j = 70; j <= 140; j += 5) {
        // if(j<85){
        //     passointerno = 1;
        // }else
        // if(j>125){
        //     passointerno = 1;
        // }else passointerno=3;
        angle[1] = i - 90;
        angle[2] = j - 90;
        arm.ForwardK(angle, type, 3, pos);
        if (pos[2] >= 7.5) {
          // std::cout << cont << " >> B: " << i << " C: " << j << " -> Z: " <<
          // pos[2] << std::endl;
          angle[1] += 90;
          angle[2] += 90;
          arm.sendMoveMulti(angle, joint, 3);
          int tentativas = 0;
          while (true) {
            if (vision.getVisualPosition(x, y)) {
              points_x[cont] = x;
              points_y[cont] = y;
              angle_1[cont] = i;
              angle_2[cont] = j;
              cont++;
              std::cerr << cont << " Pontos coletados\n";
              break;
            } else {
              tentativas++;
              if (tentativas > 10) {
                break;
              }
            }
            // std::cout << cont << " >> B:" << i << " C:" << j << " -> X:" <<
            // (int)x << " Y:" << (int)y << std::endl;
            // myfile << i << " " << j << " " << x << " " << y << std::endl;
          }
        }
      }
      crescente = false;
    } else {
      for (int j = 140; j >= 70; j -= 5) {
        // if(j<85){
        //     passointerno = 1;
        // }else
        // if(j>125){
        //     passointerno = 1;
        // }else passointerno=5;
        angle[1] = i - 90;
        angle[2] = j - 90;
        arm.ForwardK(angle, type, 3, pos);
        if (pos[2] >= 7.5) {
          // std::cout <<  cont << " >> B: " << i << " C: " << j << " -> Z: " <<
          // pos[2] << std::endl;
          angle[1] += 90;
          angle[2] += 90;
          std::cerr << "Mandei moveer\n";
          arm.sendMoveMulti(angle, joint, 3);
          std::cerr << "terminou moveer\n";
          int tentativas = 0;
          while (true) {
            if (vision.getVisualPosition(x, y)) {
              points_x[cont] = x;
              points_y[cont] = y;
              angle_1[cont] = i;
              angle_2[cont] = j;
              cont++;
              break;
            } else {
              tentativas++;
              if (tentativas > 10) {
                break;
              }
            }
            // std::cout << cont << " >> B:" << i << " C:" << j << " -> X:" <<
            // (int)x << " Y:" << (int)y << std::endl;
            // myfile << i << " " << j << " " << x << " " << y << std::endl;
          }
        }
      }
      crescente = true;
    }
  }

  // Finalizing
  cv::String diretorioImag = cv::String("coleta1.png");
  std::string diretorioDado = cv::String("data/braco_modular_arco.txt");

  std::cout << "Quantidade de pontos coletados: " << cont << std::endl;

  std::cout << "Escrevendo Dados..." << std::endl;

  // Salvando arquivos:
  std::cout << "Diretorio de dados: " << diretorioDado << std::endl;
  std::ofstream myfile;
  myfile.open(diretorioDado);

  myfile << cont << " "
         << "4" << std::endl;

  for (int i = 0; i < cont; i++) {
    double neuron[4];
    double norma;
    neuron[0] = angle_1[i];
    neuron[1] = angle_2[i];
    neuron[2] = points_x[i];
    neuron[3] = points_y[i];
    myfile << neuron[0] << " " << neuron[1] << " " << neuron[2] << " "
           << neuron[3] << std::endl;
  }
  myfile.close();

  // Mostrando imagem resultante
  vision.showPoints(points_x, points_y, cont, cv::Scalar(0, 0, 255), true);

  // Retornando para home:
  std::cout << "Retornando braço para posição inicial..." << std::endl;
  arm.sendHome();

  std::cout << "Coleta Finalizada" << std::endl;

  return 0;  //
}