#include <opencv2/features2d/features2d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

int main(int argc, char* argv[])
{
	auto img1 = cv::imread("img1.jpg");
	auto img2 = cv::imread("img2.jpg");

	auto img1_original = img1;

	cv::Mat img2_1;

	resize(img2, img2_1, cv::Size(img1.cols, img1.rows));

	img2 = img2_1;

	cv::Mat gray1;
	cv::Mat gray2;

	cvtColor(img1, gray1, cv::COLOR_RGB2GRAY);
	cvtColor(img2, gray2, cv::COLOR_RGB2GRAY);

	cv::FastFeatureDetector ffd;

	std::vector<cv::KeyPoint> kpl;

	ffd.detect(gray1, kpl);

	std::vector<cv::Point2f> ptl;

	for (auto i : kpl)
	{
		ptl.push_back(i.pt);
	}
	
	std::vector<cv::Point2f> ptr;
	std::vector<uchar> vstatus;
	std::vector<float> verror;

	calcOpticalFlowPyrLK(gray1, gray2, ptl, ptr, vstatus, verror);

	auto lineColor = CV_RGB(255, 0, 0);

	for (auto i = 0; i < ptl.size(); i++)
	{
		arrowedLine(img1_original, ptl[i], ptr[i], lineColor);
	}

	imshow("Lab 6", img1_original);

	cv::waitKey();
	
	return 0;
}

