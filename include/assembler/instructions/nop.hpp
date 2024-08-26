#pragma once

#include <string>
#include <regex>
#include "assembler/instructions/definitions.hpp"

namespace gemma{
  namespace assembler {
    
    /**
     * @brief NOP Instruction. Skip the next cycle in the NPU.
     */
    struct NOP {
      /**
       * @brief Get the mnemonic of this instruction
       */
      static std::string getMnemonic(){ return "NOP"; }

      /**
       * @brief Get the pattern to match this instruction from a string
       */
      static std::string getRegexString(){ return "NOP"; }

      /**
       * @brief Return the opcode of the instruction.
       * 
       * The combination of getOpcode() and getFlag() should be unique 
       */
      static opcode_t getOpcode(){ return 0; }

      /**
       * @brief Return optional flags for this instruction
       * 
       * The combination of getOpcode() and getFlag() should be unique 
       */
      static flag_t   getFlag(){ return 0; }

      /**
       * @brief Get the raw instruction
       */
      static instruction_t build( std::smatch & ){ return instruction_t{ NOP::getOpcode(), NOP::getFlag() ,0, {0,0,0,0,0,0,0,0}, {0,0,0}}; }
    };
  }
}