cmake_minimum_required(VERSION 3.16)

project(ConsoleCalculator LANGUAGES CXX)

add_subdirectory(src)

set_target_properties(${PROJECT_NAME} PROPERTIES 
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED True
)