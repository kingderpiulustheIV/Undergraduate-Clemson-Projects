Compiler = g++
Options = -Wall
Program = main.out

all: $(Program)

run: $(Program)
	./$(Program)
	
$(Program):	main.cpp	Pstring.cpp	
	$(Compiler) $(Options) main.cpp Pstring.cpp -o $(Program)
		
clean:
	rm -f $(Program)

