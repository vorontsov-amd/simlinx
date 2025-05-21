file(GLOB SOURCES CONFIGURE_DEPENDS "cpu/*.cc" 
                                    "syscall/*.cc"
                                    "virtual-memory/*.cc"
                                    "cache/*.cc"
                                    "stat/*.cc")
add_subdirectory(sim)