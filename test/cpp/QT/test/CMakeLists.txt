# 压缩并删除了E:/ProgramFiles/Anaconda/Library/lib/cmake/Qt5Widgets,E:/ProgramFiles/Anaconda/Library/include/qt/
# "E:/ProgramFiles/cppPackage/QT/6.7.2/msvc2019_64/lib/Qt6EntryPointd.lib"
# "E:/ProgramFiles/cppPackage/QT/6.7.2/wasm_singlethread/lib/cmake/Qt6/Qt6Config.cmake"
# "E:/ProgramFiles/cppPackage/QT/6.7.2/wasm_multithread/lib/cmake/Qt6/Qt6Config.cmake"
# "E:/ProgramFiles/cppPackage/QT/Tools/QtDesignStudio/qt6_design_studio_reduced_version/lib/cmake/Qt6/Qt6Config.cmake"
# "E:/ProgramFiles/cppPackage/QT/6.7.2/msvc2019_arm64/lib/cmake/Qt6/Qt6Config.cmake"
# "E:/ProgramFiles/cppPackage/QT/6.7.2/mingw_64/lib/cmake/Qt6/Qt6Config.cmake"
cmake_minimum_required(VERSION 3.5)

project(test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "E:/ProgramFiles/cppPackage/QT/6.7.2/mingw_64" CACHE PATH "Qt install prefix" FORCE)
set(Qt6_DIR "E:/ProgramFiles/cppPackage/QT/6.7.2/mingw_64/lib/cmake/Qt6")

#add_executable(test main.cpp)

include_directories("E:/ProgramFiles/cppPackage/QT/6.7.2/mingw_64/include")
#target_link_libraries(test "E:/ProgramFiles/cppPackage/QT/6.7.2/msvc2019_64/lib")

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES test_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        testUI.cpp
        testUI.h
        testUI.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(test
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET test APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(test SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(test
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(test PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.test)
endif()
set_target_properties(test PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS test
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(test)
endif()

