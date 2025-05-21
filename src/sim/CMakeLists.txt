# Find LIEF. If LIEF was not installed into a default system directory then
# specify the following option during CMake configuration:
# -DLIEF_DIR=<LIEF install prefix>/share/LIEF/cmake
find_package(LIEF REQUIRED COMPONENTS STATIC) # COMPONENTS: <SHARED | STATIC> - Default: STATIC
# add_subdirectory(${PROJECT_SOURCE_DIR}/xbyak ${CMAKE_CURRENT_BINARY_DIR}/xbyak)

list(APPEND SOURCES main.cc)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE LIEF::LIEF)
# target_link_libraries(${PROJECT_NAME} PRIVATE xbyak)