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
	
	std::vector<cv::Mat> bgr_planes;
	cv::split(image, bgr_planes);
	cv::LUT(bgr_planes[0], lut, bgr_planes[0]);
	cv::LUT(bgr_planes[1], lut, bgr_planes[1]);
	cv::LUT(bgr_planes[2], lut, bgr_planes[2]);

	cv::Mat out;
	cv::merge(bgr_planes, out);
	cv::imshow("Remezclado", out);
	
	endTicks = GetTickCount();
	milisecs = endTicks - startTicks;
	printf("Tiempo transcurrido: %lf\n", milisecs / 1000.0);

    
    cv::waitKey(0);
	return 0;
}