cmake_minimum_required(VERSION 3.7)
project(app)

set(CMAKE_CXX_STANDARD 17)

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif (NOT MSVC)

if (MSVC)
    # prevent garbling caused by utf-8 without BOM encoding on msvc
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif (MSVC)

# targets ----------------------
set(SOURCE_FILES
        Window.cpp Window.h Image.cpp Image.h CanvasWindow.cpp CanvasWindow.h
        Vector.cpp Vector.h Vector2.cpp Vector2.h KeyCode.h Rasterizer.cpp Rasterizer.h
        Matrix2.cpp Matrix2.h  Matrix.cpp Matrix.h Vector4.cpp Vector4.h Matrix4.cpp Matrix4.h )

add_executable(main WIN32
        ${SOURCE_FILES} main.cpp)


add_executable(DrawLineTester WIN32
        ${SOURCE_FILES} DrawLineTester.cpp)


add_executable(AdjacentTriangleTester WIN32
        ${SOURCE_FILES} AdjacentTriangleTester.cpp)
