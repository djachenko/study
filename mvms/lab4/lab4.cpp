#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>
#include <fstream>

const double PI = std::acos(-1);

cv::Mat rotate(cv::Mat &img, const double &angle)
{
	auto radians = angle * PI / 180.0;

	auto sine = abs(std::sin(radians));
	auto cosine = abs(std::cos(radians));

	auto newWidth = static_cast<int>(img.cols * cosine + img.rows * sine);
	auto newHeight = static_cast<int>(img.cols * sine + img.rows * cosine);

	cv::Mat targetMat = cv::Mat::zeros(cv::Size(std::max(newWidth, img.cols), std::max(newHeight, img.rows)), img.type());

	auto offsetX = (newWidth - img.cols) / 2;
	auto offsetY = (newHeight - img.rows) / 2;

	if (offsetX < 0)
	{
		offsetX = 0;
	} 
	
	if (offsetY < 0)
	{
		offsetY = 0;
	}

	img.copyTo(targetMat.rowRange(offsetY, offsetY + img.rows).colRange(offsetX, offsetX + img.cols));

	cv::Point2f center(targetMat.cols / 2.0, targetMat.rows / 2.0);
	auto rotationMatrix = getRotationMatrix2D(center, angle, 1);

	cv::Mat result;

	warpAffine(targetMat, result, rotationMatrix, cv::Size(newWidth, newHeight));

	return result;
}

int main(int argc, char* argv[])
{
	auto img = cv::imread("pic.jpg");

	cv::Mat img_rotated = rotate(img, 30);

	cv::ORB orb;

	std::vector<cv::KeyPoint> keyPoints;
	orb.detect(img, keyPoints);

	cv::Mat descriptors;
	orb.compute(img, keyPoints, descriptors);

	std::vector<cv::KeyPoint> keyPoints_rotated;
	orb.detect(img_rotated, keyPoints_rotated);

	cv::Mat descriptors_rotated;
	orb.compute(img_rotated, keyPoints_rotated, descriptors_rotated);

	cv::BFMatcher matcher(cv::NORM_HAMMING);

	std::vector<std::vector<cv::DMatch>> matches;
	matcher.knnMatch(descriptors, descriptors_rotated, matches, 2);

	std::vector<cv::DMatch> goodMatches;

	for (auto i : matches)
	{
		if (i[0].distance < 50)
		{
			goodMatches.push_back(i[0]);
		}
	}

	cv::Mat res;

	drawMatches(img, keyPoints, img_rotated, keyPoints_rotated, goodMatches, res);
	imshow("Lab 4", res);

//	std::ofstream output("output.csv");
//
//	for (auto angle = 0; angle < 360; angle++)
//	{
//		img_rotated = rotate(img, angle);
//
//		orb.detect(img_rotated, keyPoints_rotated);
//		orb.compute(img_rotated, keyPoints_rotated, descriptors_rotated);
//		matcher.knnMatch(descriptors, descriptors_rotated, matches, 2);
//
//		goodMatches.clear();
//
//		for (auto i : matches)
//		{
//			if (i[0].distance < i[1].distance * 0.75)
//			{
//				goodMatches.push_back(i[0]);
//			}
//		}
//
//		output << angle << ";" << goodMatches.size() << std::endl;
//	}
//
//	output.flush();

	cv::waitKey();

	return 0;
}

