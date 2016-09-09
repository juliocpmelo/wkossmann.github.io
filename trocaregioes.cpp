#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int, char**){
	Mat image, image2;
	int largura, altura;


	image = imread("bolhas.png", CV_LOAD_IMAGE_GRAYSCALE);
	if(!image.data){
		cout << "Nao foi possivel abrir a imagem!" << endl;		
		return 1;
	}

	//Clonar a matriz para fazer as mudanças de regioes.
	image2 = image.clone();
	
	namedWindow("Janela01",WINDOW_AUTOSIZE);

	//Armazenar tamanho da imagem para controle de troca.
	largura = image.size().width;
	altura  = image.size().height;

	//Percorrer toda a matriz auxiliar para trocar as regioes
	for(int i=0; i<largura ; i++){
		for(int j=0 ; j<altura ; j++){
			// Regiao superior esquerda da imagem 2 receber
			// a regiao inferior direita da imagem original.
			if(i<largura/2 && j<altura/2){
				image2.at<uchar>(i,j) = 
					image.at<uchar>(i+largura/2,j+altura/2);
			}else
			// Regiao inferior esquerda da imagem 2 receber
			// a regiao superior direita da imagem original.
			if(i<largura/2 && j>=altura/2){
				image2.at<uchar>(i,j) = 
					image.at<uchar>(i+largura/2,j-altura/2);
			}else
			// Regiao superior direita da imagem 2 receber 
			//a regiao inferior esquerda da imagem original.
			if(i>=largura/2 && j<altura/2){
				image2.at<uchar>(i,j) = 
					image.at<uchar>(i-largura/2,j+altura/2);
			}else
			// Regiao inferior direita da imagem 2 receber 
			//a regiao superior esquerda da imagem original.
			if(i>=largura/2 && j>=altura/2){
				image2.at<uchar>(i,j) = 
					image.at<uchar>(i-largura/2,j-altura/2);
			}			
		}
	}

	imwrite("saida3-2.png", image2);
	imshow("Janela01", image2);
	waitKey();
	
	return 0;
}
