#ifndef IMAGES_SERVER_H
#define IMAGES_SERVER_H

#include <opencv2/opencv.hpp>
#include <vector>

#include "core/object.h"
#include "core/os/os.h"
#include "core/os/thread.h"
#include "core/os/thread_safe.h"
#include "core/reference.h"
#include "core/rid.h"
#include "core/variant.h"
#include "scene/resources/texture.h"


class ImagesServer : public Object {
  GDCLASS(ImagesServer, Object);
  _THREAD_SAFE_CLASS_

  static ImagesServer *singleton;
  static void thread_func(void *p_udata);

 private:
  mutable bool exit_thread = false;
  mutable bool is_started = false;
  Thread *thread = NULL;

  PoolVector<uint8_t> data;

  void save_buf(cv::Mat *buf);

 protected:
  static void _bind_methods();

 public:
  ImagesServer();
  static ImagesServer *get_singleton();
  PoolVector<uint8_t> get_data();
  Error init();
  void start();
  void finish();
};



#endif /* IMAGES_SERVER_H */
