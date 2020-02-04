#include <math.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "Vision.h"

int main() {
  Vision vision;
  vision.start();
  double x = 0, y = 0, z = 0;

  while (true) {
    vision.get3dPosition(x, y, z);
  }
}