all: main.out

run: main.out
	./main.out

main.out: main.cpp Rational.cpp
	g++ -Wall main.cpp Rational.cpp -o main.out

clean:
	rm -f main.out