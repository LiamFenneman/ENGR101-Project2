#include "video_proc.hpp"
#include <math.h>

int main(){

	float avg_redness = 0;	// average redness of images looped over
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
		
	
		int totred = 0;
		int totint = 0;
		float redness = 0;
        Pixel curPix;
        for ( int row =0 ; row < image.height ; row++)
	    {	
		  for ( int column = 0; column < image.width ; column++)
		  {
			  curPix = get_pixel(row,column);
			  
			  totred = totred + (int)curPix.red;
			  totint = totint + ((int)curPix.red+(int)curPix.green+(int)curPix.blue)/3;
			  redness = (float)totred/(3.0*(float)totint);
			  
			  //totred = totred + (int)get_pixel(row,column,0);
			  //totint = totint + (int)get_pixel(row,column,3);
			  //redness = (float)totred/(3.0*(float)totint);
		   }	  
	    }
	    
	    // check the difference between average redness and the redness of the current image
	    // if the difference is more than 0.005 the ruby is defined as mising.
	    // since this is using an average this check will only be applied when checking the second frame
	    // this means i assumed the ruby is there during the first frame.
	    if (iFrame > 0 && std::abs(avg_redness-redness) > 0.005) {
			cout<<"Ruby is missing!"<<endl;
		}
		else if (iFrame > 0) {
			avg_redness = (avg_redness+redness)/(float)2;
			cout<<"Ruby is present."<<endl;
		}
		else {
			avg_redness = redness;
			cout<<"Ruby is present."<<endl;
		}
	}
	
	return 0; 
}
