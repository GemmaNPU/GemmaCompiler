#include <vector>
#include <memory>
#include "instructions.hpp"
#include "assembler/parser.hpp"
#include "assembler/instruction_builders.hpp"

namespace gemma{
  namespace assembler {
    std::vector<GemmaInstruction> Parser::parse(){
      std::vector<GemmaInstruction> instructions;
      Token token = lexer.next();
      std::unique_ptr<GemmaInstructionBuilder> builder;

      if ( token.getKind() != Token::Kind::MNEMONIC){
        throw std::logic_error("The first token must be an instruction");
      }

      while( token.getKind() != Token::Kind::END ){
        std::vector<Token> args;
        if ( token.getKind() == Token::Kind::MNEMONIC ){
          builder = getBuilder( token.getLexeme() );
          token = lexer.next();
        }
        if ( token.getKind() == Token::Kind::FLAG){
          args.push_back( token );
          token = lexer.next();
        }
        if ( token.getKind() == Token::Kind::NUMBER ){
          args.push_back( token );
          token = lexer.next();
        }
        if ( token.getKind() == Token::Kind::NUMBER ){
          args.push_back( token );
          token = lexer.next();
        }
        if ( token.getKind() == Token::Kind::NUMBER ){
          args.push_back( token );
          token = lexer.next();
        }
        auto instruction_result = builder->build( args );
        if ( instruction_result.is_ok() ){
          instructions.push_back( instruction_result.ok_unchecked() );
        } else {
          throw std::domain_error("Cannot generate the assembly: " + instruction_result.err_unchecked() );
        }
      }
      return instructions;
    };

    std::unique_ptr<GemmaInstructionBuilder> Parser::getBuilder( std::string_view menemonic){
      if ( menemonic == "NOP" ){
        std::unique_ptr<NopInstructionBuilder> builder ( new NopInstructionBuilder() ) ;
        return builder;
      } else if ( menemonic == "RHM") {
        std::unique_ptr<ReadHostMemoryInstructionBuilder> builder ( new ReadHostMemoryInstructionBuilder() );
        return builder;
      } else if ( menemonic == "WHM" ){
        std::unique_ptr<WriteHostMemoryInstructionBuilder> builder ( new WriteHostMemoryInstructionBuilder() );
        return builder;
      } else if ( menemonic == "MM" ){
        std::unique_ptr<MatrixMultiplyInstructionBuilder> builder ( new MatrixMultiplyInstructionBuilder() );
        return builder;
      } else if ( menemonic == "ACT" ){
        std::unique_ptr<ActivationInstructionBuilder> builder ( new ActivationInstructionBuilder() );
        return builder;
      } else if ( menemonic == "CON" ){
        std::unique_ptr<ConfigureInstructionBuilder> builder ( new ConfigureInstructionBuilder() );
        return builder;
      } else if ( menemonic == "SYN" ){
        std::unique_ptr<SyncInstructionBuilder> builder ( new SyncInstructionBuilder() );
        return builder;
      } else if ( menemonic == "HLT" ){
        std::unique_ptr<HaltInstructionBuilder> builder ( new HaltInstructionBuilder() );
        return builder;
      } else {
        throw std::domain_error( "Unknown Token" );
      }
    }
  }
} 
