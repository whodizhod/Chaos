#include <array>
#include <string>
#include <sstream>
#include <random>
#include <fstream>
#include <cmath>
#include "vec3.h"

// Output image resolution
static const int imageWidth = 30;
static const int imageHeight = 30;

static const int maxColorComponent = 255;

using bitmap = std::array<std::array<Vec3f, imageHeight>, imageWidth>;

int main() {
	static bitmap bitMap;
	Vec3f origin;

	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitMap[x][y].x = int(abs((((2.0 * ((x + 0.5) / imageWidth)) - 1.0) * (imageWidth / imageHeight)) * 255));
			bitMap[x][y].y = int(abs((1.0 - (2.0 * ((y + 0.5) / imageHeight))) * 255));
			bitMap[x][y].z = int(abs( - 1.0f * 255));
		}
	}

	std::ofstream ppmFileStream("rays.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
		for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
			ppmFileStream << bitMap[colIdx][rowIdx].x << " " << bitMap[colIdx][rowIdx].y << " " << bitMap[colIdx][rowIdx].z << "\t";
		}
		ppmFileStream << "\n";
	}

	ppmFileStream.close();

	return 0;
}