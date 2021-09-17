#ifndef WEB_CAMERA_H
#define WEB_CAMERA_H

#include <opencv2/opencv.hpp>

#include "core/object.h"

class WebCamera : public Object {
  GDCLASS(WebCamera, Object);

  static WebCamera *singleton;

 protected:
  static void _bind_methods();

 private:
  cv::VideoCapture cap;
  cv::Mat frame;
  bool is_initialized = false;

 public:
  WebCamera();
  static WebCamera *get_singleton();
  cv::Mat *get_image();
  void close();
};

#endif /* WEB_CAMERA_H */
