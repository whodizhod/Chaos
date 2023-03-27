#include <array>
#include <fstream>
#include <cmath>
#include "vec3.h"

// Output image resolution
static const int imageWidth = 1920;
static const int imageHeight = 1080;

static const int maxColorComponent = 255;
static const float pixelCenter = 0.5;

using Vec3f = Vec3 <float>;
using Bitmap = std::array <std::array <Vec3f, imageHeight>, imageWidth>;

// Converts coordinates to NDC space
void toNDC(Bitmap& bitMap) {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitMap[x][y].x = int((x + pixelCenter) / imageWidth * maxColorComponent);
			bitMap[x][y].y = int((y + pixelCenter) / imageHeight * maxColorComponent);
			bitMap[x][y].z = int(abs(-1.0f * maxColorComponent));
		}
	}
}

// Converts coordinates to Screen space
// Without aspect ratio
void toScreenSpace(Bitmap& bitMap) {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitMap[x][y].x = int(abs((2.0f * ((x + pixelCenter) / imageWidth) - 1.0f) * maxColorComponent));
			bitMap[x][y].y = int(abs((1.0f - (2.0f * ((y + pixelCenter) / imageHeight))) * maxColorComponent ));
			bitMap[x][y].z = int(abs(-1.0f * maxColorComponent));
		}
	}
}

// Converts coordinates to Screen space
// With aspect ratio
void toScreenSpaceAspect(Bitmap& bitMap) {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitMap[x][y].x = int(abs(((2.0f * ((x + pixelCenter) / imageWidth)) - 1.0f) * (float(imageWidth)/float(imageHeight)) * maxColorComponent));
			bitMap[x][y].y = int(abs((1.0f - (2.0f * ((y + pixelCenter) / imageHeight))) * maxColorComponent));
			bitMap[x][y].z = int(abs(-1.0f * maxColorComponent));
		}
	}
}

int main() {
	static Bitmap bitMap;

	toScreenSpaceAspect(bitMap);

	std::ofstream ppmFileStream("Screen_space_z255_aspect.ppm", std::ios::out | std::ios::binary);
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