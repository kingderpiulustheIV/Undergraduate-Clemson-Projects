

# Object files for imgviewer (minimal dependencies - no StarterViewer, no oiiostuff)
OFILES = \
         base/Matrix.o \
         base/LinearAlgebra.o \
	 base/ImgProc.o \
	 base/ImageRenderer.o \
	 base/ImageViewer.o \
	 base/Fractal.o

ROOTDIR = .
LIB = $(ROOTDIR)/lib/libimgviewer.a

GLLDFLAGS     = -lglut -lGL -lm -lGLU

CXX = g++ -Wall -g -O2 -fPIC $(DEFINES) -fopenmp -std=c++14

INCLUDES =  -I ./include/ -I /usr/local/include/ -I/usr/include/ -I../build/include/


.C.o:
	$(CXX) -c $(INCLUDES) $< -o $@

base: $(OFILES)
	ar rv $(LIB) $(OFILES)
	$(CXX) base/ImgViewerMain.C $(INCLUDES)  -L./lib -limgviewer $(GLLDFLAGS) -L../build/lib -Wl,-rpath,"$(shell realpath ../build/lib)" -lOpenImageIO -lOpenImageIO_Util -o bin/imgviewer

clean:
	rm -rf bin/imgviewer *.o base/*.o base/*~ include/*~ $(LIB) *~ 



