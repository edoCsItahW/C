cmake_policy(SET CMP0057 NEW)

cmake_minimum_required(VERSION {} FATAL_ERROR)

project({})

find_package(Python {} COMPONENTS Interpreter Development REQUIRED)

find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module({} {})