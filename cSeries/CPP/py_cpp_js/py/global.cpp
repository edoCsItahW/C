// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/*****************************************************
 * @File name: py_cpp_js
 * @Author: edocsitahw
 * @Version: 1.1
 * @Date: 2024/08/18 下午2:52
 * @Commend:
 *******************************************************/

#include "global.h"

namespace Glb {
    py::scoped_interpreter guard{};
    py::module builtins = py::module::import("builtins");
    py::function dir    = builtins.attr("dir");
    std::map<std::string, node::Function> dynaCacher{};
}  // namespace Global

namespace Err {
    void NotImplementedError(node::Env env, const std::string &msg) { node::Error::New(env, "NotImplementedError: " + msg).ThrowAsJavaScriptException(); }

    void ArgumentError(node::Env env, const std::string &msg) { node::Error::New(env, msg).ThrowAsJavaScriptException(); }

    Try::Try(node::Env env)
        : _env(env) {}

    Try::Try()  = default;
    Try::~Try() = default;

    Try &Try::getInstance(node::Env env) {
        static Try instance(env);
        return instance;
    }

    Try &Try::getInstance() {
        static Try instance;
        return instance;
    }

    template<typename R, typename... Args>
    std::function<R(Args...)> Try::operator()(R (*f)(Args...), node::Env env, std::source_location loc) {
        return [f, loc, env](Args... args) -> R {
            try {
                return f(args...);
            } catch (const std::exception &e) {
                std::ostringstream oss;

                oss << "\tFile: " << loc.file_name() << " line " << loc.line() << " in " << loc.function_name() << "\n" << e.what();
                node::Error::New(env, oss.str()).ThrowAsJavaScriptException();
            }
            return R();
        };
    }

    template<typename R, typename... Args>
    std::function<R(Args...)> Try::operator()(R (*f)(Args...), std::source_location loc) {
        std::ostringstream oss;

        oss << "Try::operator() env is null\n\tFile: " << loc.file_name() << " line " << loc.line() << " in " << loc.function_name();

        if (_env == nullptr) throw std::runtime_error(oss.str());

        return operator()(f, _env, loc);
    }

    Try &try_ = Try::getInstance();
}  // namespace Error

namespace Py {
    namespace Tools {
        std::string getPyType(const py::object &value) { return py::type::of(value).attr("__name__").cast<std::string>(); }

        py::list getAttr(const py::object &obj) { return Glb::dir(obj); }

        py::tuple getArgs(const node::CallbackInfo &info) {
            py::tuple args(info.Length());

            for (int i = 0; i < info.Length(); i++) args[i] = Js::Converter::jsToPy(info[i]);

            return args;
        }
    }  // namespace Tools

    namespace Converter {
        node::String str(node::Env env, const py::object &value) { return node::String::From(env, value.cast<std::string>()); }

        node::Number integer(node::Env env, const py::object &value) { return node::Number::New(env, value.cast<int64_t>()); }

        node::Number float_(node::Env env, const py::object &value) { return node::Number::New(env, value.cast<double>()); }

        node::Boolean boolean(node::Env env, const py::object &value) { return node::Boolean::New(env, value.cast<bool>()); }

        node::Array list(node::Env env, const py::object &value) {
            auto list = value.cast<py::list>();
            auto arr  = node::Array::New(env, list.size());

            for (int i = 0; i < list.size(); i++) arr[i] = Err::try_(pyToJs, env)(env, list[i]);

            return arr;
        }

        node::Object dict(node::Env env, const py::object &value) {
            auto dict = value.cast<py::dict>();
            auto obj  = node::Object::New(env);

            for (auto it : dict) obj.Set(it.first.cast<std::string>(), Err::try_(pyToJs, env)(env, it.second.cast<py::object>()));

            return obj;
        }

        node::Function function(node::Env env, const py::object &value) {
            return node::Function::New(
                env,
                [value, env](const node::CallbackInfo &info) -> node::Value {
                    auto args = Tools::getArgs(info);

                    auto func = value.cast<py::function>();

                    auto result = func(*args);
                    return Err::try_(pyToJs, env)(env, result);
                },
                py::hasattr(value, "__name__") ? value.attr("__name__").cast<std::string>().c_str() : "lambda"
            );
        }

        node::Object module(node::Env env, const py::object &value) {
            auto attrs = Err::try_(Tools::getAttr, env)(value);
            auto obj   = node::Object::New(env);
            for (auto it : attrs) {
                auto k = it.cast<std::string>();
                if (py::hasattr(value, k.c_str())) {
                    auto v = py::getattr(value, k.c_str());
                    obj.Set(k, Err::try_(pyToJs, env)(env, v));
                }
            }
            return obj;
        }

