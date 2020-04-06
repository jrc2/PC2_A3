cmake_minimum_required(VERSION 3.15)
project(MoviePlaiterCLion)

set(CMAKE_CXX_STANDARD 14)

include_directories(Model)
include_directories(Utils)
include_directories(View)

add_executable(MoviePlaiterCLion
        Model/Movie.cpp
        Model/Movie.h
        Utils/Utils.cpp
        Utils/Utils.h
        View/AddMovieWindow.cpp
        View/AddMovieWindow.h
        View/DeleteMovieWindow.cpp
        View/DeleteMovieWindow.h
        View/MovieLibraryWindow.cpp
        View/MovieLibraryWindow.h
        View/OKCancelWindow.cpp
        View/OKCancelWindow.h
        main.cpp)

set(FLTK_SKIP_FLUID true)
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${FLTK_BASE_LIBRARY} ${FLTK_PLATFORM_DEPENDENT_LIBS})