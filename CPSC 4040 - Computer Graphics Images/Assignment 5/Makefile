

# Default target - build both programs
all: imgviewer opticalflow

# Object files for imgviewer (minimal dependencies - no StarterViewer, no oiiostuff)
OFILES = \
         base/Matrix.o \
         base/LinearAlgebra.o \
	 base/ImgProc.o \
	 base/ImageRenderer.o \
	 base/ImageViewer.o \
	 base/Fractal.o

# Object files for optical flow processing
OF_OFILES = \
         base/Matrix.o \
         base/LinearAlgebra.o \
         base/ImgProc.o \
         base/OpticalFlow.o

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

# Build image viewer program only
imgviewer: $(OFILES)
	ar rv $(LIB) $(OFILES)
	$(CXX) base/ImgViewerMain.C $(INCLUDES)  -L./lib -limgviewer $(GLLDFLAGS) -L../build/lib -Wl,-rpath,"$(shell realpath ../build/lib)" -lOpenImageIO -lOpenImageIO_Util -o bin/imgviewer

# Build optical flow program
opticalflow: $(OF_OFILES)
	ar rv $(LIB) base/Matrix.o base/LinearAlgebra.o base/ImgProc.o
	$(CXX) base/OpticalFlowMain.C $(INCLUDES) base/OpticalFlow.o -L./lib -limgviewer -L../build/lib -Wl,-rpath,"$(shell realpath ../build/lib)" -lOpenImageIO -lOpenImageIO_Util -o bin/opticalflow


clean:
	rm -rf bin/imgviewer bin/opticalflow *.o base/*.o base/*~ include/*~ $(LIB) *~ flow_viz.*.jpg target_flown.*.jpg frame.*.jpg

clean_opticalflow:
	rm -rf bin/opticalflow base/OpticalFlow.o flow_viz.*.jpg target_flown.*.jpg frame.*.jpg

.PHONY: all base imgviewer opticalflow clean clean_opticalflow 



