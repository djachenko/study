#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

int main(int argc, char* argv[])
{
	auto img = cv::imread("img.jpg");

	cv::Size boardSize(8, 6);
	std::vector<cv::Point2f> corners;
	auto result = findChessboardCorners(img, boardSize, corners);
	
//	cv::drawChessboardCorners(img, boardSize, corners, result);

	std::vector<cv::Point3f> objectPoints;

	for (auto y = 0; y < boardSize.height; y++)
	{
		for (auto x = 0; x < boardSize.width; x++)
		{
			objectPoints.push_back(cv::Point3f(x, y, 0));
		}
	}

	std::vector<std::vector<cv::Point3f>> allObjectPoints;
	std::vector<std::vector<cv::Point2f>> allCorners;

	allObjectPoints.push_back(objectPoints);
	allCorners.push_back(corners);

	cv::Mat cameraMatrix;
	cv::Mat distCoeffs;
	std::vector<cv::Mat> rvecs;
	std::vector<cv::Mat> tvecs;

	calibrateCamera(allObjectPoints, allCorners, cv::Size(img.cols, img.rows), cameraMatrix, distCoeffs, rvecs, tvecs);

	if (result)
	{
		cv::Mat rvec;
		cv::Mat tvec;

		solvePnP(objectPoints, corners, cameraMatrix, distCoeffs, rvec, tvec);

		std::vector<cv::Point3f> axis;

		auto len = 3;

		axis.push_back(cv::Point3f(len, 0, 0));
		axis.push_back(cv::Point3f(0, len, 0));
		axis.push_back(cv::Point3f(0, 0, -len));		

		std::vector<cv::Point2f> imagePoints;

		projectPoints(axis, rvec, tvec, cameraMatrix, distCoeffs, imagePoints);

		auto center = corners[0];
		auto lineColor = CV_RGB(255, 0, 0);

		for (auto i : imagePoints)
		{
			arrowedLine(img, center, i, lineColor, 2);
		}
	}

	imshow("Lab 6", img);

	cv::waitKey();

	return 0;
}

