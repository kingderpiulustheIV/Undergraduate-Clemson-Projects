all: main.out

run: main.out
	./main.out dates.txt

main.out: main.cpp Date.cpp
	g++ -Wall main.cpp Date.cpp -o main.out

clean:
	rm -f main.out