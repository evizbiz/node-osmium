#ifndef BASIC_READER_WRAP_HPP
#define BASIC_READER_WRAP_HPP

// v8/node
#include "include_v8.hpp"
#include <node_object_wrap.h>

// osmium
#include <osmium/io/any_input.hpp>
#include <osmium/io/reader.hpp>
#include <osmium/osm/entity_bits.hpp>
#include <osmium/osm/location.hpp>
#include <osmium/osm/types.hpp>

namespace node_osmium {

    class BasicReaderWrap : public node::ObjectWrap {

        static v8::Handle<v8::Value> header(const v8::Arguments& args);
        static v8::Handle<v8::Value> close(const v8::Arguments& args);
        static v8::Handle<v8::Value> read(const v8::Arguments& args);
        static v8::Handle<v8::Value> read_all(const v8::Arguments& args);

        osmium::io::Reader m_this;

    public:

        static v8::Persistent<v8::FunctionTemplate> constructor;
        static void Initialize(v8::Handle<v8::Object> target);
        static v8::Handle<v8::Value> New(const v8::Arguments& args);

        BasicReaderWrap(const osmium::io::File& file, osmium::osm_entity_bits::type entities) :
            ObjectWrap(),
            m_this(file, entities) {
        }

        osmium::io::Reader& get() {
            return m_this;
        }

    private:

        ~BasicReaderWrap() = default;

    }; // class BasicReaderWrap

} // namespace node_osmium

#endif // BASIC_READER_WRAP_HPP
