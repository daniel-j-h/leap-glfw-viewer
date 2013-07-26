#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "Renderer.h"


int main() try {
  Renderer r;
  r.render();
} catch(const std::runtime_error& e) {
  std::cerr << e.what() << std::endl;
  return EXIT_FAILURE;
}

