g++ -std=c++11 -c vm.cpp -o temp/vm.o
g++ -std=c++11 -c main.cpp -o temp/main.o
g++ -std=c++11 temp/vm.o temp/main.o -o interp.exe