#include <iostream>
#include <vector>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Image.h"
using namespace std;

void Read(string fileName, vector<Image>& data) {

	ifstream file(fileName, ios_base::binary);

	/*==== idLength ====*/
	char idLength;
	file.read(&idLength, sizeof(idLength));
	//cout << (int)idLength << endl;

	/*==== colorMapType ====*/
	char colorMapType;
	file.read(&colorMapType, sizeof(colorMapType));
	//cout << (int)colorMapType << endl;

	/*==== imageType ====*/
	char imageType;
	file.read(&imageType, sizeof(imageType));
	//cout << (int)imageType << endl;

	/*==== colorMapOrigin ====*/
	short colorMapOrigin;
	file.read((char*)&colorMapOrigin, sizeof(colorMapOrigin));
	//cout << colorMapOrigin<< endl;

	/*==== colorMapLength ====*/
	short colorMapLength;
	file.read((char*)&colorMapLength, sizeof(colorMapLength));
	//cout << colorMapLength << endl;

	/*==== colorMapDepth ====*/
	char colorMapDepth;
	file.read(&colorMapDepth, sizeof(colorMapDepth));
	//cout << (int)colorMapDepth << endl;

	/*==== xOrigin ====*/
	short xOrigin;
	file.read((char*)&xOrigin, sizeof(xOrigin));
	//cout << xOrigin << endl;

	/*==== yOrigin ====*/
	short yOrigin;
	file.read((char*)&yOrigin, sizeof(yOrigin));
	//cout << yOrigin << endl;

	/*==== width ====*/
	short width;
	file.read((char*)&width, sizeof(width));
	//cout << width << endl;

	/*==== height ====*/
	short height;
	file.read((char*)&height, sizeof(height));
	//cout << height << endl;

	/*==== pixelDepth ====*/
	char pixelDepth;
	file.read(&pixelDepth, sizeof(pixelDepth));
	//cout << (int)pixelDepth << endl;

	/*==== imageDescriptor ====*/
	char imageDescriptor;
	file.read(&imageDescriptor, sizeof(imageDescriptor));
	//cout << (int)imageDescriptor << endl;

	/*==== image data ====*/
	int imageData = height * width;
	//cout << imageData << endl;

	vector<Image::Pixel> pixels;

	for (int i = 0; i < imageData; i++) {

		unsigned char blue;
		file.read((char*)& blue, sizeof(blue));
		//cout << (int)blue << endl;

		unsigned char green;
		file.read((char*)&green, sizeof(green));
		//cout << (int)green << endl;

		unsigned char red;
		file.read((char*)&red, sizeof(red));
		//cout << (int)red << endl;

		Image::Pixel BGR (blue, green, red);
		pixels.push_back(BGR);
	}

	Image image (idLength, colorMapType, imageType, colorMapOrigin, colorMapLength,
		colorMapDepth, xOrigin, yOrigin, width, height, pixelDepth, imageDescriptor, pixels);
	data.push_back(image);

	file.close();
}



void Write(string fileName, Image data) {

	ofstream file(fileName, ios_base::binary);

	/*==== idLength ====*/
	file.write(&data.idLength, sizeof(data.idLength));

	/*==== colorMapType ====*/
	file.write(&data.colorMapType, sizeof(data.colorMapType));

	/*==== imageType ====*/
	file.write(&data.imageType, sizeof(data.imageType));

	/*==== colorMapOrigin ====*/
	file.write((char*)&data.colorMapOrigin, sizeof(data.colorMapOrigin));

	/*==== colorMapLength ====*/
	file.write((char*)&data.colorMapLength, sizeof(data.colorMapLength));

	/*==== colorMapDepth ====*/
	file.write(&data.colorMapDepth, sizeof(data.colorMapDepth));

	/*==== xOrigin ====*/
	file.write((char*)&data.xOrigin, sizeof(data.xOrigin));

	/*==== yOrigin ====*/
	file.write((char*)&data.yOrigin, sizeof(data.yOrigin));

	/*==== width ====*/
	file.write((char*)&data.width, sizeof(data.width));

	/*==== height ====*/
	file.write((char*)&data.height, sizeof(data.height));

	/*==== pixelDepth ====*/
	file.write(&data.pixelDepth, sizeof(data.pixelDepth));

	/*==== imageDescriptor ====*/
	file.write(&data.imageDescriptor, sizeof(data.imageDescriptor));

	/*==== image data ====*/
	int imageData = data.height * data.width;

	vector<Image::Pixel> pixels = data.GetPixels();


	for (int i = 0; i < imageData; i++) {	

		unsigned char blue = pixels[i].GetBlue();
		file.write((char*)&blue, sizeof(blue));
		//cout << (float)blue << endl;

		unsigned char green = pixels[i].GetGreen();
		file.write((char*)&green, sizeof(green));
		//cout << (float)green << endl;

		unsigned char red = pixels[i].GetRed();
		file.write((char*)&red, sizeof(red));
		//cout << (float)red << endl;
	}
}

