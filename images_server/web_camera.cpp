#include "web_camera.h"

#include <iostream>

WebCamera *WebCamera::singleton = NULL;

WebCamera *WebCamera::get_singleton() { return singleton; }

WebCamera::WebCamera() { singleton = this; }

cv::Mat *WebCamera::get_image() {
  if (is_initialized == false) {
    cap.open(0);
    if (!cap.isOpened()) {
        cap.release();
        throw std::runtime_error("Unable to open camera");
    }
    is_initialized = true;
  }

  cv::Mat buffer;
  cap >> buffer;
  // Opencv get images in BGR
  cv::cvtColor(buffer,frame, cv::COLOR_BGR2RGB);

  return &frame;
}

void WebCamera::close() { cap.release(); }

void WebCamera::_bind_methods() {}
