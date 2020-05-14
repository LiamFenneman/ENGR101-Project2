#include "video_proc.hpp"
#include <math.h>

int redPositionError(ImagePPM image);
int* getRedPixelIndexes(ImagePPM image);
int countRedPixels(ImagePPM img);
bool isPixelRed(Pixel p);

int main(){
	int rubyRedCount = 0;
	int* rubyRedIndexes;
    int nFrames = 20;
    for ( int iFrame = 0; iFrame < nFrames ; iFrame++){
		// produce file name of "X.ppm" type where X goes from 0 to number of images
		std::string fileName;
		std::ostringstream stringStream;
        stringStream <<iFrame<<".ppm";
        fileName = stringStream.str();
		std::cout<<" File::"<<fileName<<std::endl;
		// open image file
		OpenPPMFile(fileName);
	
		int sum_red = countRedPixels(image);
		
		if (iFrame == 0) {
			rubyRedCount = countRedPixels(image);
			rubyRedIndexes = getRedPixelIndexes(image);
			cout<<"Ruby is present"<<endl;
			continue;
		}
	    
	    if (abs(sum_red-rubyRedCount) < 500 && redPositionError(image) < 100) {
			cout<<"Ruby is present."<<endl;
		}
		else {
			cout<<"Ruby is missing!"<<endl;
		}
	}
	
	return 0;
}

int redPositionError(ImagePPM image) {
	int error = 0;
	
	return error;
}

// returns an array of indexes of pixels which are red
int* getRedPixelIndexes(ImagePPM image) {
	int redCount = countRedPixels(image);
	int* indexes = new int[redCount];
	
	Pixel curPix;
	int index;
	int i = 0;
	for (int row = 0; row < image.height; row++) {
		for ( int column = 0; column < image.width; column++) {
			curPix = get_pixel(row,column);
			index = row*column + column;
			if (isPixelRed(curPix)) {
				indexes[i] = index;
				i++;
			}
		}
	}
	return indexes;
}

// count the number of red pixels in the image
int countRedPixels(ImagePPM image) {
	int c = 0;
	Pixel curPix;
	for (int row = 0; row < image.height; row++) {
		for ( int column = 0; column < image.width; column++) {
			curPix = get_pixel(row,column);
			if (isPixelRed(curPix))
				c++;
		}
	}
	return c;
}

// checks if the red value is greater than both green and blue
// 10 is my threshold for a red pixel - this means a color is only red
// when it's red component is 10 more than both green and blue
bool isPixelRed(Pixel p) {
	int redThreshold = 10;
	int r = (int)p.red - redThreshold;
	int g = (int)p.green;
	int b = (int)p.blue;
	
	if (r > g && r > b)
		return true;
	
	return false;
		
}
