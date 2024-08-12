#include "assembler/parser.hpp"
#include "instructions/instruction.hpp"

[[ nodiscard ]] std::variant<std::vector<gemma::Instruction>, std::string> gemma::assembler::Parser::parse() noexcept {
        std::vector<Instruction> result;
        Token token = m_lexer.next();
        Builder op_builder;

        while( token.getKind() != Token::Kind::END ){
          if ( token.getKind() != Token::Kind::MNEMONIC ){
            std::string error { "Expected a menomic, got " };
            error += token.getLexeme();
            return std::variant<std::vector<Instruction>, std::string>{ error };
          }
          if ( !m_builders.contains( std::string{ token.getLexeme() } )){
            std::string error { "Unknown mnemonic: " };
            error += token.getLexeme();
            return std::variant<std::vector<Instruction>, std::string>{ error };
          } else {
            op_builder = m_builders.find( std::string { token.getLexeme() } )->second;
          }
          token = m_lexer.next();
          std::optional<std::string_view> flag;
          std::array<std::optional<uint64_t>, 3> options;
          std::array<std::optional<uint64_t>, 3>::size_type current_option_index = 0;
          if ( token.getKind() == Token::Kind::FLAG){
            flag = token.getLexeme();
            token = m_lexer.next();
          }
          while ( token.getKind() == Token::Kind::NUMBER && current_option_index < 3 ) {
            uint64_t parse_result;
            [[ maybe_unused ]]
            std::from_chars_result chars_result = std::from_chars(token.getLexeme().data(), token.getLexeme().data() + token.getLexeme().size(), parse_result);
            // TODO: add checks for conversion errors
            options[current_option_index] = parse_result;
            current_option_index++;
            token = m_lexer.next();
          }
          BuilderReturnType instruction = op_builder( flag, options );
          if ( instruction.index() == 1 ){
            std::string error { "Error while parsing " };
            error += token.getLexeme();
            error += ": ";
            error += std::get<std::string>( instruction );
            return std::variant<std::vector<Instruction>, std::string>{ error };
          }
          result.push_back( std::get<Instruction>( instruction ) );
        }
        return result;
}