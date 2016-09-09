#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int, char**){
	Mat image;
	int x1,y1 ,x2,y2;	
	image = imread("biel.png", CV_LOAD_IMAGE_GRAYSCALE);
	if(!image.data){
		cout << "Nao foi possivel abrir a imagem!" << endl;		
		return 1;
	}

	//Solicita para o usuário a regiao para realizar o negativo.
	cout << "Informe x1 e y1: " << endl;
	cin >> x1 >> y1;	
	cout << "Informe x2 e y2: " << endl;
	cin >> x2 >> y2;
	
	namedWindow("Janela01",WINDOW_AUTOSIZE);

	//Verifica se há necessidade de troca de 
	//valores para for ser sempre crescente.
	if(x1 > x2){
		int aux;
		aux = x2;
		x2 = x1;
		x1 = aux;
	}
	if(y1 > y2){
		int aux;
		aux = y2;
		y2 = y1;
		y1 = aux;
	}

	//Loop para preenchimento da regiao escolhida
	// com o negativo de cada pixel.
	for(int i=x1 ; i<x2 ; i++){
		for(int j=y1 ; j<y2 ; j++){
			image.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);
		}
	}

	imwrite("saida3-1.png", image);
	imshow("Janela01", image);
	waitKey();
	
	return 0;
}
