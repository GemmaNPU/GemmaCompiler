#pragma once

#include <regex>
#include <string>
#include "assembler/instructions/definitions.hpp"

namespace gemma {
  namespace assembler {
    
    /**
     * @brief HALT Instruction. Stop the execution on the NPU.
     */
    struct HALT {
      /**
       * @brief Get the mnemonic of this instruction
       */
      static std::string getMnemonic(){ return "HALT"; }

      /**
       * @brief Get the pattern to match this instruction from a string
       */
      static std::string getRegexString(){ return "HALT"; }

      /**
       * @brief Return the opcode of the instruction.
       * 
       * The combination of getOpcode() and getFlag() should be unique 
       */
      static opcode_t getOpcode(){ return 1; }

      /**
       * @brief Return optional flags for this instruction
       * 
       * The combination of getOpcode() and getFlag() should be unique 
       */
      static flag_t   getFlag(){ return 0; }

      /**
       * @brief Get the raw instruction
       */
      static instruction_t build( std::smatch & ){ return instruction_t{ HALT::getOpcode(), HALT::getFlag() ,0, {0,0,0,0,0,0,0,0}, {0,0,0}}; }
    };
  }
}