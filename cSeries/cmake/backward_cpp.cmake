if (NOT DEFINED BACKWARD_CPP_DIR)
    set(BACKWARD_CPP_DIR "E:/ProgramFiles/cppPackage/backward_cpp")
endif ()

find_package(Backward REQUIRED PATHS ${BACKWARD_CPP_DIR})

include_directories(BACKWARD_CPP_DIR)
MESSAGE(STATUS "backward_cpp.cmake <BACKWARD_CPP_DIR>: ${BACKWARD_CPP_DIR}")

if (WIN32)
    find_library(DBGHELP_LIBRARY dbghelp)
endif ()

MESSAGE(STATUS "backward_cpp.cmake <DBGHELP_LIBRARY>: ${DBGHELP_LIBRARY}")
MESSAGE(STATUS "backward_cpp.cmake <NOTE>: Please link dbghelp library if you are using Windows platform.")
