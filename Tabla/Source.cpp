#include <iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>


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


	cv::Mat lut(1, 256, CV_8UC1);
	uchar* plut = lut.data;
	for (int i = 0; i < 256; i++) {
		double x = (double)i / 256.0;
		plut[i] = cvRound( 256.0 * std::pow(x, factor));
	}
	cv::Mat img;
	cv::cvtColor(image, img, cv::COLOR_BGR2YUV);

	std::vector<cv::Mat> YUV_planes;
	cv::split(img, YUV_planes);
	cv::LUT(YUV_planes[0], lut, YUV_planes[0]);

	
	
	endTicks = GetTickCount();
	milisecs = endTicks - startTicks;
	printf("Tiempo transcurrido: %lf\n", milisecs / 1000.0);
	cv::Mat out;
	cv::merge(YUV_planes, out);
	cv::imshow("Remezclado", out);
    
    cv::waitKey(0);
	return 0;
}