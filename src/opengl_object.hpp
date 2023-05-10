#pragma once

#include "glad/gl.h"

class SingleId {
    protected:
    unsigned int id;

    public:
    SingleId(void (*generator)(int, unsigned int *)) {
        generator(1, &this->id);
    }
    virtual ~SingleId() { glDeleteBuffers(1, &this->id); }

    constexpr inline unsigned int get_id() { return this->id; }
};

template <int BufferTarget> class Buffer: public SingleId {
    public:
    Buffer() : SingleId(glGenBuffers) {}

    void bind() { glBindBuffer(BufferTarget, this->id); }
    void data();
};

using ElementBuffer = Buffer<GL_ELEMENT_ARRAY_BUFFER>;
using ArrayBuffer = Buffer<GL_ARRAY_BUFFER>;
