#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>

/// Output image resolution
static const int imageWidth = 900;
static const int imageHeight = 900;

static const int maxColorComponent = 255;

std::string pixel[imageWidth][imageHeight];

// Translates string color and returns corresponding data
std::string getColor(std::string color){
	std::ostringstream os;

	if(color == "black"){
		os << rand()%64 << " " << rand()%64 << " " << rand()%64 << "\t";
		return os.str();
	}

	if(color == "grey"){
		os << rand()%128 << " " << rand()%128 << " " << rand()%128 << "\t";
		return os.str();
	}

	if(color == "white"){
		os << rand()%255 << " " << rand()%255 << " " << rand()%255 << "\t";
		return os.str();
	}
	
	if(color == "red"){
		os << "255 " << rand()%255 << " " << rand()%255 << "\t";
		return os.str();
	}

	if(color == "green"){
		os << rand()%255 << " 255 " << rand()%255 << "\t";
		return os.str();
	}
	
	if(color == "blue"){
		os << rand()%255 << " " << rand()%255 << " 255\t";
		return os.str();
	}

	if(color == "cyan"){
		os << rand()%255 << " 255 255\t";
		return os.str();
	}

	if(color == "magenta"){
		os << "255 " << rand()%255 << " 255\t";
		return os.str();
	}

	if(color == "yellow"){
		os << "255 255 " << rand()%255 << "\t";
		return os.str();
	}
}

// Fills pixel[][] with white color
void pixelInit(){	
	for(int y = 0; y < imageHeight; ++y){
		for(int x = 0; x < imageWidth; ++x){
			pixel[x][y] = "255 255 255\t";
		}
	}
}

// Draws rectangle
// x1 and y1 - Upper left corner coordinates
// x2 and y2 - Bottom right corner coordinates
// color (black, grey, white, red, green, blue, cyan, magenta, yellow)
void drawRectangle(int x1, int y1, int x2, int y2, std::string color){
	for(int y = y1; y < y2; ++y){
		for(int x = x1; x < x2; ++x){
			pixel[x][y] = getColor(color);
		}
	}
}

int main() {
	pixelInit();
	drawRectangle(0, 0, 300, 300, "black");
	drawRectangle(300, 0, 600, 300, "grey");
	drawRectangle(600, 0, 900, 300, "white");
	drawRectangle(0, 300, 300, 600, "red");
	drawRectangle(300, 300, 600, 600, "green");
	drawRectangle(600, 300, 900, 600, "blue");
	drawRectangle(0, 600, 300, 900, "cyan");
	drawRectangle(300, 600, 600, 900, "magenta");
	drawRectangle(600, 600, 900, 900, "yellow");

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
