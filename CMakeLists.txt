cmake_minimum_required(VERSION 3.5)

project(main LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)

add_subdirectory(cuda)
set (EXTRA_LIBS ${EXTRA_LIBS} rgb2yuv_gpu)

add_executable(main ${SOURCES})

target_link_libraries(main ${OpenCV_LIBS})
target_link_libraries(main ${EXTRA_LIBS})