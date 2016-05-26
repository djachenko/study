
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
	auto image = cv::imread("rice.jpg");

	cv::Mat src_gray;

	cvtColor(image, src_gray, CV_RGB2GRAY);

	cv::Mat dst;
	
	threshold(src_gray, dst, 120, 255, CV_THRESH_BINARY);

	cv::Mat distanceTransformed;

	distanceTransform(dst, distanceTransformed, CV_DIST_L2, CV_DIST_MASK_PRECISE);

	cv::Mat normalized;

	normalize(distanceTransformed, normalized, 0, 1, cv::NORM_MINMAX);

	cv::Mat transformedBinary;

	threshold(distanceTransformed, transformedBinary, 9, 1, CV_THRESH_BINARY);

	std::vector<std::vector<cv::Point2i>> contours;

	cv::Mat binaryForContours;

	transformedBinary.convertTo(binaryForContours, CV_8UC1);

	findContours(binaryForContours, contours, CV_RETR_CCOMP, cv::CHAIN_APPROX_NONE);

	cv::Mat contouredImage(image);

	for (size_t i = 0; i < contours.size(); i++)
	{
		drawContours(contouredImage, contours, static_cast<int>(i), cv::Scalar::all(static_cast<int>(i)+1), -1);
	}

	std::cout << "There are " << contours.size() << " contours" << std::endl;

	imshow("lab3", contouredImage);

	cv::waitKey(0);

	return 0;
}