bool Compare(string layerA, string layerB, vector<Image>& pictures) {

	Read(layerA, pictures);
	Read(layerB, pictures);

	float blue = 0;
	float green = 0;
	float red = 0;

	Image imageA = pictures[pictures.size() - 2];
	Image imageB = pictures[pictures.size() - 1];

	vector<Image::Pixel> y = imageA.GetPixels();
	vector<Image::Pixel> x = imageB.GetPixels();

	size_t size = x.size();

	int counter = 0;

	for (size_t i = 0; i < size; i++) {
		if (y[i].GetBlue() == x[i].GetBlue() && y[i].GetGreen() == x[i].GetGreen() && y[i].GetRed() == x[i].GetRed()) {
			counter++;
		}
		//else {
		//	cout << endl;
		//	if (y[i].GetBlue() != x[i].GetBlue()) {
		//		cout << "Error in Blue: " << (float)y[i].GetBlue() << " should be " << (float)x[i].GetBlue() << endl << endl;
		//	}
		//	if (y[i].GetGreen() != x[i].GetGreen()) {
		//	cout << "Error in Green: " << (float)y[i].GetGreen() << " should be " << (float)x[i].GetGreen() << endl << endl;;
		//	}
		//	if (y[i].GetRed() != x[i].GetRed()) {
		//		cout << "Error in Red: " << (float)y[i].GetRed() << " should be " << (float)x[i].GetRed() << endl << endl;;
		//	}
		//}
	}
	if (counter == size) {
		return true;
	}
	return false;
}



void Multiply(string layerA, string layerB, string writeTo, vector<Image>& pictures) {
	
	Read(layerA, pictures);
	Read(layerB, pictures);

	float blue = 0;
	float green = 0;
	float red = 0;

	Image imageA = pictures[pictures.size() - 2];
	Image imageB = pictures[pictures.size() - 1];

	vector<Image::Pixel> x = imageB.GetPixels();
	vector<Image::Pixel> y = imageA.GetPixels();

	size_t size = x.size();

	vector<Image::Pixel> newImage;

	for (size_t i = 0; i < size; i++) {

		blue = ((((float)x[i].GetBlue() / 255.0f) * ((float)y[i].GetBlue() / 255.0f))) * 255.0f + 0.5f;

		green = ((((float)x[i].GetGreen() / 255.0f) * ((float)y[i].GetGreen() / 255.0f))) * 255.0f + 0.5f;

		red = ((((float)x[i].GetRed() / 255.0f) * ((float)y[i].GetRed() / 255.0f))) * 255.0f + 0.5f;


		Image::Pixel image((unsigned char)blue, (unsigned char)green, (unsigned char)red);

		newImage.push_back(image);
	}

	Image picture ((char)0, (char)0, (char)2, (short)0, (short)0, (char)0, (short)0, (short)0, 
		(short)512, (short)512, (char)24, (char)0, newImage);

	Write(writeTo, picture);
}



