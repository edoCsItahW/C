// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

/**
 * @file global.h
 * @author edocsitahw
 * @version 1.1
 * @date 2024/08/18 下午2:52
 * @brief 实现通过cpp桥接python与js交互
 * @copyright CC BY-NC-SA
 * */

#ifndef PY_CPP_JS_GLOBAL_H
#define PY_CPP_JS_GLOBAL_H
#pragma once

#include <napi.h>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <vector>
#include <iostream>
#include <map>
#include <functional>
#include <source_location>
#include <sstream>
#include <ranges>
// #include <optional>
#include <cstdlib>
// #include <stack>
// #include <algorithm>
// #include <typeindex>
// #include <variant>

/**
 * @namespace py
 * @typedef pybind11
 * @brief 重命名pybind11为py
 * */
namespace py = pybind11;
/**
 * @namespace node
 * @typedef Napi
 * @brief 重命名Napi为node
 * */
namespace node = Napi;

/**
 * @namespace Glb
 * @brief 全局变量
 * @details 该命名空间用于存储全局变量。
 * */
namespace Glb {
	/**
	 * @var guard
	 * @brief 全局解释器
	 * @qualifier extern
	 * */
	extern py::scoped_interpreter guard;

	/**
	 * @var builtins
	 * @brief 全局python内建模块
	 * @qualifier extern
	 * */
	extern py::module builtins;

    /**
     * @var dir
     * @brief 全局python内建函数dir
     * @qualifier extern
     * */
	extern py::function dir;

    /**
     * @var dynaCacher
     * @brief 动态缓存器
     * @qualifier extern
     * */
    extern std::map<std::string, node::Function> dynaCacher;
}

/**
 * @namespace Err
 * @brief 错误处理
 * @details 该命名空间用于处理错误。
 * */
namespace Err {
    /**
     * @brief 未实现错误
     * @details 该函数用于处理未实现错误。
     * @param env node环境
     * @param msg 错误信息
     * @exception NotImplementedError 未实现错误
     * */
	void NotImplementedError(node::Env env, const std::string& msg);

    /**
     * @brief 参数错误
     * @details 该函数用于处理参数错误。
     * @param env node环境
     * @param msg 错误信息
     * @exception ArgumentError 参数错误
     * */
	void ArgumentError(node::Env env, const std::string& msg);

	/**
	 * @class Try global.h
	 * @brief 函数异常处理装饰器类
	 * @qualifier decorator
	 * @details 该类用于处理函数异常。
	 * @remark 在C++中实现单例模式,通常需要确保以下几点: \n
	 *	- 构造函数和析构函数是私有的,以防止外部实例化.
	 *	- 拷贝构造函数和赋值运算符是私有的,以防止拷贝和赋值.
	 *	- 提供一个静态方法来获取单例实例.
	 *	- 使用一个静态成员变量来存储唯一的实例.
	 * */
	class Try {
		private:
			node::Env _env = nullptr;  /// @private @memberof Try @var _env 环境变量
			/**
			 * @brief 构造函数
			 * @details 私有构造函数,禁止外部实例化.
			 * @param env node环境
			 * @private @memberof Try
			 * */
			explicit Try(node::Env env);
			explicit Try();
            /**
             * @brief 析构函数
             * @details 私有析构函数,禁止外部实例化.
             * @private @memberof Try
             * */
			~Try();

		public:
            /**
             * @brief 获取单例实例
             * @details 获取单例实例,如果不存在,则创建.
             * @param env node环境
             * @return 单例实例
             * */
			static Try& getInstance(node::Env env);
			static Try& getInstance();
			Try(const Try&) = delete;
			void operator=(const Try&) = delete;
            /**
             * @brief 装饰器函数
             * @details 装饰器函数,用于处理函数异常.
             * @tparam R 返回值类型
             * @tparam Args 参数类型
             * @param f 函数指针
             * @param loc 位置信息
             * @return 函数指针
             * */
			template <typename R, typename... Args>
			std::function<R(Args...)> operator()(R(*f)(Args...), std::source_location loc = std::source_location::current());
			template <typename R, typename... Args>
			std::function<R(Args...)> operator()(R(*f)(Args...), node::Env env, std::source_location loc = std::source_location::current());
	};

	extern Try& try_;
}

namespace Py {
	namespace Tools {
		std::string getPyType(const py::object& value);

		py::list getAttr(const py::object& obj);

		py::tuple getArgs(const node::CallbackInfo& info);
	}
	namespace Converter {
		node::Value pyToJs(node::Env env, const py::object &value);

		node::String str(node::Env env, const py::object& value);
		node::Number integer(node::Env env, const py::object& value);
		node::Number float_(node::Env env, const py::object& value);
		node::Boolean boolean(node::Env env, const py::object& value);
		node::Array list(node::Env env, const py::object& value);
		node::Object dict(node::Env env, const py::object& value);
		node::Function function(node::Env env, const py::object& value);
		node::Function class_(node::Env env, const py::object& value, const std::string& type);
		/**
	     * @brief 该函数用于将py模块转为js模块(实则为js对象)
	     * @param env node环境
	     * @param value py模块
	     * @return js模块
	     * @note 由于该函数使用递归实现,可能会导致栈溢出,对于大型模块,可能需要使用循环或迭代的方式实现.
	     * */
		node::Object module(node::Env env, const py::object& value);
		node::Value none(node::Env env);
	}
}

namespace Js::Converter {
	py::object jsToPy(const node::Value& value);

	py::str string(const node::Value& value);
	py::int_ integer(const node::Value& value);
	py::float_ number(const node::Value& value);
	py::bool_ boolean(const node::Value& value);
	py::list array(const node::Value& value);
	py::dict object(const node::Value& value);
	py::function function(const node::Value& value);
	py::none null(const node::Value& value);
}

namespace Api {
	node::Value import_(const node::CallbackInfo& info);

	void atexit(const node::CallbackInfo& info);
}


#endif // PY_CPP_JS_GLOBAL_H
