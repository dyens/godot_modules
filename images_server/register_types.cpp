/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "core/engine.h"
#include "images_server.h"
#include "web_camera.h"

static ImagesServer* images_server = NULL;
static WebCamera* web_camera = NULL;

void register_images_server_types() {
        images_server = memnew(ImagesServer);
        images_server->init();
        ClassDB::register_class<ImagesServer>();
        Engine::get_singleton()->add_singleton(Engine::Singleton("ImagesServer", ImagesServer::get_singleton()));


        web_camera = memnew(WebCamera);
        ClassDB::register_class<WebCamera>();
        Engine::get_singleton()->add_singleton(Engine::Singleton("WebCamera", WebCamera::get_singleton()));

}

void unregister_images_server_types() {
        if (images_server) {
                images_server->finish();
                memdelete(images_server);
        }
        if (web_camera) {
	  memdelete(web_camera);
	}

}
