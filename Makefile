Node: src/Node.h src/Node.cpp 
	g++ -c src/Node.cpp -o build/Node.o

Sample: src/Sample.h src/Sample.cpp 
	g++ -c src/Sample.cpp -o build/Sample.o

SOM: src/SOM.h src/SOM.cpp 
	g++ -c src/SOM.cpp -o build/SOM.o

PSOM: src/PSOM.h src/PSOM.cpp 
	g++ -c src/PSOM.cpp -o build/PSOM.o

Test: src/Test.h src/Test.cpp 
	g++ -c src/Test.cpp -o build/Test.o

DataSet: src/DataSet.h src/DataSet.cpp 
	g++ -c src/DataSet.cpp -o build/DataSet.o

main: src/main.cpp 
	g++ -c src/main.cpp -o build/main.o

output: build/Node.o build/Sample.o build/SOM.o build/Test.o build/DataSet.o build/main.o build/PSOM.o 
	g++ build/Node.o build/Sample.o build/SOM.o build/Test.o build/DataSet.o build/PSOM.o build/main.o -o exec

all:
	make Node Sample SOM PSOM Test DataSet main output

collect: src/som_collect.cpp
	make Node Sample SOM PSOM Test DataSet
	g++ -Wall -Wunused -std=c++11 -O2 `pkg-config --cflags opencv` src/som_collect.cpp -o som_collect `pkg-config --libs opencv`

execute: src/som_execute.cpp
	make Node Sample SOM PSOM Test DataSet
	g++ -Wall -Wunused -std=c++11 -O2 `pkg-config --cflags opencv` build/Node.o build/Sample.o build/SOM.o build/Test.o build/DataSet.o build/PSOM.o src/som_execute.cpp -o som_execute `pkg-config --libs opencv`

draw:
	make Node Sample SOM PSOM Test DataSet
	g++ -Wall -Wunused -std=c++11 -O2 `pkg-config --cflags opencv` build/Node.o build/Sample.o build/SOM.o build/Test.o build/DataSet.o build/PSOM.o src/draw_map.cpp -o draw_map `pkg-config --libs opencv`

click: src/execute_on_click.cpp
	make Node Sample SOM PSOM Test DataSet
	g++ -Wall -Wunused -std=c++11 -O2 `pkg-config --cflags opencv` build/Node.o build/Sample.o build/SOM.o build/Test.o build/DataSet.o build/PSOM.o src/execute_on_click.cpp -o execute_on_click `pkg-config --libs opencv`

train: src/train.cpp
	make Node Sample SOM PSOM Test DataSet
	g++ -Wall -Wunused -std=c++11 -O2 `pkg-config --cflags opencv` build/Node.o build/Sample.o build/SOM.o build/Test.o build/DataSet.o build/PSOM.o src/train.cpp -o train `pkg-config --libs opencv`



clean:
	rm build/*.o exec

    
