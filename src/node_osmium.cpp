// v8
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wctor-dtor-privacy"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <v8.h>
#pragma GCC diagnostic pop

// node
#include <node.h>

// osmium
#include <osmium/geom/wkb.hpp>
#include <osmium/geom/wkt.hpp>
#include <osmium/io/input_iterator.hpp>
#include <osmium/memory/buffer.hpp>
#include <osmium/visitor.hpp>

// node-osmium
#include "apply.hpp"
#include "file_wrap.hpp"
#include "handler.hpp"
#include "location_handler_wrap.hpp"
#include "osm_changeset_wrap.hpp"
#include "osm_node_wrap.hpp"
#include "osm_relation_wrap.hpp"
#include "osm_way_wrap.hpp"
#include "reader_wrap.hpp"

namespace node_osmium {

    v8::Persistent<v8::Object> module;
    osmium::geom::WKBFactory<> wkb_factory;
    osmium::geom::WKTFactory<> wkt_factory;

    OSMNodeWrap      node_wrap {nullptr};
    OSMWayWrap       way_wrap {nullptr};
    OSMRelationWrap  relation_wrap {nullptr};
    OSMChangesetWrap changeset_wrap {nullptr};

    v8::Persistent<v8::Object> node_object;
    v8::Persistent<v8::Object> way_object;
    v8::Persistent<v8::Object> relation_object;
    v8::Persistent<v8::Object> changeset_object;

    extern "C" {
        static void start(v8::Handle<v8::Object> target) {
            v8::HandleScope scope;
            module = v8::Persistent<v8::Object>::New(target);

            node::SetMethod(target, "apply", node_osmium::apply);

            node_osmium::OSMEntityWrap::Initialize(target);
            node_osmium::OSMObjectWrap::Initialize(target);
            node_osmium::OSMNodeWrap::Initialize(target);
            node_osmium::OSMWayWrap::Initialize(target);
            node_osmium::OSMRelationWrap::Initialize(target);
            node_osmium::OSMChangesetWrap::Initialize(target);
            node_osmium::LocationHandlerWrap::Initialize(target);
            node_osmium::JSHandler::Initialize(target);
            node_osmium::FileWrap::Initialize(target);
            node_osmium::ReaderWrap::Initialize(target);

            v8::Handle<v8::Value> extn = v8::External::New(&node_wrap);
            node_object = v8::Persistent<v8::Object>::New(OSMNodeWrap::constructor->GetFunction()->NewInstance(1, &extn));

            v8::Handle<v8::Value> extw = v8::External::New(&way_wrap);
            way_object = v8::Persistent<v8::Object>::New(OSMWayWrap::constructor->GetFunction()->NewInstance(1, &extw));

            v8::Handle<v8::Value> extr = v8::External::New(&relation_wrap);
            relation_object = v8::Persistent<v8::Object>::New(OSMRelationWrap::constructor->GetFunction()->NewInstance(1, &extr));

            v8::Handle<v8::Value> extc = v8::External::New(&changeset_wrap);
            changeset_object = v8::Persistent<v8::Object>::New(OSMChangesetWrap::constructor->GetFunction()->NewInstance(1, &extc));
        }
    }

} // namespace node_osmium

NODE_MODULE(osmium, node_osmium::start)

