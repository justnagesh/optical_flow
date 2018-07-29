cmake_minimum_required(VERSION 2.6)
project(opt_flow)

find_package( OpenCV REQUIRED )
add_executable( opt_flow main.cpp )
target_link_libraries( opt_flow ${OpenCV_LIBS} )


install(TARGETS opt_flow RUNTIME DESTINATION bin)
