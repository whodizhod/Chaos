#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>

// Output image resolution
static const int imageWidth = 900;
static const int imageHeight = 900;

static const int maxColorComponent = 255;

// Screen
static std::string pixel[imageWidth][imageHeight];

// Translates color string to data with noise
std::string getColor(std::string color) {
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

	os << rand()%255 << " " << rand()%255 << " " << rand()%255 << "\t";
	return os.str();
}

// Fills the screen with white color
void pixelInit(){	
	for(int y = 0; y < imageHeight; ++y){
		for(int x = 0; x < imageWidth; ++x){
			pixel[x][y] = "255 255 255\t";
		}
	}
}

// Fills the screen
void pixelInit(std::string color){	
	for(int y = 0; y < imageHeight; ++y){
		for(int x = 0; x < imageWidth; ++x){
			pixel[x][y] = getColor(color);
		}
	}
}

// Draws filled rectangle
void drawRectangle(int x1, int y1, int x2, int y2, std::string color) {
	for(int y = y1; y < y2; ++y){
		for(int x = x1; x < x2; ++x){
			pixel[x][y] = getColor(color);
		}
	}
}

// Draws a filled circle
void drawCircle(int xc, int yc, int r, std::string color) {
	int d = (5 - r * 4)/4;
    int x = 0;
    int y = r;
	int count;

    do {
		count = xc + x;
		do{
			pixel[count][yc + y] = getColor(color);
			pixel[count][yc - y] = getColor(color);
			count--;
		} while (count >= xc - x);

		count = yc + y;
		do{ 
			pixel[count][xc + x] = getColor(color);
			pixel[count][xc - x] = getColor(color);
			count--;
		} while (count >= yc - y);

        if (d < 0) {
            d += 2*x + 1;
        } else {
            d += 2*(x - y) + 1;
            y--;
        }
        x++;

    } while (x <= y);
}

int main() {
	pixelInit("grey");
	drawCircle(450, 450, 300, "green");

	std::ofstream ppmFileStream("figures.ppm", std::ios::out | std::ios::binary);
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
