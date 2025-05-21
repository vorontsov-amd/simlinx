cmake_minimum_required(VERSION 3.20)
project(simlinx)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (NOT DEFINED LIEF_DIR)
  if (NOT EXISTS lib/LIEF)
    execute_process(COMMAND bash installLIEF.sh)
  endif()
  set(LIEF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/LIEF/lib/cmake/LIEF)
endif()

execute_process(COMMAND python3 generate/generator.py)
execute_process(COMMAND python3 generate/syscall/sysGen.py)
execute_process(COMMAND python3 generate/autoClangFormat.py)

include_directories(include)
add_subdirectory(src)