void Subtract(string layerA, string layerB, string writeTo, vector<Image>& pictures) {

	Read(layerA, pictures);
	Read(layerB, pictures);

	float blue = 0;
	float green = 0;
	float red = 0;

	Image imageA = pictures[pictures.size() - 2];
	Image imageB = pictures[pictures.size() - 1];

	vector<Image::Pixel> x = imageB.GetPixels();
	vector<Image::Pixel> y = imageA.GetPixels();

	size_t size = x.size();

	vector<Image::Pixel> newImage;

	for (size_t i = 0; i < size; i++) {

		blue = ((((float)x[i].GetBlue() / 255.0f) - ((float)y[i].GetBlue() / 255.0f))) * 255.0f + 0.5f;
		if (blue < 0.0f) {
			blue = 0.0f;
		}

		green = ((((float)x[i].GetGreen() / 255.0f) - ((float)y[i].GetGreen() / 255.0f))) * 255.0f + 0.5f;
		if (green < 0.0f) {
			green = 0.0f;
		}

		red = ((((float)x[i].GetRed() / 255.0f) - ((float)y[i].GetRed() / 255.0f))) * 255.0f + 0.5f;
		if (red < 0.0f) {
			red = 0.0f;
		}

		Image::Pixel image((unsigned char)blue, (unsigned char)green, (unsigned char)red);

		newImage.push_back(image);
	}

	Image picture ((char)0, (char)0, (char)2, (short)0, (short)0, (char)0, (short)0, (short)0,
		(short)512, (short)512, (char)24, (char)0, newImage);

	Write(writeTo, picture);
}



void Screen(string layerA, string layerB, string writeTo, vector<Image>& pictures) {

	Read(layerA, pictures);
	Read(layerB, pictures);

	float blue = 0;
	float green = 0;
	float red = 0;

	Image imageA = pictures[pictures.size() - 2];
	Image imageB = pictures[pictures.size() - 1];

	vector<Image::Pixel> x = imageB.GetPixels();
	vector<Image::Pixel> y = imageA.GetPixels();

	size_t size = x.size();

	vector<Image::Pixel> newImage;

	for (size_t i = 0; i < size; i++) {

		blue = (( 1 - (1 - ((float)x[i].GetBlue() / 255.0f)) * (1 - ((float)y[i].GetBlue() / 255.0f)))) * 255.0f + 0.5f;

		green = ((1 - (1 - ((float)x[i].GetGreen() / 255.0f)) * (1 - ((float)y[i].GetGreen() / 255.0f)))) * 255.0f + 0.5f;

		red = ((1 - (1 - ((float)x[i].GetRed() / 255.0f)) * (1 - ((float)y[i].GetRed() / 255.0f)))) * 255.0f + 0.5f;

		Image::Pixel image((unsigned char)blue, (unsigned char)green, (unsigned char)red);

		newImage.push_back(image);
	}

	Image picture((char)0, (char)0, (char)2, (short)0, (short)0, (char)0, (short)0, (short)0,
		(short)512, (short)512, (char)24, (char)0, newImage);

	Write(writeTo, picture);
}



