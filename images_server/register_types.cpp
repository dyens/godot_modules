/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "core/engine.h"
#include "images_server.h"

static ImagesServer* images_server = NULL;

void register_images_server_types() {
        images_server = memnew(ImagesServer);
        images_server->init();
        ClassDB::register_class<ImagesServer>();
        Engine::get_singleton()->add_singleton(Engine::Singleton("ImagesServer", ImagesServer::get_singleton()));
}

void unregister_images_server_types() {
        if (images_server) {
                images_server->finish();
                memdelete(images_server);
        }

}
