# Modular-robotic-manipulator

For accurate execution of any robotic system proper sensing and control is expected. However, kinematic modeling can become a very laborious step when performed analytically. Approaches using neural networks seek to simplify this process but in return require relatively high amount of training data. The following work explores neural networks that can more efficiently deliver adequate results at lower computational costs.

This work is highly based on [this](https://github.com/WKossmann/ModularRoboticManipulator-MRM) developed by Willian Kossmann da Silva.


## Installing the requisites
* OpenCV 3.4.x [Installation Guide](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)
* ArUco 3.0.10 [Installation Guide](http://maztories.blogspot.com/2013/07/installing-aruco-augmented-reality.html)

This project was initially executed on a Linux environment with the distribution Ubuntu 18.04. The OpenCV version was 3.4.1 and the ArUco version was 3.0.10. The machine had an Intel Core i5 7th generation and 4GB of RAM Memory.


## Proposed Method

The first step is to capture the points that will be the input of neural network training. About 170 basis points are captured as shown in the image below.

![Captured points](https://github.com/LuizFelipeLemon/Modular-robotic-manipulator/blob/master/data/coleta1_181.png)

In order to execute this step run:

```
make collect
./som_collect
```
Next it is necessary to train the model with the desired topology. To ajust parameters of the Network fell free to edit [here](https://github.com/LuizFelipeLemon/Modular-robotic-manipulator/codes/src/train.cpp), might be appropriate to change the input filename also. In order to execute this step run:

```
make train
./train
```

Below we can see the result of the trained algorithm. The SOM Map printed on the image on green. The red and blue points are not important right now.


![Map of a 15x15 SOM](https://github.com/LuizFelipeLemon/Modular-robotic-manipulator/blob/master/data/coleta2_15x15.png)


Lastly we validate the training with the excecution code. This will run through some arbitrary points in order to validate, error evaluation are printed on screen. To execute this step run:

```
make execute
./som_execute
```
Below we can see the result of the excecution of the movement. The SOM Map printed on the image on green. The red and blue points are now important! In red we can see the target points, in blue are the resulting points from the execution of the movement.

![Map of a 15x15 SOM](https://github.com/LuizFelipeLemon/Modular-robotic-manipulator/blob/master/data/coleta2_15x15.png)
