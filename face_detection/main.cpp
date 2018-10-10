#include <iostream>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

/**************************FUNCTION PROTOTYPE**********************************/
void detectAndDisplay(cv::Mat frame);


/*************GLOBAL VARIABLES (AT LEAST FOR NOW....)************************/
cv::String face_cascade_name = "haarcascade_frontalface_alt.xml";
cv::String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses-xml";
cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;

std::string window_name = "Capture - Face detection";
cv::RNG rng(12345);
//--------------------------------------------------------------------------------

int main()
{

	

	return 0;
}

/****************DETECT AND DISPLAY IMPLEMENTATION*******************************/
void detectAndDisplay(cv::Mat frame)
{
	std::vector<cv::Rect> faces;
	cv::Mat frame_gray;

	cv::cvtColor(frame, frame_gray, CV_BGR2GRAY);
	cv::equalizeHist( frame_gray, frame_gray);

	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2,
		              0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++)
	{
		cv::Point center(faces[i].x + faces[i].width*0.5,
			             faces[i].y + faces[i].height*0.5 );

		cv::ellipse( frame, center, cv::Size(faces[i].width*0.5,
			        faces[i].height*0.5), 0, 0, 360,
			         cv::Scalar(255, 0, 255 ), 4, 8, 0);

		cv::Mat faceROI = frame_gray(faces[i]);
		std::vector<cv::Rect> eyes;

		//-- In each face, detect eyes
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2,
			0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			cv::Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5,
				             faces[i].y + eyes[j].y + eyes[j].height*0.5 );
			int radius = cvRound((eyes[j].width + eyes[j].height*0.25));
			cv::circle(frame, center, radius, cv::Scalar(255,0,0), 4, 8. 0);
		}
		
	}
	//--show the detection
	cv::imshow(window_name, frame);


}

