#include <vector>
using namespace std;

struct Image {
	struct Pixel {
		unsigned char red; 
		unsigned char green;
		unsigned char blue;

		Pixel(unsigned char blue, unsigned char green, unsigned char red) {
			this->blue = blue;
			this->green = green;
			this->red = red;
		}
		unsigned char GetBlue() {
			return blue;
		}
		unsigned char GetGreen() {
			return green;
		}
		unsigned char GetRed() {
			return red;
		}
	};

	char idLength;
	char colorMapType;
	char imageType;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char pixelDepth;
	char imageDescriptor;
	vector<Pixel> pixels;

	Image(
	char idLength,
	char colorMapType,
	char imageType,
	short colorMapOrigin,
	short colorMapLength,
	char colorMapDepth,
	short xOrigin,
	short yOrigin,
	short width,
	short height,
	char pixelDepth,
	char imageDescriptor,
	vector<Pixel> pixels);

	vector<Pixel> GetPixels();
};

inline Image::Image(
	char idLength,
	char colorMapType,
	char imageType,
	short colorMapOrigin,
	short colorMapLength,
	char colorMapDepth,
	short xOrigin,
	short yOrigin,
	short width,
	short height,
	char pixelDepth,
	char imageDescriptor,
	vector<Pixel> pixels) {

	this->idLength = idLength;
	this->colorMapType = colorMapType;
	this->imageType = imageType;
	this->colorMapOrigin = colorMapOrigin;
	this->colorMapLength = colorMapLength;
	this->colorMapDepth = colorMapDepth;
	this->xOrigin = xOrigin;
	this->yOrigin = yOrigin;
	this->width = width;
	this->height = height;
	this->pixelDepth = pixelDepth;
	this->imageDescriptor = imageDescriptor;
	this->pixels = pixels;
}

inline vector<Image::Pixel> Image::GetPixels(){
	return pixels;
}
