function(findTarget target)
    if (TARGET ${target})
        MESSAGE(STATUS "boost.cmake <Target>: ${target}")
        target_link_libraries(${target} PRIVATE ${boost_LIBRARIES})
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE ${boost_INCLUDE_DIRS})
        MESSAGE(FATAL_ERROR "boost.cmake <Target>: ${target} not found")
    endif()
endfunction()

if (NOT BOOST_ROOT)
    set(BOOST_ROOT "E:/ProgramFiles/cppPackage/boost_1_85_0")

endif()

MESSAGE(STATUS "boost.cmake <BOOST_ROOT>: '${BOOST_ROOT}'")

find_package(Boost 1.85.0 REQUIRED)

if (NOT Boost_FOUND)
    MESSAGE(FATAL_ERROR "boost.cmake <Boost_FOUND> not found")
endif ()

set(Boost_DEBUG ON)
set(Boost_DETAILED_FAILURE_MSG ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_ARCHITECTURE "-x64")
set(Boost_COMPILER "-mgw13")

MESSAGE(STATUS "boost.cmake <options>: \n
\tBoost_DEBUG: '${Boost_DEBUG}'\n
\tBoost_DETAILED_FAILURE_MSG: '${Boost_DETAILED_FAILURE_MSG}'\n
\tBoost_USE_STATIC_LIBS: '${Boost_USE_STATIC_LIBS}'\n
\tBoost_ARCHITECTURE: '${Boost_ARCHITECTURE}'\n
\tBoost_COMPILER: '${Boost_COMPILER}'")

if (Boost_INCLUDE_DIRS)
    MESSAGE(STATUS "boost.cmake <Boost_INCLUDE_DIRS>: '${Boost_INCLUDE_DIRS}'")
    include_directories(${Boost_INCLUDE_DIRS})
    MESSAGE(STATUS "boost.cmake <NOTE>: The library '${Boost_INCLUDE_DIRS}' has been automatically included for you")
else ()
    MESSAGE(FATAL_ERROR "boost.cmake <Boost_INCLUDE_DIRS> not found")
endif ()

if (Boost_LIBRARIES)
    MESSAGE(STATUS "boost.cmake <Boost_LIBRARIES>: '${Boost_LIBRARIES}'")
endif ()

if (NOT BOOST_LIBRARYDIR)
    set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib)
endif ()

MESSAGE(STATUS "boost.cmake <BOOST_LIBRARYDIR>: '${BOOST_LIBRARYDIR}'")

MESSAGE(STATUS "boost.cmake <NOTE>: You need to 'find_mackage' the package you need again, like 'find_package(Boost REQUIRED COMPONENTS filesystem)'")

if (TARGET ${TARGET})
    findTarget(${TARGET})
endif ()
