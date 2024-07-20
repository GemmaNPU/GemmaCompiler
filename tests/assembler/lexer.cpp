#include <gtest/gtest.h>
#include <string>
#include "assembler/lexer.hpp"
#include "assembler/token.hpp"

TEST(AssemblerLexerTest, NopString){
  std::string code = "NOP";
  
  gemma::assembler::Lexer lexer{ code.c_str() };
  gemma::assembler::Token nop_token = lexer.next();

  ASSERT_EQ( nop_token.getKind(), gemma::assembler::Token::Kind::MNEMONIC );
  ASSERT_EQ( nop_token.getLexeme(), "NOP");
  ASSERT_EQ( lexer.next().getKind(), gemma::assembler::Token::Kind::END );
}

TEST(AssemblerLexerTest, EmptyString) {
  std::string code = "";
  
  gemma::assembler::Lexer lexer{ code.c_str() };
  gemma::assembler::Token end_token = lexer.next();

  ASSERT_EQ( end_token.getKind(), gemma::assembler::Token::Kind::END );
  ASSERT_EQ( *(end_token.getLexeme().data()), '\0' );
}

TEST(AssemblerLexerTest, CommasAsSpaces) {
  std::string code_comma = "NOP,NOP,NOP";
  std::string code_spaces = "NOP NOP NOP";
  
  gemma::assembler::Lexer lexer_comma{ code_comma.c_str() };
  gemma::assembler::Lexer lexer_space{ code_spaces.c_str() };

  auto token_comma = lexer_comma.next();
  auto token_space = lexer_space.next();
  
  while( token_comma.getKind() != gemma::assembler::Token::Kind::END && 
         token_space.getKind() != gemma::assembler::Token::Kind::END ){
    ASSERT_EQ( token_comma.getKind(), token_space.getKind() );
    token_comma = lexer_comma.next();
    token_space = lexer_space.next();
  }
}