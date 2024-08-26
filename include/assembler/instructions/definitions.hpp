#pragma once

#include <array>
#include <tuple>

namespace gemma {
  namespace assembler {
    /**
     * @brief The size of the opcode 
     */
    using opcode_t = char;

    /**
     * @brief The size of the flag 
     */
    using flag_t = char;

    /**
     * @brief The size of the length
     */
    using length_t = char;

    /**
     * @brief The address of the host  
     */
    using host_address_t = std::array<char, 8>;

    /**
     * @brief The address of the npu local memory 
     */
    using local_address_t = std::array<char,3>;

    /**
     * @brief Base class for each instruction. This only specifies the sizeof each component of the instruction
     */
    using instruction_t = std::tuple<opcode_t, flag_t, length_t, host_address_t, local_address_t>;
  }
}