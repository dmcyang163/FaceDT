INC = $(shell pkg-config --cflags opencv) 
INC += $(shell pkg-config --cflags libzmq)  
INC += -I. 
INC += -I./seetaface/include 
INC += -I./mongo-cxx-driver-legacy/include 
$(warning $(INC))



LIBS = $(shell pkg-config --libs opencv)
LIBS += $(shell pkg-config --libs libzmq)  
LIBS += -lpthread -ljpeg -lwiringPi
LIBS += -Wl,-rpath=.:lib  
LIBS += -L./lib -lseeta_facedet_lib -lviplnet -lseeta_fa_lib
LIBS += -lmongoclient


SRC = $(wildcard *.cpp)
OBJDIR = ./obj
OBJ = $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC))) 
$(warning  $(OBJ)) 

CXX = g++
CFLAGS = -O3 -pipe -std=c++11 -fopenmp -ffast-math -ftree-vectorize -mfpu=neon -mfloat-abi=hard

all: face

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) $(INC) -c  $< -o $@

face: $(OBJ)
	$(CXX) $(OBJ) $(CFLAGS) $(LIBS)  -o $@

clean:
	@rm ./obj/* -rf