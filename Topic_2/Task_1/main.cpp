#include <fstream>
#include <string>

/// Output image resolution
static const int imageWidth = 1920;
static const int imageHeight = 1080;

static const int maxColorComponent = 255;

int main() {
	std::ofstream ppmFileStream("crt_output_image.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	std::string color = "0 0 0\t";

	for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
		if(rowIdx%100==0){
				if(color=="0 0 0\t"){
					color = "255 0 255\t";
				}else{
					color = "0 0 0\t";
				}
			}
		for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
			if(colIdx%100==0){
				if(color=="0 0 0\t"){
					color = "255 0 255\t";
				}else{
					color = "0 0 0\t";
				}
			}

			ppmFileStream << color;
		}
		ppmFileStream << "\n";
	}

	ppmFileStream.close();

	return 0;
}
