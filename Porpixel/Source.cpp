#include <iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>

float funciongamma(float pixel, float factorgamma) {
	float  s = std::pow(pixel/255, factorgamma);
	return s;
}
int main(int argc, char** argv)
{
	// se carga la imagen ingresada por comando
std::cout << "ingrese foto a procesar" << std::endl;
	std::string ruta;
	std::cin >> ruta;
	cv::Mat image = cv::imread(ruta, 1);

	std::cout << "ingrese factor" << std::endl;
	float factor;
	std::cin >> factor;

	// verificar si la imagen ha sida cargada correctamente 
	if (image.empty())
	{
		printf("No image data \n");
		return -1;
	}
	unsigned int startTicks, endTicks;
	unsigned int milisecs;
	startTicks = GetTickCount();

	cv::Mat_<cv::Vec3b> _I = image;
	
     for (int i = 0; i < image.rows; ++i)
	 for (int j = 0; j < image.cols; ++j) {
		_I(i, j)[0] = funciongamma(_I(i, j)[0], factor)*255;
		_I(i, j)[1] = funciongamma(_I(i, j)[1], factor)*255;
	    _I(i, j)[2] = funciongamma(_I(i, j)[2], factor)*255;
		
	}
 image = _I;




 cv::imshow("imagen", image);
 endTicks = GetTickCount();
 milisecs = endTicks - startTicks;
 printf("Tiempo transcurrido: %lf\n", milisecs / 1000.0);
    cv::waitKey(0);
	return 0;
}