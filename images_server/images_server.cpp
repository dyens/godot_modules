#include "images_server.h"
#include <iostream>



ImagesServer *ImagesServer::singleton = NULL;

ImagesServer *ImagesServer::get_singleton() {
        return singleton;
}

ImagesServer::ImagesServer() {
        singleton = this;
}



void ImagesServer::thread_func(void *p_udata) {
        std::cout << "thread started" << std::endl;

        ImagesServer *ac = (ImagesServer *) p_udata;
        uint64_t msdelay = 1000;

        std::cout << "exit thread =" << ac->exit_thread << std::endl;
        while (!ac->exit_thread) {
	  ac->get_picture();
          std::cout << "thread tick" << std::endl;

	  // Variant hello_string = Variant("Hello from server");
          // emit_signal("images_server_signal", hello_string);
	  ImagesServer::get_singleton()->emit_signal("images_server_signal", 3);
          OS::get_singleton()->delay_usec(msdelay * 1000);
        }
}

void ImagesServer::get_picture() {
  std::cout << "get_picture" << std::endl;
}



void ImagesServer::test() {
  std::cout << "test" << std::endl;
};


Error ImagesServer::init() {
  std::cout << "init images server" << std::endl;
  thread = memnew(Thread);
  thread->start(ImagesServer::thread_func, this);
  return OK;
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
        ClassDB::bind_method(D_METHOD("test"), &ImagesServer::test);
        ADD_SIGNAL(MethodInfo("images_server_signal", PropertyInfo(Variant::STRING, "msg")));
}
