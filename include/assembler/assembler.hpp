#pragma once 

#include <istream>
#include <ostream>
#include "assembler/instructions/instructions_set.hpp"
#include "assembler/scanner.hpp"

namespace gemma {
  namespace assembler {

    /**
     * @brief Wrapper for the most useful operation of the assembler
     */
    class Assembler {
    public:

      /**
       * @brief Run the assembler in interactive mode, so it will wait for a string, parse if and write the result to the output stream. 
       *        The only way to exit this loop is throug Ctrl-C
       */
      template<typename Scanner, typename Formatter>
      void interactive ( std::istream& input, std::ostream& output, std::string prompt = "[gemma assembler]>>> ") const noexcept {
        std::string input_string;
        while ( true ){
          output << prompt;
          std::getline( input, input_string );
          Scanner scanner( input_string );
          Formatter formatter{ output };
          auto instruction = scanner.getNextInstruction();
          if ( instruction.index() == 0 ){
            if( std::get<0>( instruction ).has_value() ){
              formatter.format( std::get<0>( instruction ).value() );
            }
          } else {
            output << "Error: " << std::get<1>( instruction );
            output << '\n';
          }
        }
      }
    };

  }
}