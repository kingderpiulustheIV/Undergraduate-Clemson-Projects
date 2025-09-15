

OFILES = \
         base/Matrix.o \
         base/LinearAlgebra.o \
	 base/StarterViewer.o \
	 base/oiiostuff.o \
	 base/ImgProc.o \
	 base/ImageViewer.o

ROOTDIR = .
LIB = $(ROOTDIR)/lib/libstarter.a 

GLLDFLAGS     = -lglut -lGL -lm -lGLU

CXX = g++ -Wall -g -O2 -fPIC $(DEFINES) -fopenmp -std=c++14

INCLUDES =  -I ./include/ -I /usr/local/include/ -I/usr/include/ -I../build/include/


.C.o:
	$(CXX) -c $(INCLUDES) $< -o $@

base: $(OFILES)
	ar rv $(LIB) $?
	$(CXX) base/simple_viewer.C $(INCLUDES)  -L./lib -lstarter $(GLLDFLAGS) -L../build/lib -Wl,-rpath,"$(shell realpath ../build/lib)" -lOpenImageIO -lOpenImageIO_Util -o bin/simple_viewer
	$(CXX) base/ImgViewerMain.C $(INCLUDES)  -L./lib -lstarter $(GLLDFLAGS) -L../build/lib -Wl,-rpath,"$(shell realpath ../build/lib)" -lOpenImageIO -lOpenImageIO_Util -o bin/imgviewer

clean:
	rm -rf bin/simple_viewer bin/imgviewer *.o base/*.o base/*~ include/*~ $(LIB)  *~ 



