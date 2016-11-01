INC = $(shell pkg-config --cflags opencv)
INC += $(shell pkg-config --cflags libzmq)  
INC += -I. 
$(warning $(INC))

SRC = $(wildcard *.cpp)


LIBS = $(shell pkg-config --libs opencv)
LIBS += $(shell pkg-config --libs libzmq)  
LIBS += -lpthread -ljpeg -lwiringPi


OBJDIR = ./obj
OBJ = $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC))) 
$(warning  $(OBJ)) 

CXX = g++
CFLAGS = -O3 -pipe -std=c++11 -fopenmp -ffast-math -ftree-vectorize -mfpu=neon -mfloat-abi=hard

all: face

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) -I. -I$(INC) -c  $< -o $@

face: $(OBJ)
	$(CXX) $(OBJ) $(CFLAGS) $(LIBS)  -o $@

clean:
	@rm ./obj/* -rf