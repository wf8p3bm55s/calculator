set(CMAKE_AUTOUIC ON)	
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick Qml REQUIRED)
find_package(Qt5QuickCompiler)
qtquick_compiler_add_resources(RESOURCES "../qml.qrc")

add_executable(${PROJECT_NAME}
    main.cpp
    calclibwrapper.cpp
    resultsaver.cpp
    "../include/calclibwrapper.h"
    "../include/resultsaver.h"
    ${RESOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC "../include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Quick Qt5::Core Qt5::Qml Calclib)
