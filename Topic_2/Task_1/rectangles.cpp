#include <array>
#include <string>
#include <sstream>
#include <random>
#include <fstream>

// Output image resolution
static const int imageWidth = 900;
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
		break;

	case Color::grey:

		os << rd() % 128 << " " << rd() % 128 << " " << rd() % 128 << "\t";
		return os.str();
		break;

	case Color::white:

		os << rd() % 255 << " " << rd() % 255 << " " << rd() % 255 << "\t";
		return os.str();
		break;

	case Color::red:

		os << "255 " << rd() % 255 << " " << rd() % 255 << "\t";
		return os.str();
		break;

	case Color::green:

		os << rd() % 255 << " 255 " << rd() % 255 << "\t";
		return os.str();
		break;

	case Color::blue:

		os << rd() % 255 << " " << rd() % 255 << " 255\t";
		return os.str();
		break;

	case Color::cyan:

		os << rd() % 255 << " 255 255\t";
		return os.str();
		break;

	case Color::magenta:

		os << "255 " << rd() % 255 << " 255\t";
		return os.str();
		break;

	case Color::yellow:

		os << "255 255 " << rd() % 255 << "\t";
		return os.str();
		break;

	default:

		os << rd() % 255 << " " << rd() % 255 << " " << rd() % 255 << "\t";
		return os.str();
		break;
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

// Draws rectangle
void drawRectangle(int x1, int y1, int x2, int y2, const Color& color, bitmap& bitMap) {
	for (int y = y1; y < y2; ++y) {
		for (int x = x1; x < x2; ++x) {
			bitMap[x][y] = getColor(color);
		}
	}
}

int main() {
	static bitmap bitMap;
	initBitMap(bitMap);
	drawRectangle(0, 0, 300, 300, Color::black, bitMap);
	drawRectangle(300, 0, 600, 300, Color::grey, bitMap);
	drawRectangle(600, 0, 900, 300, Color::white, bitMap);
	drawRectangle(0, 300, 300, 600, Color::red, bitMap);
	drawRectangle(300, 300, 600, 600, Color::green, bitMap);
	drawRectangle(600, 300, 900, 600, Color::blue, bitMap);
	drawRectangle(0, 600, 300, 900, Color::cyan, bitMap);
	drawRectangle(300, 600, 600, 900, Color::magenta, bitMap);
	drawRectangle(600, 600, 900, 900, Color::yellow, bitMap);

	std::ofstream ppmFileStream("rectangles.ppm", std::ios::out | std::ios::binary);
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