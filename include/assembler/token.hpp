#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <ostream>

namespace gemma {
  namespace assembler  {
    /**
     * The is a portiong of string with a precise memaing, depending on the Kind
     */
    class Token {
    public:
      /**
       * There are 5 types of tokens:
       *  * UNKNOWN is used as fallback but should never occur
       *  * END is used when the end of a string is reached
       */
      enum Kind {
        UNKNOWN,
        MNEMONIC,
        NUMBER,
        FLAG,
        END
      };

      /**
       * Allows writing tokens to a stream for debug purspose
       */
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

      /**
       * Create a new token. Once created it cannot be modified
       */
      Token( Kind k, const char* begin, size_t length) noexcept : kind(k), lexeme(begin, length) {}

      /**
       * Create a new token. Once created it cannot be modified
       */
      Token( Kind k, const char* begin, const char* end) noexcept: kind(k), lexeme(begin, (std::string_view::size_type)std::distance(begin, end)) {}
      
      /**
       * Get the kind of the Token
       * 
       * @returns The kind of the token
       */
      [[ nodiscard ]] Kind getKind() const noexcept { return this->kind; }

      /**
       * Get the string to which is associated
       * 
       * @returns Get the string to which is associated
       */
      [[ nodiscard ]] std::string_view getLexeme() const noexcept { return this->lexeme; }


    private:
      Kind kind;
      std::string_view lexeme;
    };

  }
}

#endif