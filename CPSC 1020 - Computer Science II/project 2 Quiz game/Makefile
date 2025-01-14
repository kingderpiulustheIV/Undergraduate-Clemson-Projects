all: main.out

run: main.out
	./main.out database.txt

main.out: main.cpp Quiz.cpp printResult.cpp
	g++ -Wall main.cpp Quiz.cpp printResult.cpp -o main.out

clean:
	rm -f main.out