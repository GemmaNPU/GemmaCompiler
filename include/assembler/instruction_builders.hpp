#ifndef GEMMA_ASSEMBLER_INSTRUCTION_BUILDERS_HPP
#define GEMMA_ASSEMBLER_INSTRUCTION_BUILDERS_HPP

#include <charconv>
#include "result.hpp"
#include "instructions.hpp"
#include "assembler/token.hpp"

namespace gemma {
  namespace assembler {
    class GemmaInstructionBuilder {
    public: 
      virtual result::Result<GemmaInstruction, std::string> build( std::vector<gemma::assembler::Token> ) = 0;
    };

    class NopInstructionBuilder: public GemmaInstructionBuilder {
    public:
      result::Result<GemmaInstruction, std::string> build( std::vector<gemma::assembler::Token>);
    };

    class ReadHostMemoryInstructionBuilder: public GemmaInstructionBuilder {
    public:
      result::Result<GemmaInstruction, std::string> build( std::vector<gemma::assembler::Token> args);
    };

    class WriteHostMemoryInstructionBuilder: public GemmaInstructionBuilder {
      result::Result<GemmaInstruction, std::string> build ( std::vector<gemma::assembler::Token> args );
    };

    class MatrixMultiplyInstructionBuilder: public GemmaInstructionBuilder {
      result::Result<GemmaInstruction, std::string> build ( std::vector<gemma::assembler::Token> args );
    };

    class ActivationInstructionBuilder: public GemmaInstructionBuilder {
      result::Result<GemmaInstruction, std::string> build ( std::vector<gemma::assembler::Token> args );
    };

    class ConfigureInstructionBuilder: public GemmaInstructionBuilder {
      result::Result<GemmaInstruction, std::string> build ( std::vector<gemma::assembler::Token> args );
    };

    class SyncInstructionBuilder: public GemmaInstructionBuilder {
      result::Result<GemmaInstruction, std::string> build ( std::vector<gemma::assembler::Token> args );
    };

    class HaltInstructionBuilder: public GemmaInstructionBuilder {
      result::Result<GemmaInstruction, std::string> build ( std::vector<gemma::assembler::Token> args );
    };
  }
}


#endif 