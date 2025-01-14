all: main.out

run: main.out
	./main.out

main.out: main.cpp Ev.cpp Invoice.cpp Lev.cpp Motorcycle.cpp Semi.cpp Student.cpp TA.cpp Teacher.cpp Visitor.cpp
	g++ -Wall main.cpp Ev.cpp Invoice.cpp Lev.cpp Motorcycle.cpp Semi.cpp Student.cpp TA.cpp Teacher.cpp Visitor.cpp -o main.out

clean:
	rm -f main.out