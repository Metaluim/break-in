project(break-in)
cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -mwindows)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -g -mwindows")
set(SRCS ./src/main.cpp
        ./src/game.cpp
        ./src/gfx.cpp
        ./src/model.cpp
        ./src/physics.cpp)
#set(STATIC_LIBS ./lib/libBox2D.a)
set(STATIC_LIBS ${CMAKE_SOURCE_DIR}./lib/libBox2D.a  ${CMAKE_SOURCE_DIR}./lib/libSDL2main.a ${CMAKE_SOURCE_DIR}./lib/libSDL2.a ${CMAKE_SOURCE_DIR}./lib/libSDL2_image.a)
#set(SHARED_LIBS SDL2)
set(SHARED_LIBS mingw32 m dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)

include_directories(./include)
include_directories(./include/SDL2)
link_directories(./lib)

#add_executable(break-in ${SRCS} ${STATIC_LIBS})
add_executable(break-in ${SRCS})
target_link_libraries(break-in ${SHARED_LIBS})
target_link_libraries(break-in ${STATIC_LIBS})
target_link_libraries(break-in ${SHARED_LIBS})
