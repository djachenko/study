#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <ctime>

int main()
{
	auto image = cv::imread("test.jpg");

	if (image.empty())
	{
		std::cout << "Error with image..." << std::endl;
		
		return 1;
	}

	cv::Vec3b color(0, 0, 0);
	auto count = 0;

	for (auto i = image.begin<cv::Vec3b>(); i != image.end<cv::Vec3b>(); ++i)
	{
		if (*i == color)
		{
			count++;
		}
	}

	std::cout << color << ": " << count << std::endl;

	auto width = image.cols;
	auto height = image.rows;

	srand(time(nullptr));

	for (auto i = rand() % 10000; i >= 0; i--)
	{
		cv::Scalar primitiveColor(rand() % 255, rand() % 255, rand() % 255);
		
		circle(image, cv::Point(rand() % width, rand() % height), 20, primitiveColor);
	}

	imshow("lab1", image);

	cv::waitKey(0);

	return 0;
}