#pragma once

#include <variant>
#include <regex>
#include "assembler/instructions/definitions.hpp"
#include "assembler/errors.hpp"

namespace gemma {
  namespace assembler {

    /**
     * @brief Group multiple instruction together
     */
    template<typename... Is>
    struct InstructionSet;

    /**
     * @brief Base case
     */
    template<>
    struct InstructionSet<>{
      /**
       * @breif When building instruction from an empty instruction set an error will be returned.
       */
      static std::variant<instruction_t, error> build( std::string & ){
        return error{"No instruction found"};
      }
    };

    /**
     * @brief Inductive case
     */
    template<typename Instruction, typename... Is>
    struct InstructionSet<Instruction, Is...>{

      /**
       * @brief Try parsing a line and convert into an instruction
       * 
       * @return an instruction_t if the instruction was valid, otherwise an error string
       */
      static std::variant<instruction_t, error> build( std::string &line ){
        // Automaticall add comment regexat the end
        std::regex re{ Instruction::getRegexString() + " *(;.*)?" };
        std::smatch smatch; 
        if(std::regex_match( line, smatch, re )){
          return Instruction::build( smatch );
        } else {
          return InstructionSet<Is...>::build( line );
        }
      }
      
    };
  }
}