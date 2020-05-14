#include "video_proc.hpp"
#include <math.h>

struct BoundingBox {
	int x1, x2, y1, y2; // absolute values of bounding box
	
	// simple geometric functions
	int getWidth() {return x2-x1;}
	int getHeight() {return y2-y1;}
	int getArea() {return getWidth() * getHeight();}
	
	// this detects the shape
	bool isSimilarSize(BoundingBox bb, int threshold) {
		bool similarWidth = abs(bb.getWidth()-getWidth()) < threshold;
		bool similarHeight = abs(bb.getHeight()-getHeight()) < threshold;
		return similarWidth && similarHeight;
	}
};

BoundingBox findBoundingBox(ImagePPM image);
bool isPixelRed(Pixel p);

// Challenge: find bounding box for ruby

int main(){
	BoundingBox ruby;
	int lastX;
    int nFrames = 20;
    for ( int iFrame = 0; iFrame < nFrames ; iFrame++) {
		// produce file name of "X.ppm" type where X goes from 0 to number of images
		std::string fileName;
		std::ostringstream stringStream;
        stringStream <<iFrame<<".ppm";
        fileName = stringStream.str();
		std::cout<<" File::"<<fileName<<std::endl;
		// open image file
		OpenPPMFile(fileName);
		
		BoundingBox bb = findBoundingBox(image);
		
		if (iFrame == 0) {
			ruby = bb;
			lastX = bb.x1;
		}
		
		int shift = abs(lastX-bb.x1);
		lastX = bb.x1;
		if (shift > 30 || !bb.isSimilarSize(ruby, 30)) {
			cout<<"Ruby is being stolen."<<endl;
		}
		else if (shift > 1000) {
			cout<<"Ruby has been stolen."<<endl;
		}
		else {
			cout<<"Ruby is present."<<endl;
		}
	}
	
	return 0;
}

BoundingBox findBoundingBox(ImagePPM image) {
	BoundingBox bb;
	Pixel curPix;
	int minX = 25000;
	int maxX = 0;
	int minY = 25000;
	int maxY = 0;
	for (int row = 0; row < image.height; row++) {
		for ( int col = 0; col < image.width; col++) {
			curPix = get_pixel(row,col);
			if (!isPixelRed(curPix)) continue;
			
			if (col < minX) minX = col;
			else if (col > maxX) maxX = col;
			if (row < minY) minY = row;
			else if (row > maxY) maxY = row;
		}
	}
	bb.x1 = minX;
	bb.x2 = maxX;
	bb.y1 = minY;
	bb.y2 = maxY;
	return bb;
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
