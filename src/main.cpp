/*
 * File:   main.cpp
 * Author: oriva
 *
 * Created on 20 de Agosto de 2016, 10:56
 */

// g++ main.cpp Node.cpp Sample.cpp SOM.cpp Test.cpp DataSet.cpp -o main

#include <cstdlib>
#include <iostream> 
#include "Test.h"
#include "TestArduino.h"

using namespace std;

/*
 *
 */
int main(int argc, char** argv) {
  cout << " Testando rede SOM!" << endl;

  Test test;

  // test.colorDataSet();
  // test.armInLine();

  // TestArduino test;
  // test.turnLeft();
  test.somModularArm();

  return 0;
}
