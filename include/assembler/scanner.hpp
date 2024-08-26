#pragma once

#include <variant>
#include <string>
#include <optional>
#include <regex>
#include "assembler/instructions/definitions.hpp"
#include "assembler/errors.hpp"

namespace gemma {
  namespace assembler {

    /**
     * @brief This is the most important class that converts input into instructions (is both a lexer and parser fused together).
     */
    template<typename InstructionSet>
    class Scanner{
      /**
       * Store input string program
       */
      std::string m_program;
      /**
       * Current curors, to be used as a generator
       */
      std::string::size_type m_current_line = 0;
      
      /**
       * Store last parsed cursor, next callwill start from here
       */
      std::string::size_type m_previous_line = 0;
    public:
      /**
       * @brief Build a scanner from the input string
       */
      Scanner( std::string program ): m_program{ std::move(program) + '\n' } {}

      /**
       * @brief Consume the input string and get thenext token
       * 
       * @return empty optional if reached end of string,
       *         full optional<instruction_t> if found a valid instruction
       *         error if no instruction is fould and end is not reached
       */
      std::variant<std::optional<instruction_t>, error> getNextInstruction(){
        if ( (m_current_line = m_program.find('\n', m_previous_line)) == std::string::npos){ return std::optional<instruction_t>{}; }
        std::string next_line = m_program.substr(m_previous_line, m_current_line - m_previous_line);
        m_previous_line = m_current_line + 1;
        
        if( next_line.empty() ){ return getNextInstruction(); }
        if( std::regex_match( next_line, std::regex(" *(;.*)?") ) ){ return getNextInstruction(); }

        std::variant<instruction_t, error> result = InstructionSet::build( next_line );
        if( result.index() == 1){
          return { std::get<1>( result )};
        } else {
          return { std::get<0>( result )};
        }
      }

    };
  }
}