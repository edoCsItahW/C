// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file build.cpp
 * @author edocsitahw
 * @version 1.1
 * @date 2024/10/20 上午8:23
 * @brief 将数据结构类型暴露给Python接口
 * @copyright CC BY-NC-SA
 * */

#include "pybind11/pybind11.h"
#include "st/dfImpl.h"


namespace py = pybind11;

PYBIND11_MODULE(dfImpl, m) {
    m.doc() = "Python bindings for dfImpl library";

    py::class_<S_OrderQueue>(m, "OrderQueue")
        .def(py::init<>())
        .def_property("base", [](S_OrderQueue& self) { return self.base;}, [](S_OrderQueue& self, void** value) { self.base = value; })
        .def_property("font", &S_OrderQueue::font, &S_OrderQueue::font)
        .def_property("rear", &S_OrderQueue::rear, &S_OrderQueue::rear)
        .def("__len__", [](S_OrderQueue* self) { return sizeOQ(self); })
        .def("enqueue", [](S_OrderQueue* self, void* value) { enqueueOQ(self, value); }, "Enqueue an order to the OrderQueue")
        .def("dequeue", [](S_OrderQueue* self) { dequeueOQ(self); }, "Dequeue an order from the OrderQueue")
        .def("getFront", [](S_OrderQueue* self) { return getFrontOQ(self); }, "Get the font of the OrderQueue");

    m.def("initOrderQueue", &initOrderQueue, "Initialize the OrderQueue");

    py::class_<S_LinkQueue>(m, "LinkQueue")
        .def(py::init<>())
        .def_property("base", [](S_OrderQueue& self) { return self.base;}, [](S_OrderQueue& self, void** value) { self.base = value; })
        .def_property("font", &S_OrderQueue::font, &S_OrderQueue::font)
        .def_property("rear", &S_OrderQueue::rear, &S_OrderQueue::rear)
        .def("__len__", [](S_OrderQueue* self) { return sizeOQ(self); })
        .def("enqueue", [](S_OrderQueue* self, void* value) { enqueueOQ(self, value); }, "Enqueue an order to the OrderQueue")
        .def("dequeue", [](S_OrderQueue* self) { dequeueOQ(self); }, "Dequeue an order from the OrderQueue")
        .def("getFront", [](S_OrderQueue* self) { return getFrontOQ(self); }, "Get the font of the OrderQueue");

    m.def("initOrderQueue", &initOrderQueue, "Initialize the OrderQueue");
}
