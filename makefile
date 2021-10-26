compile:./main.cpp
	g++ -c ./main.cpp
	g++ main.o -o out.app -lsfml-graphics -lsfml-window -lsfml-system

run:
	./out.app