void Overlay(string layerA, string layerB, string writeTo, vector<Image>& pictures) {

	Read(layerA, pictures);
	Read(layerB, pictures);

	float blue = 0;
	float green = 0;
	float red = 0;

	Image imageA = pictures[pictures.size() - 1];
	Image imageB = pictures[pictures.size() - 2];

	vector<Image::Pixel> x = imageA.GetPixels();
	vector<Image::Pixel> y = imageB.GetPixels();

	size_t size = x.size();
	
	vector<Image::Pixel> newImage;

	for (size_t i = 0; i < size; i++) {
		blue = (float)x[i].GetBlue();
		green = (float)x[i].GetGreen();
		red = (float)x[i].GetRed();

		if (blue > 127 || green > 127 || red > 127) {
			blue = (1 - (2 * (1 - ((float)x[i].GetBlue() / 255.0f)) * (1 - ((float)y[i].GetBlue() / 255.0f)))) * 255.0f + 0.5f;
			if (blue <= 0) {
				blue = 0;
			}
			else if (blue > 255.0f) {
				blue = 255.0f;
			}

			green = (1 - (2 * (1 - ((float)x[i].GetGreen() / 255.0f)) * (1 - ((float)y[i].GetGreen() / 255.0f)))) * 255.0f + 0.5f;
			if (green <= 0) {
				green = 0;
			}
			else if (green > 255.0f) {
				green = 255.0f;
			}

			red = (1 - (2 * (1 - ((float)x[i].GetRed() / 255.0f)) * (1 - ((float)y[i].GetRed() / 255.0f)))) * 255.0f + 0.5f;
			if (red <= 0) {
				red = 0;
			}
			else if (red > 255.0f) {
				red = 255.0f;
			}
		}
		else if (blue <= 127 || green <= 127 || red <= 127) {
			blue = ((((float)x[i].GetBlue() / 255.0f) * ((float)y[i].GetBlue() / 255.0f))) * 255.0f * 2.0f + 0.5f;
			if (blue < 0) {
				blue = 0;
			}
			else if (blue > 255.0f) {
				blue = 255.0f;
			}

			green = ((((float)x[i].GetGreen() / 255.0f) * ((float)y[i].GetGreen() / 255.0f))) * 255.0f * 2.0f + 0.5f;
			if (green < 0) {
				green = 0;
			}
			else if (green > 255.0f) {
				green = 255.0f;
			}

			red = ((((float)x[i].GetRed() / 255.0f) * ((float)y[i].GetRed() / 255.0f))) * 255.0f * 2.0f + 0.5f;
			if (red < 0) {
				red = 0;
			}
			else if (red > 255.0f) {
				red = 255.0f;
			}
		}
		Image::Pixel image((unsigned char)blue, (unsigned char)green, (unsigned char)red);

		newImage.push_back(image);
	}
	Image picture((char)0, (char)0, (char)2, (short)0, (short)0, (char)0, (short)0, (short)0,
		(short)512, (short)512, (char)24, (char)0, newImage);
	Write(writeTo, picture);
}



