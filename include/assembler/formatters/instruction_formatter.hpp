#pragma once

#include <ostream>
#include "assembler/instructions/definitions.hpp"

namespace gemma {
  namespace assembler {
    /**
     * @brief Abstract class with the purpose of writing the instruction passed into a stream.
     * 
     */
    class InstructionFormatter {
    protected:
      /**
       * Keep a reference to the stream that will receive the instruction.
       */ 
      std::ostream& m_output;

      /**
       * @brief Simple constructor that jst stores the reference to the stream
       */
      InstructionFormatter( std::ostream &output ): m_output{ output }{}

      /**
       * @brief Write the instrucion to the stored stream. Each child class should implement this differently.
       */
      virtual void format( instruction_t & ) { };
    };
  }
}