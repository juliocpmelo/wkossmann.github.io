#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  Mat image;
  int width, height;
  int nobjects,r,g,b;
  
  CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  cvtColor(image, image, CV_GRAY2RGB);
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }

  width=image.size().width;
  height=image.size().height;


  p.x=0;
  p.y=0;

  // busca objetos com buracos presentes
  nobjects=0;
  r = 0;
  g = 0;
  b = 0;

  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<Vec3b>(i,j)[0] == 255 && image.at<Vec3b>(i,j)[1] == 255 && image.at<Vec3b>(i,j)[2] == 255){
  		// achou um objeto
  		nobjects++;
      r++;
      if(r>255){
        g++;
        r=0;
      }
      if(g>255){
        b++;
        g=0;
      }
  		p.x=j;
  		p.y=i;
  		floodFill(image,p,CV_RGB(r,g,b));
  	  }
  	}
  }
  imshow("image", image);
  imwrite("saida4-1.png", image);
  waitKey();
  return 0;
}