int main(){

	vector<Image> pictures;

	int passed = 0;

	/*============================================== 1 ===================================================*/
	Multiply("input/layer1.tga", "input/pattern1.tga", "output/part1.tga", pictures);

	cout << "Test #1";
	if (Compare("output/part1.tga", "examples/EXAMPLE_part1.tga", pictures)) {
		cout << "......Passed!" << endl;
 		passed++;
	}
	else {
		cout << "......Failed!" << endl;
	}


	/*============================================== 2 ===================================================*/
	Subtract("input/layer2.tga", "input/car.tga", "output/part2.tga", pictures);

	cout << "Test #2";
	if (Compare("output/part2.tga", "examples/EXAMPLE_part2.tga", pictures)) {
		cout << "......Passed!" << endl;
		passed++;
	}
	else {
		cout << "......Failed!" << endl;
	}


	/*============================================== 3 ===================================================*/
	Multiply("input/layer1.tga", "input/pattern2.tga", "temp/temp_part3.tga", pictures);

	Screen("input/text.tga", "temp/temp_part3.tga", "output/part3.tga", pictures);

	cout << "Test #3";
	if (Compare("output/part3.tga", "examples/EXAMPLE_part3.tga", pictures)) {
		cout << "......Passed!" << endl;
		passed++;
	}
	else {
		cout << "......Failed!" << endl;
	}


	

	/*============================================== 4 ===================================================*/
	Multiply("input/layer2.tga", "input/circles.tga", "temp/temp_part4.tga", pictures);

	Subtract("input/pattern2.tga", "temp/temp_part4.tga", "output/part4.tga", pictures);

	cout << "Test #4";
	if (Compare("output/part4.tga", "examples/EXAMPLE_part4.tga", pictures)) {
		cout << "......Passed!" << endl;
		passed++;
	}
	else {
		cout << "......Failed!" << endl;
	}


	/*============================================== 5 ===================================================*/
	Overlay("input/layer1.tga", "input/pattern1.tga", "output/part5.tga", pictures);

	cout << "Test #5";
	if (Compare("output/part5.tga", "examples/EXAMPLE_part5.tga", pictures)) {
		cout << "......Passed!" << endl;
		passed++;
	}
	else {
		cout << "......Failed!" << endl;
	}

	

	/*============================================== 6 ===================================================*/
	Read("input/car.tga", pictures);

	float blue6 = 0;
	float green6 = 0;
	float red6 = 0;

	Image imageA6 = pictures[pictures.size() - 1];

	vector<Image::Pixel> y6 = imageA6.GetPixels();

	size_t size6 = y6.size();

	vector<Image::Pixel> newImage6;

	for (size_t i = 0; i < size6; i++) {

		blue6 = (float)y6[i].GetBlue();

		green6 = (float)y6[i].GetGreen() + 200.0f;
		if (green6 > 255.0f) {
			green6 = 255.0f;
		}
		red6 = (float)y6[i].GetRed();

		Image::Pixel image6((unsigned char)blue6, (unsigned char)green6, (unsigned char)red6);

		newImage6.push_back(image6);
	}

	Image picture6 ((char)0, (char)0, (char)2, (short)0, (short)0, (char)0, (short)0, (short)0,
		(short)512, (short)512, (char)24, (char)0, newImage6);

	Write("output/part6.tga", picture6);

	cout << "Test #6";
	if (Compare("output/part6.tga", "examples/EXAMPLE_part6.tga", pictures)) {
		cout << "......Passed!" << endl;
		passed++;
	}
	else {
		cout << "......Failed!" << endl;
	}
	




	/*============================================== 7 ===================================================*/
	Read("input/car.tga", pictures);

	float blue7 = 0;
	float green7 = 0;
	float red7 = 0;

	Image imageA7 = pictures[pictures.size() - 1];

	vector<Image::Pixel> y7 = imageA7.GetPixels();

	size_t size7 = y7.size();

	vector<Image::Pixel> newImage7;

	for (size_t i = 0; i < size7; i++) {

		blue7 = (float)y7[i].GetBlue() * 0;

		green7 = (float)y7[i].GetGreen();

		red7 = (float)y7[i].GetRed() * 4;
		if (red7 > 255.0f) {
			red7 = 255.0f;
		}

		Image::Pixel image7((unsigned char)blue7, (unsigned char)green7, (unsigned char)red7);

		newImage7.push_back(image7);
	}

	Image picture7((char)0, (char)0, (char)2, (short)0, (short)0, (char)0, (short)0, (short)0,
		(short)512, (short)512, (char)24, (char)0, newImage7);

	Write("output/part7.tga", picture7);

	cout << "Test #7";
	if (Compare("output/part7.tga", "examples/EXAMPLE_part7.tga", pictures)) {
		cout << "......Passed!" << endl;
		passed++;
	}
	else {
		cout << "......Failed!" << endl;
	}





	/*============================================== 8.a ===================================================*/
	Read("input/car.tga", pictures);

	float blue8a = 0;
	float green8a = 0;
	float red8a = 0;

	Image imageA8a = pictures[pictures.size() - 1];

	vector<Image::Pixel> y8a = imageA8a.GetPixels();

	size_t size8a = y8a.size();

	vector<Image::Pixel> newImage8a;

	for (size_t i = 0; i < size8a; i++) {

		blue8a = ((((float)y8a[i].GetBlue() / 255.0f)) * 255.0f + 0.5f);

		green8a = (((float)y8a[i].GetGreen() / 255.0f)) * 255.0f + 0.5f;

		red8a = (((float)y8a[i].GetRed() / 255.0f)) * 255.0f + 0.5f;

		Image::Pixel image8a((unsigned char)red8a, (unsigned char)red8a, (unsigned char)red8a);

		newImage8a.push_back(image8a);
	}

	Image picture8a((char)0, (char)0, (char)2, (short)0, (short)0, (char)0, (short)0, (short)0,
		(short)512, (short)512, (char)24, (char)0, newImage8a);

	Write("output/part8_r.tga", picture8a);

	cout << "Test #8a";
	if (Compare("output/part8_r.tga", "examples/EXAMPLE_part8_r.tga", pictures)) {
		cout << "......Passed!" << endl;
		passed++;
	}
	else {
		cout << "......Failed!" << endl;
	}





	/*============================================== 8.b ===================================================*/
	Read("input/car.tga", pictures);

	float blue8b = 0;
	float green8b = 0;
	float red8b = 0;

	Image imageA8b = pictures[pictures.size() - 1];

	vector<Image::Pixel> y8b = imageA8b.GetPixels();

	size_t size8b = y8b.size();

	vector<Image::Pixel> newImage8b;

	for (size_t i = 0; i < size8b; i++) {

		blue8b = ((((float)y8b[i].GetBlue() / 255.0f)) * 255.0f + 0.5f);

		green8b = (((float)y8b[i].GetGreen() / 255.0f)) * 255.0f + 0.5f;

		red8b = ((((float)y8b[i].GetRed() / 255.0f))) * 255.0f + 0.5f;

		Image::Pixel image8b((unsigned char)green8b, (unsigned char)green8b, (unsigned char)green8b);

		newImage8b.push_back(image8b);
	}

	Image picture8b((char)0, (char)0, (char)2, (short)0, (short)0, (char)0, (short)0, (short)0,
		(short)512, (short)512, (char)24, (char)0, newImage8b);

	Write("output/part8_g.tga", picture8b);

	cout << "Test #8b";
	if (Compare("output/part8_g.tga", "examples/EXAMPLE_part8_g.tga", pictures)) {
		cout << "......Passed!" << endl;
		passed++;
	}
	else {
		cout << "......Failed!" << endl;
	}





	/*============================================== 8.c ===================================================*/
	Read("input/car.tga", pictures);

	float blue8c = 0;
	float green8c = 0;
	float red8c = 0;

	Image imageA8c = pictures[pictures.size() - 1];

	vector<Image::Pixel> y8c = imageA8c.GetPixels();

	size_t size8c = y8c.size();

	vector<Image::Pixel> newImage8c;

	for (size_t i = 0; i < size8c; i++) {

		blue8c = ((((float)y8c[i].GetBlue() / 255.0f)) * 255.0f + 0.5f);

		green8c = (((float)y8c[i].GetGreen() / 255.0f)) * 255.0f + 0.5f;

		red8c = ((((float)y8c[i].GetRed() / 255.0f))) * 255.0f + 0.5f;

		Image::Pixel image8c((unsigned char)blue8c, (unsigned char)blue8c, (unsigned char)blue8c);

		newImage8c.push_back(image8c);
	}

	Image picture8c((char)0, (char)0, (char)2, (short)0, (short)0, (char)0, (short)0, (short)0,
		(short)512, (short)512, (char)24, (char)0, newImage8c);

	Write("output/part8_b.tga", picture8c);

	cout << "Test #8c";
	if (Compare("output/part8_b.tga", "examples/EXAMPLE_part8_b.tga", pictures)) {
		cout << "......Passed!" << endl;
		passed++;
	}
	else {
		cout << "......Failed!" << endl;
	}





	/*============================================== 9 ===================================================*/
	Read("input/layer_red.tga", pictures);
	Read("input/layer_green.tga", pictures);
	Read("input/layer_blue.tga", pictures);

	float blue9 = 0;
	float green9 = 0;
	float red9 = 0;

	Image image9r = pictures[pictures.size() - 3];
	Image image9g = pictures[pictures.size() - 2];
	Image image9b = pictures[pictures.size() - 1];

	vector<Image::Pixel> x9 = image9b.GetPixels();
	vector<Image::Pixel> y9 = image9g.GetPixels();
	vector<Image::Pixel> z9 = image9r.GetPixels();

	size_t size9 = x9.size();

	vector<Image::Pixel> newImage9;

	for (size_t i = 0; i < size9; i++) {

		blue9 = ((((float)x9[i].GetBlue() / 255.0f)) * 255.0f + 0.5f);

		green9 = (((float)y9[i].GetGreen() / 255.0f)) * 255.0f + 0.5f;

		red9 = ((((float)z9[i].GetRed() / 255.0f))) * 255.0f + 0.5f;

		Image::Pixel image9((unsigned char)blue9, (unsigned char)green9, (unsigned char)red9);

		newImage9.push_back(image9);
	}

	Image picture9((char)0, (char)0, (char)2, (short)0, (short)0, (char)0, (short)0, (short)0,
		(short)600, (short)398, (char)24, (char)0, newImage9);

	Write("output/part9.tga", picture9);

	cout << "Test #9";
	if (Compare("output/part9.tga", "examples/EXAMPLE_part9.tga", pictures)) {
		cout << "......Passed!" << endl;
		passed++;
	}
	else {
		cout << "......Failed!" << endl;
	}




	/*============================================== 10 ===================================================*/
	Read("input/text2.tga", pictures);

	Image image10 = pictures[pictures.size() - 1];

	vector<Image::Pixel> newImage10 = image10.GetPixels();

	reverse(newImage10.begin(), newImage10.end());

	Image picture10((char)0, (char)0, (char)2, (short)0, (short)0, (char)0, (short)0, (short)0,
		(short)184, (short)384, (char)24, (char)0, newImage10);

	Write("output/part10.tga", picture10);

	cout << "Test #10";
	if (Compare("output/part10.tga", "examples/EXAMPLE_part10.tga", pictures)) {
		cout << "......Passed!" << endl;
		passed++;
	}
	else {
		cout << "......Failed!" << endl;
	}
		cout <<	"Test results: " << passed << " / " << "12";
}
/*	Read(layerA, pictures);
	Read(layerB, pictures);

	float blue = 0;
	float green = 0;
	float red = 0;

	Image imageA = pictures[pictures.size() - 2];
	Image imageB = pictures[pictures.size() - 1];

	vector<Image::Pixel> x = imageB.GetPixels();
	vector<Image::Pixel> y = imageA.GetPixels();

	size_t size = x.size();

	vector<Image::Pixel> newImage;

	float A = 0;
	float B = 0;

	for (size_t i = 0; i < size; i++){

		A = (float)y[i].GetBlue() / 255.0f;
		B = (float)x[i].GetBlue() / 255.0f;
		
		if (A > 0.5f) {
			blue = 2 * (A * B) * 255.0f + 0.5f;
		}
		else {
			blue = (1 - 2 * (1 - A) * (1 - B)) * 255.0f + 0.5f;
		}
		if (blue < 0.0f) {
			blue = 0.0f;
		}
		if (blue > 255.0f) {
			blue = 255.0f;
		}

		A = (float)y[i].GetGreen() / 255.0f;
		B = (float)x[i].GetGreen() / 255.0f;


		if (A > 0.5f) {
			green = 2 * (A * B) * 255.0f + 0.5f;
		}
		else {
			green = (1 - 2 * (1 - A) * (1 - B)) * 255.0f + 0.5f;
		}
		if (green < 0.0f) {
			green = 0.0f;
		}
		if (green > 255.0f) {
			green = 255.0f;
		}

		A = (float)y[i].GetRed() / 255.0f;
		B = (float)x[i].GetRed() / 255.0f;

		if (A > 0.5f) {
			red = 2 * (A * B) * 255.0f + 0.5f;
		}
		else {
			red = (1 - 2 * (1 - A) * (1 - B)) * 255.0f + 0.5f;
		}
		if (red < 0.0f) {
			red = 0.0f;
		}
		if (red > 255.0f) {
			red = 255.0f;
		}

		Image::Pixel image((unsigned char)blue, (unsigned char)green, (unsigned char)red);

		newImage.push_back(image);
	}

	Image picture((char)0, (char)0, (char)2, (short)0, (short)0, (char)0, (short)0, (short)0,
		(short)512, (short)512, (char)24, (char)0, newImage);

	Write(writeTo, picture);*/