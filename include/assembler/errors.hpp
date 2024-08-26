#pragma once

#include <string>

namespace gemma {
  namespace assembler {

    /**
     * @brief Struct that represent an error in the program
     */
    struct error :public std::string {};

  }
}