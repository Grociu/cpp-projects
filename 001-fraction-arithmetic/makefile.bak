fractions.exe: ./_comp/fraction.o ./_comp/main.o
	g++ ./_comp/fraction.o ./_comp/main.o -o fractions.exe

./_comp/fraction.o: ./classes/fraction.cpp
	g++ -c ./classes/fraction.cpp -o ./_comp/fraction.o

./_comp/main.o: main.cpp
	g++ -c main.cpp -o ./_comp/main.o