#ifndef Vision_h
#define Vision_h

#include <iostream>
#include <opencv/cv.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#define DICTIONARY_ID 16

class Vision {
 public:
  Vision();
  ~Vision();
  bool start();
  bool getVisualPosition(int& x, int& y);
  void showPoints(int x[], int y[], int size, cv::Scalar color, bool save);
  void showPoint(int x, int y, cv::Scalar color, cv::Mat image);
  void getFrameSize(int& width, int& height) const;
  cv::VideoCapture inputVideo;

 private:
  cv::Ptr<cv::aruco::DetectorParameters> detectorParams;
  cv::Ptr<cv::aruco::Dictionary> dictionary;
  std::vector<int> ids;
  std::vector<std::vector<cv::Point2f>> corners, rejected;
  cv::Mat image, imageCopy;
};

Vision::Vision() {
  detectorParams = cv::aruco::DetectorParameters::create();
  dictionary = cv::aruco::getPredefinedDictionary(
      cv::aruco::PREDEFINED_DICTIONARY_NAME(DICTIONARY_ID));
  cv::namedWindow("Windown", cv::WINDOW_AUTOSIZE);
}
Vision::~Vision() {}

bool Vision::start() {
  inputVideo.open(1);
  if (inputVideo.isOpened()) {
    return true;
  } else {
    return false;
    std::cout << "Erro start camera" << std::endl;
  }
}

bool Vision::getVisualPosition(int& _x, int& _y) {
  // Discart 5 frames to get the newest frame
  for (int i = 0; i < 5; i++) {
    inputVideo.grab();
    inputVideo.retrieve(image);
  }
  _x = 0;
  _y = 0;

  // detect markers and estimate pose
  cv::aruco::detectMarkers(image, dictionary, corners, ids, detectorParams,
                           rejected);

  // draw results
  int sizeIds = ids.size();
  if (sizeIds <= 0) {
    std::cout << "Found nothing, Jon Snow" << std::endl;
    return false;
  } else
    for (int i = 0; i < sizeIds; i++) {
      // std::cout << "Ids: " << ids[i] << std::endl;
      // Ids: 213
      if (ids[i] == 530 || ids[i] == 213) {
        _x = (int)((corners[i][0].x + corners[i][1].x + corners[i][2].x +
                    corners[i][3].x) /
                   4);
        _y = (int)((corners[i][0].y + corners[i][1].y + corners[i][2].y +
                    corners[i][3].y) /
                   4);

        std::cout << ids[i] << " >> X: " << (int)_x << " Y: " << (int)_y
                  << std::endl;
        // image.copyTo(imageCopy);
        // cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
        // imshow("out", imageCopy);
        showPoint(_x, _y, cv::Scalar(0, 0, 255), image);
        return true;
      }
    }
  return false;
}
void Vision::showPoints(int x[], int y[], int size, cv::Scalar color,
                        bool save = false) {
  for (int i = 0; i < 5; i++) {
    inputVideo.grab();
    inputVideo.retrieve(image);
  }
  for (int i = 0; i < size; i++) {
    cv::circle(image, cv::Point(x[i], y[i]), 2, color, -1);
  }
  cv::imshow("Windown", image);
  if (save) {
    cv::String diretorioImag = cv::String("coleta1.jpg");
    std::cout << "Salvando...\n" << cv::imwrite(diretorioImag, image);
  }
  cv::waitKey(0);
}

void Vision::showPoint(int x, int y, cv::Scalar color, cv::Mat image) {
  cv::circle(image, cv::Point(x, y), 2, color, -1);
  cv::imshow("Windown", image);
  cv::waitKey(1);
}

void Vision::getFrameSize(int& width, int& height) const {
  width = inputVideo.get(cv::CAP_PROP_FRAME_WIDTH);
  height = inputVideo.get(cv::CAP_PROP_FRAME_HEIGHT);
  // std::cerr << "widht: " << width << "height: " << height;
}

#endif