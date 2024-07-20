#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <ostream>

namespace gemma {
  namespace assembler  {
    class Token {
    public:
      enum Kind {
        UNKNOWN,
        MNEMONIC,
        NUMBER,
        FLAG,
        END
      };
      friend std::ostream& operator<<(std::ostream &o, Kind k){
        switch (k){
          case Kind::UNKNOWN:
            o << "UNKNOWN";
            break;
          case Kind::MNEMONIC:
            o << "MNEMONIC";
            break;
          case Kind::FLAG:
            o << "FLAG";
            break;
          case Kind::NUMBER:
            o << "NUMBER";
            break;
          case Kind::END:
            o << "<<EOF>>";
            break;
          default:
            break;
        }
        return o;
      }

      Token( Kind k ): kind( k ){};
      Token( Kind k, const char* begin, size_t length): kind(k), lexeme(begin, length) {}
      Token( Kind k, const char* begin, const char* end): kind(k), lexeme(begin, (std::string_view::size_type)std::distance(begin, end)) {}
      
      Kind getKind(){ return this->kind; }
      Token setKind(Kind k){ this->kind = k; return *this; }

      std::string_view getLexeme(){ return this->lexeme; }
      Token setLexeme( std::string_view l ){ this->lexeme = l; return *this; }
      Token setLexeme( const char* begin, size_t length ){ this->lexeme = std::string_view(begin, length); return *this;}
      Token setLexeme( const char* begin, const char* end){ this->lexeme = std::string_view(begin, (std::string_view::size_type)std::distance(begin, end)); return *this; }

    private:
      Kind kind;
      std::string_view lexeme;
    };

  }
}

#endif