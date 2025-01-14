COMPILER = g++
OPTIONS = -Wall
PROGRAM = main.out

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)

$(PROGRAM): main.cpp EncryptableString.cpp
	$(COMPILER) $(OPTIONS) main.cpp EncryptableString.cpp -o $(PROGRAM)
	
clean:
	rm *.out
