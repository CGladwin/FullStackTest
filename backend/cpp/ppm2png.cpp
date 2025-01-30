#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

bool readPPM(const std::string& filename, int& width, int& height, std::vector<unsigned char>& pixels) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string format;
    file >> format;
    if (format != "P3" && format != "P6") {
        std::cerr << "Error: Unsupported PPM format (only P3 and P6 are supported)" << std::endl;
        return false;
    }

    file >> width >> height;
    int maxVal;
    file >> maxVal;
    file.ignore(); // Skip the newline after the header

    pixels.resize(width * height * 3);

    if (format == "P6") {
        // Binary format (P6)
        file.read(reinterpret_cast<char*>(pixels.data()), pixels.size());
    } else {
        // ASCII format (P3)
        for (size_t i = 0; i < pixels.size(); ++i) {
            int value;
            file >> value;
            pixels[i] = static_cast<unsigned char>(value);
        }
    }

    if (!file) {
        std::cerr << "Error: Failed to read pixel data" << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.ppm> <output.png>" << std::endl;
        return 1;
    }

    std::string ppmFilename = argv[1];
    std::string pngFilename = argv[2];

    int width, height;
    std::vector<unsigned char> pixels;

    if (!readPPM(ppmFilename, width, height, pixels)) {
        return 1;
    }

    if (!stbi_write_png(pngFilename.c_str(), width, height, 3, pixels.data(), width * 3)) {
        std::cerr << "Error: Failed to write PNG file" << std::endl;
        return 1;
    }

    std::cout << "Successfully converted " << ppmFilename << " to " << pngFilename << std::endl;
    return 0;
}