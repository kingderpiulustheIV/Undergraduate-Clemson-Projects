all: main.out

run: main.out
	./main.out

main.out: hospCharges.cpp Patient.cpp
	g++ -Wall hospCharges.cpp Patient.cpp -o main.out

clean:
	rm -f main.out