        node::Function class_(node::Env env, const py::object &value, const std::string &type) {
            std::cout << value.attr("__name__").cast<std::string>() << std::endl;
            if (auto res = Glb::dynaCacher.find(value.attr("__name__").cast<std::string>()); res != Glb::dynaCacher.end()) {
                std::cout << value.attr("__name__").cast<std::string>() << " is cached" << std::endl;
                return res->second;
            }
            auto constructor = node::Function::New(
                env,
                [value, env](const node::CallbackInfo &info) -> node::Value {
                    auto pyIns     = value(*Tools::getArgs(info));
                    auto jsIns     = node::Object::New(env);
                    py::list attrs = Err::try_(Tools::getAttr, env)(pyIns);
                    for (auto it : attrs) {
                        auto k = it.cast<std::string>();
                        if (py::hasattr(pyIns, k.c_str())) {
                            auto v = py::getattr(pyIns, k.c_str());
                            jsIns.Set(k, Err::try_(pyToJs, env)(env, v));
                        }
                    }
                    return jsIns;
                },
                py::hasattr(value, "__name__") ? value.attr("__name__").cast<std::string>().c_str() : type.c_str()
            );
            auto attrs = Err::try_(Tools::getAttr, env)(value);
            for (auto it : attrs) {
                auto k = it.cast<std::string>();
                if (py::hasattr(value, k.c_str())) {
                    auto v = py::getattr(value, k.c_str());
                    constructor.Set(k, Err::try_(pyToJs, env)(env, v));
                }
            }

            Glb::dynaCacher[value.attr("__name__").cast<std::string>()] = constructor;
            return constructor;
        }

        node::Value none(node::Env env) { return env.Null(); }

        node::Value pyToJs(node::Env env, const py::object &value) {
            auto type     = Err::try_(Tools::getPyType, env)(value);
            auto funcType = std::vector<std::string>{"function", "method-wrapper", "builtin_function_or_method", "staticmethod", "classmethod", "getset_descriptor"};

            if (py::isinstance<py::str>(value))
                return Err::try_(str, env)(env, value);
            else if (py::isinstance<py::int_>(value))
                return Err::try_(integer, env)(env, value);
            else if (py::isinstance<py::float_>(value))
                return Err::try_(float_, env)(env, value);
            else if (py::isinstance<py::bool_>(value))
                return Err::try_(boolean, env)(env, value);
            else if (py::isinstance<py::list>(value))
                return Err::try_(list, env)(env, value);
            else if (py::isinstance<py::dict>(value))
                return Err::try_(dict, env)(env, value);
            else if (std::ranges::contains(funcType, type))
                return Err::try_(function, env)(env, value);
            else if (type == "module")
                return Err::try_(module, env)(env, value);
            else if (type == "NoneType" || value.is_none())
                return none(env);
            else
                return Err::try_(class_, env)(env, value, type);
        }
    }  // namespace Converter
}  // namespace Py

namespace Js::Converter {
    py::str string(const node::Value &value) { return py::cast(value.ToString().Utf8Value()); }

    py::int_ integer(const node::Value &value) { return py::cast(value.ToNumber().Int32Value()); }

    py::float_ number(const node::Value &value) { return py::cast(value.ToNumber().DoubleValue()); }

    py::bool_ boolean(const node::Value &value) { return py::cast(value.ToBoolean()); }

    py::list array(const node::Value &value) {
        auto arr = value.As<node::Array>();
        py::list list;
        for (int i = 0; i < arr.Length(); i++) list.append(Err::try_(jsToPy, arr.Env())(arr[i]));
        return list;
    }

    py::dict object(const node::Value &value) {
        auto obj  = value.As<node::Object>();
        auto iter = obj.GetPropertyNames();
        py::dict dict;
        for (auto it = iter.begin(); it != iter.end(); ++it) dict[it.operator*().first.ToString().Utf8Value().c_str()] = Err::try_(jsToPy, obj.Env())(obj.Get(it.operator*().first));
        return dict;
    }

    py::function function(const node::Value &value) {
        // TODO: 实现js函数转为py函数
        // return py::cast([value](const py::args& args) -> py::object {})
        Err::NotImplementedError(value.Env(), "Function is not supported yet.");
    }

    py::none null(const node::Value &value) { return {}; }

    py::object jsToPy(const node::Value &value) {
        if (value.IsString())
            return Err::try_(string, value.Env())(value);
        else if (value.IsNumber())
            return Err::try_(number, value.Env())(value);
        else if (value.IsBoolean())
            return Err::try_(boolean, value.Env())(value);
        else if (value.IsArray())
            return Err::try_(array, value.Env())(value);
        else if (value.IsObject())
            return Err::try_(object, value.Env())(value);
        else if (value.IsFunction())
            return Err::try_(function, value.Env())(value);
        else if (value.IsUndefined() || value.IsNull())
            return null(value);
        else
            Err::NotImplementedError(value.Env(), "Unsupported type" + value.As<node::Object>().Get("constructor").As<node::Object>().Get("name").ToString().Utf8Value());
        return py::none();
    }
}  // namespace Js::Converter

namespace Api {
    node::Value import_(const node::CallbackInfo &info) {
        if (info.Length() != 1) Err::ArgumentError(info.Env(), "import() takes exactly one argument");
        auto module = py::module::import(info[0].As<node::String>().Utf8Value().c_str());
        return Err::try_(Py::Converter::pyToJs, info.Env())(info.Env(), module);
    }

    void atexit(const node::CallbackInfo &info) {
        if (info.Length() != 0) Err::ArgumentError(info.Env(), "atexit() takes no arguments");
        if (std::atexit([]() { std::cout << "exit" << std::endl; })) return;
    }
}  // namespace Api
