#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int nobjects;
  
  CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  //retirar elementos das bordas:
  for(int i=0; i<height; i++){
    if(image.at<uchar>(i,0) == 255){
      p.x=0;
      p.y=i;
      floodFill(image,p,0);
    }
    if(image.at<uchar>(i,width-1) == 255){
      p.x=width-1;
      p.y=i;
      floodFill(image,p,0);
    }
  }
  for(int j=0; j<width; j++){
    if(image.at<uchar>(0,j) == 255){
      p.x=j;
      p.y=0;
      floodFill(image,p,0);
    }
    if(image.at<uchar>(height-1,j) == 255){
      p.x=j;
      p.y=height-1;
      floodFill(image,p,0);
    }
  }
  imshow("passo1", image);
  imwrite("passo1.png", image);




  p.x=0;
  p.y=0;

  // busca por bolha c ou sem buraco
  nobjects=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
  		// achou um objeto
  		nobjects++;
  		p.x=j;
  		p.y=i;
  		floodFill(image,p,nobjects);
  	  }
  	}
  }
  imshow("passo2", image);
  imwrite("passo2.png", image);


  bool flag = false;
  //preenche o fundo com com o ultimo ton de cinza encontrado +1 
  //para poder encontrar os buracos posteriormente
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 0){
        p.x=j;
        p.y=i;
        floodFill(image,p,nobjects+1);
        flag = true;
        break;
      }
    }
    if(flag) break;
  }
  imshow("passo3", image);
  imwrite("passo3.png", image);


  int nburaco = 0;
  int pixAnterior=0;
  bool temBuraco=false;
  for(int k=nobjects; k>0; k--){
    for(int i=0; i<height; i++){
      for(int j=0; j<width; j++){
        if(pixAnterior==k){
          if(image.at<uchar>(i,j) == 0){
            temBuraco=true;
            p.x=j;
            p.y=i;
            floodFill(image,p,k+nobjects+1);
          }
        }
        pixAnterior = image.at<uchar>(i,j);
      }
    }
    if(temBuraco){
      nburaco++;
    }
    temBuraco=false;
  }

  cout << "Numero de bolhas total:     " << nobjects << endl;
  cout << "Numero de bolhas c/ buracos:" << nburaco  << endl;
  cout << "Numero de bolhas s/ buracos:" << nobjects - nburaco << endl;

  imshow("passo4", image);
  imwrite("passo4.png", image);
  waitKey();
  return 0;
}
