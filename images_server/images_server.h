#ifndef IMAGES_SERVER_H
#define IMAGES_SERVER_H


#include "core/object.h"
#include "core/os/thread_safe.h"
#include "core/reference.h"
#include "core/rid.h"
#include "core/variant.h"
#include "core/os/os.h"

#include "core/os/thread.h"


class ImagesServer : public Object {
	GDCLASS(ImagesServer, Object);
	_THREAD_SAFE_CLASS_

        static ImagesServer *singleton;
        static void thread_func(void *p_udata);

private:
        mutable bool exit_thread = false;
        Thread *thread;
	void get_picture();

protected:
        static void _bind_methods();
public:
	ImagesServer();
        static ImagesServer *get_singleton();
	void test();
	Error init();
        void finish();
};


#endif /* IMAGES_SERVER_H */
