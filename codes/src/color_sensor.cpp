#include <unistd.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "PSOM.h"

using namespace std;

#define qtdTestes 4

int main() {
    std::cout << "Criando a PSOM...\n";

    PSOM som(3);
    std::cout << "Lendo a PSOM...\n";
    std::string input_file = "data/color_sensor.txt";
    std::string output_file = "codes/output/out_color_10000.csv";

    // som.train(input_file, output_file, 10000);
    som.load(output_file);
    // Treina uma som com dados em input file e salva em output file
    // Treina com 10000 iterações e maxFeatureInitialValue = 0.01
    std::cout << "PSOM Treinada\n Iniciando validação...\n";
    std::ifstream file;
    std::vector<double> lineMatrix;

    file.open(input_file.c_str());
    if (!file.good()) {
        std::cout << " File, " << input_file << ", not found! " << std::endl;
        return 0;
    }

    float columns, lines, data;
    file >> lines >> columns;
    double input[4];
    std::vector<double> output;

    for (int i = 0; i < lines; i++) {
        if (file.good()) {
            for (int j = 0; j < columns; j++) {
                file >> data;
                input[j] = data;
            }
            // std::cerr << "Input " << input[0] << " " << input[1] << " "
            //          << input[2] << " " << input[3] << "\n";
            som.bestResponse(input, output, 0, 2);
            std::cout << i + 1 << ":SOM: " << output[4] << " " << output[5];
            if (input[3] == 0) std::cout << " Verde" << std::endl;
            if (input[3] == 1) std::cout << " Azul" << std::endl;
            if (input[3] == 2) std::cout << " Vermelho" << std::endl;
                }
    }

    //
    return 0;
}