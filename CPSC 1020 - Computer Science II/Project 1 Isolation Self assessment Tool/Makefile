all: main.out

run: main.out
	./main.out

main.out: main.cpp calcDays.cpp Date.cpp
	g++ -Wall main.cpp calcDays.cpp Date.cpp -o main.out

clean:
	rm -f main.out