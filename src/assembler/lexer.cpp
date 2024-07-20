#include "assembler/lexer.hpp"
#include "assembler/token.hpp"

namespace gemma {
  namespace assembler {
    namespace {
      bool is_space( char c ) noexcept {  
        switch (c) {
        case ' ':
        case '\n':
        case '\t':
        case '\r':
        case ',':
          return true;
        default:
          return false;
        }
      }

      bool is_number( char c ) noexcept {
        return isdigit( c );
      }

      bool is_identifier_char( char c ) noexcept {
        return isalnum(c);
      }
    }
    [[nodiscard ]] char Lexer::peek() const& noexcept { return *cursor; };
    char Lexer::get() noexcept { return *cursor++; }
    Lexer Lexer::setCursor(const char* c) noexcept{ cursor = c; return *this; }
    Token Lexer::next() noexcept {
        while (is_space( peek() )) {
          get();
        }
        if( peek() == '\0'){ 
          return Token( Token::Kind::END, cursor, 1); 
        }
        // If it's a letter ( lower or upper ) we compose the whole identifier
        if( isalpha( peek() ) ){
          const char* begin = cursor;
          get();
          while( gemma::assembler::is_identifier_char( peek() ) ){ get(); }
          return Token(Token::Kind::MNEMONIC, begin, cursor);
        }
        if ( peek() == '.'){
          get();
          const char* begin = cursor;
          while( gemma::assembler::is_identifier_char( peek() )){ get(); }
          return Token(Token::Kind::FLAG, begin, cursor);
        }
        // If it's a number
        if ( isdigit( peek() ) ){
          const char* begin = cursor;
          get();
          while( gemma::assembler::is_number( peek() )){ get(); }
          return Token( Token::Kind::NUMBER, begin, cursor );
        }
        // If it's a comment we simply skip 
        if ( peek() == ';' ){
          while( peek() != '\n' ){ get(); }
          return next();
        }

        const char* begin = cursor;
        get();
        return Token( Token::Kind::UNKNOWN, begin, cursor);
      };
  }
}