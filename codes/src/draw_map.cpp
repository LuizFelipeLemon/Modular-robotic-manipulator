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

    PSOM som(10);
    std::cout << "Treinando a PSOM...\n";
    std::string input_file = "data/braco_modular_arco.txt";
    std::string output_file = "output/braco_modular_arco2_10_10000.csv";

    //som.train(input_file, output_file, 10000);
    som.load(output_file);
    // Treina uma som com dados em input file e salva em output file
    // Treina com 10000 iterações e maxFeatureInitialValue = 0.01
    std::cout << "PSOM Treinada\n Iniciando validação...\n";

    cv::Mat image;
    cv::String diretorioImag = cv::String("coleta1.png");
    image = cv::imread(diretorioImag);

    std::cout<<"N=[";
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            std::vector<double> w;
            som.getNodeFeatures(j,i,w);
            cv::circle(image, cv::Point(w[2], w[3]), 1, cv::Scalar(255, 0, 0),
               2);
            
            std::cout<<w[2]<<","<<w[3]<<'\n';
            cv::imshow("Windown", image);
            //cv::waitKey(0);
        
        }   
    }

    std::cout<<"];";

    //cv::imshow("Windown", image);
    cv::waitKey(0);
    cv::String save = cv::String("som_map10X10.png");
    std::cout << "Salvando...\n" << cv::imwrite(save, image);

    image = cv::imread(diretorioImag);

    double s1 = 350.49;
    double s2 = 350.40;
    std::vector<double> outVec;
    som.lagrangeInterpolationAxis(s1, s2, outVec);




}