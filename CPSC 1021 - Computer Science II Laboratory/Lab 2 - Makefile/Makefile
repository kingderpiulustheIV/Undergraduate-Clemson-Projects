all: hospitalCharges.out

run: hospitalCharges.out
	./hospitalCharges.out

hospitalCharges.out: hospitalCharges.cpp calcTotalCharges.cpp validateUserInput.cpp
	g++ -Wall hospitalCharges.cpp calcTotalCharges.cpp validateUserInput.cpp -o hospitalCharges.out

clean:
	rm -f hospitalCharges.out