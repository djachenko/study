#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>

int main()
{
	auto image = cv::imread("test.jpg");

	if (image.empty())
	{
		std::cout << "Error with image..." << std::endl;

		return 1;
	}

	cv::Mat saltpepper_noise = cv::Mat::zeros(image.rows, image.cols, CV_8U);
	randu(saltpepper_noise, 0, 255);
	
	cv::Mat black = saltpepper_noise<5;
	cv::Mat white = saltpepper_noise>250;
	
	auto saltpepper_image = image.clone();
	
	saltpepper_image.setTo(255, white);
	saltpepper_image.setTo(0, black);

	imshow("", saltpepper_image);

//	image = saltpepper_image;
	
	cv::Mat gray;

	cvtColor(image, gray, CV_RGB2GRAY);

	cv::Mat grad_x;
	cv::Mat grad_y;

	auto ddepth = CV_16S;

	auto x_derivative_order = 1;
	auto y_derivative_order = 0;
	auto kernel_size = 3;

	Sobel(gray, grad_x, ddepth, x_derivative_order, y_derivative_order, kernel_size);
	

	x_derivative_order = 0;
	y_derivative_order = 1;

	Sobel(gray, grad_y, ddepth, x_derivative_order, y_derivative_order, kernel_size);

	cv::Mat abs_grad_x;
	cv::Mat abs_grad_y;

	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);

	cv::Mat grad;

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad, -1);

	imshow("lab2", grad);

	cv::Scalar mean;
	cv::Scalar standart_deviation;

	meanStdDev(grad, mean, standart_deviation);

	std::cout << mean << std::endl;
	std::cout << standart_deviation << std::endl;

	cv::waitKey(0);

	return 0;
}