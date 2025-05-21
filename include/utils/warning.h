#pragma once
#include <iostream>

#define BAD_IMPLEMENTED(message)                                               \
  {                                                                            \
    std::cout << "Function " << __PRETTY_FUNCTION__ << " is bad implemented:" << std::endl;      \
    std::cout << message << std::endl;                                             \
  }

#define NotImplemented()                                                      \
  { std::cout << "Function " << __PRETTY_FUNCTION__ << " is not implemented" << std::endl; }
