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

float centralize(const int& n) {
	return (n + pixelCenter);
}

float calculate_ndc_space_x(const int& x) {
	return centralize(x) / imageWidth;
}

float calculate_ndc_space_y(const int& y) {
	return centralize(y) / imageHeight;
}

float calculate_screen_space_x(const int& x) {
	return (2.0f * calculate_ndc_space_x(x)) - 1.0f;
}

float calculate_screen_space_y(const int& y) {
	return 1.0f - (2.0f * calculate_ndc_space_y(y));
}

void convert_to_ndc_space(Bitmap& bitmap) {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitmap[x][y].x = calculate_ndc_space_x(x);
			bitmap[x][y].y = calculate_ndc_space_y(y);
			bitmap[x][y].z = -1.0f;
		}
	}
}

void convert_to_screen_space(Bitmap& bitmap) {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitmap[x][y].x = calculate_screen_space_x(x);
			bitmap[x][y].y = calculate_screen_space_y(y);
			bitmap[x][y].z = -1.0f;
		}
	}
}

void convert_to_screen_space_w_aspect_ratio(Bitmap& bitmap) {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitmap[x][y].x = calculate_screen_space_x(x) * aspect_ratio;
			bitmap[x][y].y = calculate_screen_space_y(y);
			bitmap[x][y].z = -1.0f;
		}
	}
}

void convert_to_normalized(Bitmap& bitmap) {
	float max_magnitude = 1.0f;

	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitmap[x][y].x = calculate_screen_space_x(x) * aspect_ratio;
			bitmap[x][y].y = calculate_screen_space_y(y);
			bitmap[x][y].z = -1.0f;

			// faster than pow()
			max_magnitude =
				std::sqrt(
					bitmap[x][y].x * bitmap[x][y].x  +
					bitmap[x][y].y * bitmap[x][y].y  +
					bitmap[x][y].z * bitmap[x][y].z
				);

			// faster "bitmap[x][y].n /= max_magnitude"
			bitmap[x][y].x = bitmap[x][y].x * (1 / max_magnitude);
			bitmap[x][y].y = bitmap[x][y].y * (1 / max_magnitude);
			bitmap[x][y].z = bitmap[x][y].z * (1 / max_magnitude);
		}
	}
}

void colorize_vectors(Bitmap& bitmap) {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitmap[x][y].x *= maxColorComponent ;
			bitmap[x][y].y *= maxColorComponent;
			bitmap[x][y].z *= maxColorComponent;
		}
	}
}

int main() {
	Bitmap bitmap(imageWidth, std::vector<Vec3f>(imageHeight));

	convert_to_normalized(bitmap);
	colorize_vectors(bitmap);

	std::ofstream ppmFileStream("Normalized_final.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
		for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
			ppmFileStream << int(std::abs(bitmap[colIdx][rowIdx].x)) << " "
						  << int(std::abs(bitmap[colIdx][rowIdx].y)) << " "
						  << int(std::abs(bitmap[colIdx][rowIdx].z)) << "\t";
		}
		ppmFileStream << "\n";
	}

	ppmFileStream.close();

	return 0;
}