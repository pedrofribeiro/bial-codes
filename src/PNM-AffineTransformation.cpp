/**
New test code. The purpose of this code is to implement
Euclidean Transformations using the BIAL environment
Done already: Translation
*/

#include <iostream>
#include "Image.hpp"
#include "FileImage.hpp"
#include "Color.hpp"

using namespace Bial;
using namespace std;

int main(int argc, char* argv[]){

// variables used:
// imA, imB, extension, dimX, dimY, t, u, translation;


  if(argc != 3){
    cout << "Insufficient number of parameters given to the function." << endl;
    cout << "The input should be of the form: <img> <out>" << endl;
    return( 0 );
  }

  //reading the image from the user input
  Image<int> imA( Read<int>(argv[1]) );

  //dimension's control variables for the new, extended, image
  //translation variable, pondered by the extension
  //shoulb both of them (extension, translation) be read from stdio?
  const size_t extension = 200; //cannot be altered during exec time.
  const size_t translation = extension/2; //integer division,it's ok.
  size_t dimX = 0, dimY = 0;

  dimX = imA.size(0) + extension;
  dimY = imA.size(1) + extension;

  //creating a new image using the user informed one as a basis,
  //extending it in all dimensions by a fixed number of pixels
  //making the background white, to make it easier to validade
  //the effectiveness of the translation proccess
  Image<int> imB( dimX , dimY );
  imB.Set(255);

  //since the sizes of the images are different, I cannot use
  //imA += imB;
  //copying the data from imA to imB
  for(size_t t = 0; t < imA.size(0); ++t){
    for(size_t u = 0; u < imA.size(1); ++u){
      imB(t, u) = imA(t, u);
    }
  }

  //translating all pixels 100 positions to the right
  //and 100 positions down.This is equivalent to the vector function
  //mapping: f(x,y) = <g(x),h(y)> , g(x) = 200+x , h(y) = 200+y
  for(size_t t = 0; t < imB.size(0); ++t){
    for(size_t u = 0; u < imB.size(1); ++u){
      imB(t+translation, u+translation) = imB(t, u);
    }
  }

  Write(imB, argv[2]);

  return(0);
}
