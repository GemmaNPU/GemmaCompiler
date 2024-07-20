#ifndef GEMMA_ASSEMBLER_LEXER_HPP
#define GEMMA_ASSEMBLER_LEXER_HPP

#include "assembler/token.hpp"

namespace gemma {
  namespace assembler {
    class Lexer {
    private:
      const char* cursor; 
      [[ nodiscard]] char peek() const& noexcept;
      char get() noexcept;
      Lexer setCursor(const char *c) noexcept;

    public:
      Lexer(const char* c): cursor( c ) {};
      Lexer() = default;
      Token next() noexcept ;
      ~Lexer() = default ;
    };
  }  
}

#endif 