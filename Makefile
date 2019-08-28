Node: codes/src/Node.h codes/src/Node.cpp 
	g++ -c codes/src/Node.cpp -o codes/build/Node.o

Sample: codes/src/Sample.h codes/src/Sample.cpp 
	g++ -c codes/src/Sample.cpp -o codes/build/Sample.o

SOM: codes/src/SOM.h codes/src/SOM.cpp 
	g++ -c codes/src/SOM.cpp -o codes/build/SOM.o

PSOM: codes/src/PSOM.h codes/src/PSOM.cpp 
	g++ -c codes/src/PSOM.cpp -o codes/build/PSOM.o

Test: codes/src/Test.h codes/src/Test.cpp 
	g++ -c codes/src/Test.cpp -o codes/build/Test.o

DataSet: codes/src/DataSet.h codes/src/DataSet.cpp 
	g++ -c codes/src/DataSet.cpp -o codes/build/DataSet.o

main: codes/src/main.cpp 
	g++ -c codes/src/main.cpp -o codes/build/main.o

output: codes/build/Node.o codes/build/Sample.o codes/build/SOM.o codes/build/Test.o codes/build/DataSet.o codes/build/main.o codes/build/PSOM.o 
	g++ codes/build/Node.o codes/build/Sample.o codes/build/SOM.o codes/build/Test.o codes/build/DataSet.o codes/build/PSOM.o codes/build/main.o -o exec

all:
	make Node Sample SOM PSOM Test DataSet main output

collect: codes/src/som_collect.cpp
	make Node Sample SOM PSOM Test DataSet
	g++ -Wall -Wunused -std=c++11 -O2 `pkg-config --cflags opencv` codes/src/som_collect.cpp -o som_collect `pkg-config --libs opencv`

execute: codes/src/som_execute.cpp
	make Node Sample SOM PSOM Test DataSet
	g++ -Wall -Wunused -std=c++11 -O2 `pkg-config --cflags opencv` codes/build/Node.o codes/build/Sample.o codes/build/SOM.o codes/build/Test.o codes/build/DataSet.o codes/build/PSOM.o codes/src/som_execute.cpp -o som_execute `pkg-config --libs opencv`

draw:
	make Node Sample SOM PSOM Test DataSet
	g++ -Wall -Wunused -std=c++11 -O2 `pkg-config --cflags opencv` codes/build/Node.o codes/build/Sample.o codes/build/SOM.o codes/build/Test.o codes/build/DataSet.o codes/build/PSOM.o codes/src/draw_map.cpp -o draw_map `pkg-config --libs opencv`

click: codes/src/execute_on_click.cpp
	make Node Sample SOM PSOM Test DataSet
	g++ -Wall -Wunused -std=c++11 -O2 `pkg-config --cflags opencv` codes/build/Node.o codes/build/Sample.o codes/build/SOM.o codes/build/Test.o codes/build/DataSet.o codes/build/PSOM.o codes/src/execute_on_click.cpp -o execute_on_click `pkg-config --libs opencv`

train: codes/src/train.cpp
	make Node Sample SOM PSOM Test DataSet
	g++ -Wall -Wunused -std=c++11 -O2 `pkg-config --cflags opencv` codes/build/Node.o codes/build/Sample.o codes/build/SOM.o codes/build/Test.o codes/build/DataSet.o codes/build/PSOM.o codes/src/train.cpp -o train `pkg-config --libs opencv`



clean:
	rm codes/build/*.o exec

    
