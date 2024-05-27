cmake_minimum_required(VERSION 3.28)

# Suppressing annoying warning about unused variable CMAKE_TOOLCHAIN_FILE
message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

project(MyProject VERSION 0.0.1)

# find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(target_sources
  src/main.cpp
)

set(target_name MyTarget)
add_executable(${target_name} ${target_sources})
target_include_directories(${target_name} PRIVATE src)

if(MSVC)
  target_compile_options(${target_name} PRIVATE /W4 /WX)
else()
  # -Werror to tread warnings as errors
  target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(GNUInstallDirs)
install(TARGETS ${target_name}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

