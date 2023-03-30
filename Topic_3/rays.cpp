#include <vector>
#include <fstream>
#include <cmath>
#include "vec3.h"

// Output image resolution
static const int imageWidth = 1920;
static const int imageHeight = 1080;

static const float aspect_ratio = float(imageWidth) / float(imageHeight);

static const int maxColorComponent = 255;
static const float pixelCenter = 0.5;

using Vec3f = Vec3 <float>;
using Bitmap = std::vector <std::vector <Vec3f> >;

// Converts coordinates to NDC space
void toNDC(Bitmap& bitMap) {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitMap[x][y].x = (x + pixelCenter) / imageWidth * maxColorComponent;
			bitMap[x][y].y = (y + pixelCenter) / imageHeight * maxColorComponent;
			bitMap[x][y].z = std::abs(-1.0f * maxColorComponent);
		}
	}
}

// Converts coordinates to Screen space
// Without aspect ratio
void toScreenSpace(Bitmap& bitMap) {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitMap[x][y].x = std::abs((2.0f * ((x + pixelCenter) / imageWidth) - 1.0f) * maxColorComponent);
			bitMap[x][y].y = std::abs((1.0f - (2.0f * ((y + pixelCenter) / imageHeight))) * maxColorComponent);
			bitMap[x][y].z = std::abs(-1.0f * maxColorComponent);
		}
	}
}

// Converts coordinates to Screen space
// With aspect ratio
void toScreenSpaceAspect(Bitmap& bitMap) {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitMap[x][y].x = std::abs(((2.0f * ((x + pixelCenter) / imageWidth)) - 1.0f) * aspect_ratio) * maxColorComponent);
			bitMap[x][y].y = std::abs((1.0f - (2.0f * ((y + pixelCenter) / imageHeight))) * maxColorComponent);
			bitMap[x][y].z = std::abs(-1.0f * maxColorComponent);
		}
	}
}

// Converts coordinates to Screen space
// with aspect ratio and normalizes the vectors
void normalize(Bitmap& bitMap) {
	float max_magnitude = 1.0f;

	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitMap[x][y].x = (((2.0f * ((x + pixelCenter) / imageWidth)) - 1.0f) * (float(imageWidth) / float(imageHeight)));
			bitMap[x][y].y = (1.0f - (2.0f * ((y + pixelCenter) / imageHeight)));
			bitMap[x][y].z = -1.0f;

			max_magnitude = std::sqrt(std::pow(bitMap[x][y].x, 2) + std::pow(bitMap[x][y].y, 2) + std::pow(bitMap[x][y].z, 2));

			bitMap[x][y].x = std::abs(bitMap[x][y].x / max_magnitude) * maxColorComponent;
			bitMap[x][y].y = std::abs(bitMap[x][y].y / max_magnitude) * maxColorComponent;
			bitMap[x][y].z = std::abs(bitMap[x][y].z / max_magnitude) * maxColorComponent;
		}
	}
}

int main() {
	Bitmap bitmap(imageWidth, std::vector<Vec3f>(imageHeight));

	normalize(bitmap);

	std::ofstream ppmFileStream("Normalized_final.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
		for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
			ppmFileStream << int(bitmap[colIdx][rowIdx].x) << " " << int(bitmap[colIdx][rowIdx].y) << " " << int(bitmap[colIdx][rowIdx].z) << "\t";
		}
		ppmFileStream << "\n";
	}

	ppmFileStream.close();

	return 0;
}