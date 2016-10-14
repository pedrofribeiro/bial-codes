/**
Sample code, produced in order to test my abilities using the BIAL environment.
*/
#include <iostream>
#include "Image.hpp"
#include "Color.hpp"
#include "FileBasics.hpp"

using namespace Bial;
using namespace std;


int main(int argc, char* argv[]){

//holds: the min and max values of the image
//the upperBound and lowerBound values provided by the user
//the ranges from both pairs of extreme values
int min = 0, max = 0, upperBound = 0, lowerBound = 0, rangeOfImage = 0, rangeOfBounds = 0;

if(argc != 5){
  cout << "There haven't been provided enough arguments to the function. \n" << endl;
  cout << "The input should be of the form: <img1> <newImg> <upperBound> <lowerBound> \n" << endl;
  return ( 0 );
}

//reads the image
Image<int> imA( Read<int>( argv[1] ) );

//finding the max and min values of the image
for(size_t t = 0; t < imA.size(); ++t){
  if( imA[t] < min ){
    min = imA[t];
    continue; //no need to further compare within this iteration.
  }
  if( imA[t] > max ){
    max = imA[t];
  }
}

//constants needed to the normalization proccess
upperBound = atoi(argv[4]);
lowerBound = atoi(argv[3]);
rangeOfImage = max - min;
rangeOfBounds = upperBound - lowerBound;


//normalizing the image
for(size_t k = 0; k < imA.size(); ++k){
  //new = lowerBound + { [(current - min)/(max - min)] * (upperBound - lowerBound) }
  imA[k] = lowerBound +  ((imA[k] - min) / rangeOfImage) * rangeOfBounds;
}

//creates the resulting image using the same dimensions of the original image
Image<int> imB( imA );

//recording the new image
Write (imB, argv[2]);

  return ( 0 );
}
