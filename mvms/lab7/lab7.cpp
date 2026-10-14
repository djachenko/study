#include<vector>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>

cv::Mat mixcolors(const std::vector<cv::Mat> &channels, const int &r, const int &g, const int &b)
{
	std::vector<cv::Mat>rgb;

	rgb.push_back(channels[b - 1]);
	rgb.push_back(channels[g - 1]);
	rgb.push_back(channels[r - 1]);

	cv::Mat color;

	cv::merge(rgb, color);

	return color;
}


int main(int argc, char*argv[])
{
	std::vector<cv::Mat> pseudocolors(7);

	for (auto i = 0; i < 7; i++)
	{
		auto tempMat = cv::imread("tm/small/p149r22_5t19890905_nn" + std::to_string(i + 1) + "s.tif", CV_LOAD_IMAGE_GRAYSCALE);

		tempMat.convertTo(pseudocolors[i], CV_32F);
	}

	auto img = mixcolors(pseudocolors, 4, 5, 1);

	cv::Mat normalized;

	normalize(img, normalized, 0, 1, cv::NORM_MINMAX);

	imshow("Lab 7: 7 2 1", normalized);

#define NIR 3
#define RED 2

	auto ndvi = (pseudocolors[NIR] - pseudocolors[RED]) / (pseudocolors[NIR] + pseudocolors[RED]);
	auto rvi = pseudocolors[NIR] / pseudocolors[RED];
	auto dvi = pseudocolors[NIR] - pseudocolors[RED];

	normalize(ndvi, normalized, 0, 1, cv::NORM_MINMAX);

	imshow("Lab 7: NDVI", normalized);

	normalize(rvi, normalized, 0, 1, cv::NORM_MINMAX);

	imshow("Lab 7: RVI", normalized);

	normalize(dvi, normalized, 0, 1, cv::NORM_MINMAX);

	imshow("Lab 7: DVI", normalized);

	cv::Mat distrib = cv::Mat::zeros(256, 256, CV_32F);

	for (auto y = 0; y < pseudocolors[RED].rows; y++)
	{
		for (auto x = 0; x < pseudocolors[RED].cols; x++)
		{
			auto nir = static_cast<int>(pseudocolors[NIR].at<float>(y, x));
			auto red = static_cast<int>(pseudocolors[RED].at<float>(y, x));

			distrib.at<float>(nir, red)++;
		}
	}

	distrib.at<float>(0, 0) = 0;

//	for (auto y = 0; y < distrib.rows; y++)
//	{
//		for (auto x = 0; x < distrib.cols; x++)
//		{
//			auto val = distrib.at<int>(y, x);
//			
//			if (val > 0)
//			{
//				std::cout << x << ", " << y << ": " << val << std::endl;
//			}
//		}
//	}

	normalize(distrib, normalized, 0, 1, cv::NORM_MINMAX);

	imshow("Lab7: terrain", normalized);

	cv::waitKey();

	return 0;
}