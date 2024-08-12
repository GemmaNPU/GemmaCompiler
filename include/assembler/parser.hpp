#pragma once 

#include <vector>
#include <unordered_map>
#include <string>
#include <variant>
#include <array>
#include <optional>
#include <functional>
#include <charconv>
#include <cstdint>

#include "assembler/lexer.hpp"
#include "instructions/instruction.hpp"
#include "instructions/flag.hpp"

using BuilderReturnType = std::variant<gemma::Instruction, std::string>;
using Builder = BuilderReturnType (*)( std::optional<std::string_view>, std::array< std::optional<uint64_t>, 3>);
using Menomic = std::string;

namespace gemma {
  namespace assembler { 

    /**
     * The Parser uses the stream of tokens obtained from the lexer and converts them in a list of instructions
     */
    class Parser {
      /**
       * The lexer used to convert a string into the Tokens
       */
      Lexer m_lexer;
      /**
       * A map that given the mnemonic finds the right instruction builder
       */
      std::unordered_map<Menomic, Builder> m_builders;

    public:
      /**
       * Create a new Parser using a specific lexer
       */
      Parser( Lexer lexer ): m_lexer{ lexer }{}

      /**
       * Register a new instruction.
       * If the mnemonic is already used, it simply replace the old one with the one provided, without issuing warnings.
       * 
       * @returns A reference to self to chain multiple registrations
       */
      Parser& addInstructionBuilder( std::string mnemonic, Builder builder ) noexcept { m_builders[mnemonic] = builder; return *this; }

      /**
       * This is where the magic happens, and converts the input into a list of instructions.
       * 
       * @returns A vector of instructions if everything went smooth, a string with the error reason otherwise
       */
      [[ nodiscard ]] std::variant<std::vector<Instruction>, std::string> parse() noexcept;
    };
  };  
}