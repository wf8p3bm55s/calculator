add_library(${PROJECT_NAME} SHARED calclib.c)
add_library("${PROJECT_NAME}Static" STATIC calclib.c)

target_include_directories(${PROJECT_NAME} PUBLIC "../include")
target_include_directories("${PROJECT_NAME}Static" PUBLIC "../include")