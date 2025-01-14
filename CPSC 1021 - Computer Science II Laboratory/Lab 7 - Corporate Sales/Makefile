COMPILER = g++
OPTIONS = -Wall
PROGRAM = main.out

all: main.out

run: $(PROGRAM)
	./$(PROGRAM)

$(PROGRAM): main.cpp
	$(COMPILER) $(OPTIONS) main.cpp DivSales.cpp -o $(PROGRAM)

clean:
	rm main.out
