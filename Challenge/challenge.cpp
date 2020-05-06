#include "video_proc.hpp"
#include <math.h>
#include <vector>

bool isPixelRed(Pixel p);

int main(){
	vector<int> redPixelTarget;
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
		
        Pixel curPix;
        int iPixel = 0;
        int sum_red = 0;
        for ( int row =0 ; row < image.height ; row++)
	    {	
		  for ( int column = 0; column < image.width ; column++)
		  {
			  curPix = get_pixel(row,column);
			  if (isPixelRed(curPix)) {
				  if(iFrame == 0)
					redPixelTarget.push_back(iPixel);
				  sum_red++;
			  }
			  
			  iPixel++;
		   }
	    }
	    
	    cout<<redPixelTarget.size()-sum_red<<endl;
	    
	    if (std::abs(10-sum_red) > 100) {
			cout<<"Missing"<<endl;
		}
		else {
			cout<<"Present"<<endl;
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
