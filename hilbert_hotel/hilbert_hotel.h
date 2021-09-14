#ifndef HILBERT_HOTEL_H
#define HILBERT_HOTEL_H

#include "core/list.h"
#include "core/object.h"
#include "core/os/thread.h"
#include "core/os/mutex.h"
#include "core/rid.h"
#include "core/set.h"
#include "core/variant.h"

class InfiniteBus : public RID_Data {
        RID self;

private:
        uint64_t prime_num;
        uint64_t num;

public:
        uint64_t next_room() {
                return prime_num * num++;
        }

        uint64_t get_bus_num() const {
                return prime_num;
        }

        uint64_t get_current_room() const {
                return prime_num * num;
        }

        _FORCE_INLINE_ void set_self(const RID &p_self) {
                self = p_self;
        }

        _FORCE_INLINE_ RID get_self() const {
                return self;
        }

        InfiniteBus(uint64_t prime) : prime_num(prime), num(1) {};
        ~InfiniteBus() {};
};



class HilbertHotel : public Object {
        GDCLASS(HilbertHotel, Object);

        static HilbertHotel *singleton;
        static void thread_func(void *p_udata);

private:
        bool thread_exited;
        mutable bool exit_thread;
        Thread *thread;
        Mutex *mutex;

public:
        static HilbertHotel *get_singleton();
        Error init();
        void lock();
        void unlock();
        void finish();

protected:
        static void _bind_methods();

private:
        uint64_t counter;
        RID_Owner<InfiniteBus> bus_owner;
        // https://github.com/godotengine/godot/blob/3.x/core/rid.h#L196
        Set<RID> buses;
        void _emit_occupy_room(uint64_t room, RID rid);

public:
        RID create_bus();
        Variant get_bus_info(RID id);
        bool empty();
        bool delete_bus(RID id);
        void clear();
        void register_rooms();
        HilbertHotel();
};


class _HilbertHotel : public Object {
        GDCLASS(_HilbertHotel, Object);

        friend class HilbertHotel;
        static _HilbertHotel *singleton;

protected:
        static void _bind_methods();

private:
        void _occupy_room(int room_number, RID bus);

public:
        RID create_bus();
        void connect_signals();
        bool delete_bus(RID id);
        static _HilbertHotel *get_singleton();
        Variant get_bus_info(RID id);

        _HilbertHotel();
        ~_HilbertHotel();
};

#endif
