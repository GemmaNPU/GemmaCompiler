#pragma once

#include <ostream>
#include <iomanip>
#include "assembler/formatters/instruction_formatter.hpp"

namespace gemma {
  namespace assembler {
    
    /**
     * @brief Formatter that writes the instruction in ahuman readable hex format, but not suitable for binary files
     */
    class HumanHexInstructionFormatter: public InstructionFormatter {
    public:
    /**
     * @brief Constructor. See base class for details
     */
      HumanHexInstructionFormatter(std::ostream& output): InstructionFormatter{ output }{}

      /**
       * @brief Write the instruction in the stream as a stream of chars [00-ff]
       */
      void format( instruction_t &instruction ) override { 
        this->m_output << std::setfill('0') << std::setw(2) << std::hex << std::get<0>( instruction ) + '\0';
        this->m_output << std::setfill('0') << std::setw(2) << std::hex << std::get<1>( instruction ) + '\0';
        this->m_output << std::setfill('0') << std::setw(2) << std::hex << std::get<2>( instruction ) + '\0';
        for(size_t i = 0; i < 8; ++i ){
          this->m_output << std::setfill('0') << std::setw(2) << std::hex << std::get<3>( instruction )[i] + '\0';
        }
        for(size_t i = 0; i < 3; ++i ){
          this->m_output << std::setfill('0') << std::setw(2) << std::hex << std::get<4>( instruction )[i] + '\0';
        }
        this->m_output << '\n';
      }
    };
  }
}