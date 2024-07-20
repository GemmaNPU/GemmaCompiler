#ifndef GEMMA_ASSEMBLER
#define GEMMA_ASSEMBLER

#include "assembler/instruction_builders.hpp"
#include "assembler/lexer.hpp"
#include "assembler/parser.hpp"
#include "assembler/token.hpp"

namespace gemma {
  namespace assembler {
    /**
     * \brief The Assebler class is a wrapper around Lexer and Parser to automate all the process
     */
    class Assembler {
      Parser parser;
    public:
      Assembler() = default;

      Parser& getParser(){ return this->parser; }
      Assembler* setParser( Parser p ){ this->parser = p; return this; }
      std::vector<GemmaInstruction> assemble( ){ return this->parser.parse(); }
    };
  };
}

#endif