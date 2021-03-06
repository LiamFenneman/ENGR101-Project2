#include "video_proc.hpp"
#include <math.h>

bool isPixelRed(Pixel p);

int main(){
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
		
	
		int sum_red = 0;
        Pixel curPix;
        for ( int row =0 ; row < image.height ; row++)
	    {	
		  for ( int column = 0; column < image.width ; column++)
		  {
			  curPix = get_pixel(row,column);
			  
			  if (isPixelRed(curPix)==true){
				  sum_red++;
			  }
		   }	  
	    }
	    
	    if (sum_red > 1000) {
			cout<<"Ruby is present."<<endl;
		}
		else {
			cout<<"Ruby is missing!"<<endl;
		}
	}
	
	return 0;
}

bool isPixelRed(Pixel p) {
	int r = (int)p.red - 3;
	int g = (int)p.green;
	int b = (int)p.blue;
	
	if (r > g && r > b)
		return true;
	
	return false;
		
}
