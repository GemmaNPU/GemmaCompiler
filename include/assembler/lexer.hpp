#pragma once

#include "assembler/token.hpp"

namespace gemma {
  namespace assembler {
    /**
     * The purpose of the Lexer is to convert a string into a stream of Tokens,
     * so the next steps are easier to handle
     */
    class Lexer {
    private:
      /**
       * Store the current position inside the string
       */
      const char* cursor; 
      
      /**
       * Read the next char without incrementing the cursor position
       * 
       * @returns The next char in the input string
       */
      [[ nodiscard]] char peek() const& noexcept;

      /**
       * Consume the next char
       * 
       * @returns The next char in the input string
       */
      char get() noexcept;

      /**
       * Jump the cursor to another character in the input string 
       */
      Lexer setCursor(const char *c) noexcept;

    public:
      /**
       * Create a new Lexer with the curor pointing at at the given position
       */
      Lexer(const char* c): cursor( c ) {};

      /**
       * Step on the string until a new token valid token is found and then returns it
       * 
       * @returns The next token of the program
       */
      Token next() noexcept ;
    };
  }  
}