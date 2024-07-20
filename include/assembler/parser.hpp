#ifndef GEMMA_ASSEMBLER_PARSER_HPP
#define GEMMA_ASSEMBLER_PARSER_HPP

#include <vector>
#include "assembler/lexer.hpp"
#include "assembler/instruction_builders.hpp"
#include "instructions.hpp"

namespace gemma {
  namespace assembler { 
    class Parser {
      Lexer lexer;
      [[nodiscard]] std::unique_ptr<GemmaInstructionBuilder> getBuilder( std::string_view );

    public:
      Parser( Lexer l ): lexer( l ) {};
      [[nodiscard]] std::vector<GemmaInstruction> parse();
      ~Parser() = default;
    };
  };
}

#endif