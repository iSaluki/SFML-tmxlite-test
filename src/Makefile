build:
	g++ -c main.cpp
	g++ main.o -o game -lsfml-graphics -lsfml-window -lsfml-system
build-and-run:
	g++ -c main.cpp
	g++ main.o -o game -lsfml-graphics -lsfml-window -lsfml-system -I/usr/local/include -L/usr/local/lib/libtmxlite.so 
	./game