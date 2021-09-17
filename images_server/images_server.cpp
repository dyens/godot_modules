#include "images_server.h"

#include <iostream>

#include "web_camera.h"

ImagesServer *ImagesServer::singleton = NULL;

ImagesServer *ImagesServer::get_singleton() { return singleton; }

ImagesServer::ImagesServer() { singleton = this; }

void ImagesServer::thread_func(void *p_udata) {
  std::cout << "thread started" << std::endl;
  uint64_t msdelay = 1000;

  ImagesServer *self = (ImagesServer *)p_udata;
  std::cout << "self ok" << self << std::endl;
  WebCamera* wc = WebCamera::get_singleton();
  std::cout << "camera ok" << wc << std::endl;

  while (!self->exit_thread) {
    if (!self->is_started) {
       OS::get_singleton()->delay_usec(msdelay * 1000);
       continue;
    }
    std::cout << "thread tick" << std::endl;
    cv::Mat *img = wc->get_image();
    std::cout << "captured" << std::endl;
    self->save_buf(img);

    self->emit_signal("images_server_signal", true);
    // OS::get_singleton()->delay_usec(msdelay * 1000);
    std::cout << "MSG emit" << std::endl;
  }
}

void ImagesServer::save_buf(cv::Mat *buf) {
  cv::Size s = buf->size();
  int rows = s.height;
  int cols = s.width;

  data.resize(rows * cols * 3);
  PoolVector<uint8_t>::Write wr = data.write();
  std::cout << "Save buffer: rows, cols" << rows << cols << std::endl;
  copymem(wr.ptr(), buf->data, 3 * sizeof(uint8_t) * rows * cols);
}

PoolVector<uint8_t> ImagesServer::get_data() {
  std::cout << "get data. Size: " << data.size() << std::endl;
  return data;
};

Error ImagesServer::init() {
  std::cout << "init images server" << std::endl;
  if (!thread) {
    thread = memnew(Thread);
    thread->start(ImagesServer::thread_func, this);
  }
  return OK;
};

void ImagesServer::start() {
  is_started = true;
};

void ImagesServer::finish() {
  std::cout << "finish images server" << std::endl;
  if (!thread) {
    return;
  }

  exit_thread = true;
  thread->wait_to_finish();

  memdelete(thread);
  thread = NULL;
}

void ImagesServer::_bind_methods() {
  ClassDB::bind_method(D_METHOD("start"), &ImagesServer::start);
  //        ADD_SIGNAL(MethodInfo("images_server_signal",
  //        PropertyInfo(Variant::STRING, "msg")));
  ADD_SIGNAL(
      MethodInfo("images_server_signal", PropertyInfo(Variant::BOOL, "msg")));
  ClassDB::bind_method(D_METHOD("get_data"), &ImagesServer::get_data);
}
