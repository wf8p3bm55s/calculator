cmake_minimum_required(VERSION 3.16)

project(Calclib VERSION 1.0 LANGUAGES C)

add_subdirectory(src)

set_target_properties(${PROJECT_NAME} PROPERTIES 
	C_STANDARD 99
	C_STANDARD_REQUIRED True
)