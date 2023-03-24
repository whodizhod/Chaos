#include <array>
#include <string>
#include <sstream>
#include <random>
#include <fstream>

// Output image resolution
static const int imageWidth = 900;//!!! Program crashes if imageWidth > imageHeight !!!
static const int imageHeight = 900;

static const int maxColorComponent = 255;

using bitmap = std::array<std::array<std::string, imageWidth>, imageHeight>;

enum class Color { black, grey, white, red, green, blue, cyan, magenta, yellow };

// Returns data for the corresponding color
std::string getColor(const Color& color) {
	std::ostringstream os;
	std::random_device rd;

	switch (color) {
	case Color::black:

		os << rd() % 64 << " " << rd() % 64 << " " << rd() % 64 << "\t";
		return os.str();

	case Color::grey:

		os << rd() % 128 << " " << rd() % 128 << " " << rd() % 128 << "\t";
		return os.str();

	case Color::white:

		os << rd() % 255 << " " << rd() % 255 << " " << rd() % 255 << "\t";
		return os.str();

	case Color::red:

		os << "255 " << rd() % 255 << " " << rd() % 255 << "\t";
		return os.str();

	case Color::green:

		os << rd() % 255 << " 255 " << rd() % 255 << "\t";
		return os.str();

	case Color::blue:

		os << rd() % 255 << " " << rd() % 255 << " 255\t";
		return os.str();

	case Color::cyan:

		os << rd() % 255 << " 255 255\t";
		return os.str();

	case Color::magenta:

		os << "255 " << rd() % 255 << " 255\t";
		return os.str();

	case Color::yellow:

		os << "255 255 " << rd() % 255 << "\t";
		return os.str();

	default:

		os << rd() % 255 << " " << rd() % 255 << " " << rd() % 255 << "\t";
		return os.str();
	}
}

// Fills bitMap with white color
void initBitMap(bitmap& bitMap) {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitMap[x][y] = "255 255 255\t";
		}
	}
}

// Fills the screen
void initBitMap(const Color& color, bitmap& bitMap) {
	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			bitMap[x][y] = getColor(color);
		}
	}
}

// Draws rectangle
void drawRectangle(int x1, int y1, int x2, int y2, const Color& color, bitmap& bitMap) {
	for (int y = y1; y < y2; ++y) {
		for (int x = x1; x < x2; ++x) {
			bitMap[x][y] = getColor(color);
		}
	}
}

// Draws a filled circle
void drawCircle(int xc, int yc, int r, const Color& color, bitmap& bitMap) {
	for (int y = yc - r; y < imageHeight; ++y) {
		for (int x = xc - r; x < imageWidth; ++x) {
			if (r >= sqrt(pow(abs(x - xc), 2) + pow(abs(y - yc), 2)))
				bitMap[x][y] = getColor(color);
		}
	}
}

int main() {
	static bitmap bitMap;
	initBitMap(Color::grey, bitMap);
	drawCircle(450, 450, 300, Color::green, bitMap);

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