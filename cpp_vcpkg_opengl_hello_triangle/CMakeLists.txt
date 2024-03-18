cmake_minimum_required(VERSION 3.28)

# Suppressing annoying warning about unused variable CMAKE_TOOLCHAIN_FILE
message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

project(MyProject VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(soil2 CONFIG REQUIRED)

set(target_sources
  src/main.cpp
  src/pch.h
)

set(target_name MyTarget)
add_executable(${target_name} ${target_sources})
target_precompile_headers(${target_name} PRIVATE src/pch.h)
target_link_libraries(${target_name} PRIVATE GLEW::GLEW)
target_link_libraries(${target_name} PRIVATE glfw)
target_link_libraries(${target_name} PRIVATE glm::glm)
target_link_libraries(${target_name} PRIVATE soil2)

set_target_properties(${target_name} PROPERTIES INSTALL_RPATH "$ORIGIN/../lib")

target_include_directories(${target_name} PRIVATE src)

if(MSVC)
  target_compile_options(${target_name} PRIVATE /W4 /WX)
else()
  # -Werror to tread warnings as errors
  target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(GNUInstallDirs)
install(TARGETS ${target_name} RUNTIME_DEPENDENCIES
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#get_target_property(GLEW_LIBRARY_DEBUG GLEW::GLEW IMPORTED_LOCATION_DEBUG)
#install(FILES ${GLEW_LIBRARY_DEBUG} DESTINATION ${CMAKE_INSTALL_LIBDIR})

