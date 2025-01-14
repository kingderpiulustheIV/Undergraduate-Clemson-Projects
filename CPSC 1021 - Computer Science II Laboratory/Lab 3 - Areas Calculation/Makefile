all: main.out

run: main.out
	./main.out

main.out: areaCalc.cpp Circle.cpp Rectangle.cpp Square.cpp Trapezoid.cpp
	g++ -Wall areaCalc.cpp Circle.cpp Rectangle.cpp Square.cpp Trapezoid.cpp -o main.out

clean:
	rm -f main.out