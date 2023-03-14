#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>

/// Output image resolution
static const int imageWidth = 900;
static const int imageHeight = 900;

static const int maxColorComponent = 255;

std::string pixel[imageWidth][imageHeight];

std::string getColor(std::string color){
	if(color == "black")
	return "255 255 255\t";

	if(color == "white")
	return "0 0 0\t";
	
	if(color == "red")
	return "255 0 0\t";

	if(color == "green")
	return "0 255 0\t";
	
	if(color == "blue")
	return "0 0 255\t";

	if(color == "cyan")
	return "0 255 255\t";

	if(color == "magenta")
	return "255 0 255\t";

	if(color == "yellow")
	return "255 255 0\t";
}

/// Fills all pixels with white color
void pixelInit(){	
	for(int y = 0; y < imageHeight; ++y){
		for(int x = 0; x < imageWidth; ++x){
			pixel[x][y] = "255 255 255\t";
		}
	}
}

void drawRectangle(int x1, int y1, int x2, int y2, std::string color){
	for(int y = 0; y < imageHeight; ++y){
		for(int x = 0; x < imageWidth; ++x){
			if(x >= x1 && y >= y1 && x <= x2 && y <= y2)
			pixel[x][y] = getColor(color);
		}
	}
}

int main() {
	pixelInit();
	drawRectangle(0, 0, 300, 700, "red");
	drawRectangle(300, 700, 500, 800, "green");
	drawRectangle(200, 200, 700, 700, "blue");
	drawRectangle(300, 300, 600, 600, "magenta");

	std::ofstream ppmFileStream("main.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
		for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
			ppmFileStream << pixel[colIdx][rowIdx];
		}
		ppmFileStream << "\n";
	}

	ppmFileStream.close();

	return 0;
}
