g++ -c -g ../*.cpp
del main.o
g++ -o tests.exe ../tests/*.cpp *.o && tests.exe