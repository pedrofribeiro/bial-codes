/**
This is a very simple filter, the moving mean. This code is intended
as practice in the BIAL environment.
*/

#include <iostream>
#include "Image.hpp"
#include "FileBasics.hpp"
#include "Color.hpp"

using namespace Bial;
using namespace std;

int main(int argc, char* argv[]){

if (argc != 3) {
  cout << "Not enough arguments provided.\n" << endl;
  cout << "The input should be of the form: <img1> <newImg>" << endl;
  return (0);
}

//read the image from the user's input
Image<int> imA( Read<int>(argv[1]) );

//applying the filter with 2 neighbours' influence
for (size_t t = 0; t < imA.size(); ++t){
  //first pixel
  //side-note: first "oh no" moment with c++. It does not allow double usage of
  //the increment and decrement operators, such as ++t++ like C allows.
  if (t == 0) {
    imA[t] = (imA[t+1] + imA[t+2]) * 0.5;
    continue; // no need to further comparing within this iteration
  }
  //last pixel
  if (t == imA.size()) {
    imA[t] = (imA[t-1] + imA[t-2]) * 0.5;
    continue; // no need to further comparing within this iteration
  }
  //all other pixels
  //new = arithmetic mean of values of the anterior and posterior neighbours
  imA[t] = (imA[t-1] + imA[t+1]) * 0.5;
}

//creating the new image, with exactly the same dimensions of the original
Image<int> imB( imA );

//writing the new image information
Write (imB, argv[2]);

  return ( 0 );
}
