#include <array>
#include <string>
#include <sstream>
#include <random>
#include <fstream>

// Output image resolution
static const int imageWidth = 900;
static const int imageHeight = 900;

static const int maxColorComponent = 255;

std::array <std::array <std::string, imageWidth>, imageHeight> bitMap;

// Translates string color and returns corresponding data
std::string getColor(const std::string& color) {
	std::ostringstream os;

	std::random_device rd;

	if (color == "black") {
		os << rd() % 64 << " " << rd() % 64 << " " << rd() % 64 << "\t";
		return os.str();
	}

	if (color == "grey") {
		os << rd() % 128 << " " << rd() % 128 << " " << rd() % 128 << "\t";
		return os.str();
	}

	if (color == "white") {
		os << rd() % 255 << " " << rd() % 255 << " " << rd() % 255 << "\t";
		return os.str();
	}

	if (color == "red") {
		os << "255 " << rd() % 255 << " " << rd() % 255 << "\t";
		return os.str();
	}

	if (color == "green") {
		os << rd() % 255 << " 255 " << rd() % 255 << "\t";
		return os.str();
	}

	if (color == "blue") {
		os << rd() % 255 << " " << rd() % 255 << " 255\t";
		return os.str();
	}

	if (color == "cyan") {
		os << rd() % 255 << " 255 255\t";
		return os.str();
	}

	if (color == "magenta") {
		os << "255 " << rd() % 255 << " 255\t";
		return os.str();
	}

	if (color == "yellow") {
		os << "255 255 " << rd() % 255 << "\t";
		return os.str();
	}

	os << rd() % 255 << " " << rd() % 255 << " " << rd() % 255 << "\t";
	return os.str();
}

// Fills bitMap with white color
void initBitMap() {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitMap[x][y] = "255 255 255\t";
		}
	}
}

// Fills the screen
void initBitMap(const std::string& color) {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitMap[x][y] = getColor(color);
		}
	}
}

// Draws rectangle
void drawRectangle(int x1, int y1, int x2, int y2, const std::string& color) {
	for (int y = y1; y < y2; ++y) {
		for (int x = x1; x < x2; ++x) {
			bitMap[x][y] = getColor(color);
		}
	}
}

// Draws a filled circle
void drawCircle(int xc, int yc, int r, const std::string& color) {
	int d = (5 - r * 4) / 4;
	int x = 0;
	int y = r;
	int count;

	do {
		count = xc + x;
		do {
			bitMap[count][yc + y] = getColor(color);
			bitMap[count][yc - y] = getColor(color);
			count--;
		} while (count >= xc - x);

		count = yc + y;
		do {
			bitMap[count][xc + x] = getColor(color);
			bitMap[count][xc - x] = getColor(color);
			count--;
		} while (count >= yc - y);

		if (d < 0) {
			d += 2 * x + 1;
		}
		else {
			d += 2 * (x - y) + 1;
			y--;
		}
		x++;
	} while (x <= y);
}

int main() {
	initBitMap("grey");
	drawCircle(450, 450, 300, "green");

	std::ofstream ppmFileStream("figures.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
		for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
			ppmFileStream << bitMap[colIdx][rowIdx];
		}
		ppmFileStream << "\n";
	}

	ppmFileStream.close();

	return 0;
}