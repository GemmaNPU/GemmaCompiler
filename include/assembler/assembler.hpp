#pragma once

#include <string>
#include <variant>

#include "assembler/lexer.hpp"
#include "assembler/parser.hpp"
#include "assembler/token.hpp"
#include "assembler/instructions_set.hpp"

namespace gemma {
  namespace assembler {
    /**
     * \brief The Assebler class is a wrapper around Lexer and Parser to automate all the process.
     * 
     * This is a helper around the parser. After constructiong with a parser you probably want to
     * load an instruction set using `loadInstructionSet` method
     */
    class Assembler {
      Parser parser;
    public:
      /**
       * Build an assembler with a specific parser. To change it later call `setParser`
       */
      Assembler( Parser p ): parser{ p } {};
      
      /**
       * Automatically build an assembler with the given string as input.
       * To actually run the assembly process call the method `assemble`.
       */
      explicit Assembler( const char* s ): parser{ Parser( Lexer( s )) } {};

      /**
       * Extend the parser with a new instruction set. You probably want always to load the `BaseInstructionSet`,
       * which contains all the standard instructions. To  extend the instruction set see the `BaseInstructionSet` class
       */
      template<typename InstructionSet>
      void loadInstructionSet(){ InstructionSet::registerInstructions( parser ); }

      /**
       * Returns a reference to the parser in use
       */
      Parser& getParser(){ return this->parser; }
      
      /**
       * Change the parser in use. The state of the parser is lost, so the assemly method will restart from  begin.
       * You may want to change parser to run a different isntruction set and compare the results.
       */
      Assembler* setParser( Parser p ){ this->parser = p; return this; }

      /**
       * Run the assembler on the input string and return the list of instructions or a string explaining where an error occurred.
       * 
       * @returns A vector of instructions if everything went smooth, a string with the error reason otherwise
       */
      std::variant<std::vector<Instruction>, std::string> assemble( ){ return this->parser.parse(); }
    };
  };
}