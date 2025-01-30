# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

# Source and output files
SRC = ppm2png.cpp
TARGET = ppm2png.bin

# stb_image_write.h path (assuming it's in the same directory)
STB_HEADER = stb_image_write.h

all: $(TARGET)

$(TARGET): $(SRC) $(STB_HEADER)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)