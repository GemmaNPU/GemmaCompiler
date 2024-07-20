#include "assembler/instruction_builders.hpp"
#include "result.hpp"

namespace gemma{
  namespace assembler{

    result::Result<GemmaInstruction, std::string> NopInstructionBuilder::build( std::vector<gemma::assembler::Token>){ 
      return result::Ok( GemmaInstruction().setOpcode(NOP_OPCODE) ); 
    }

    result::Result<GemmaInstruction, std::string> ReadHostMemoryInstructionBuilder::build( std::vector<gemma::assembler::Token> args){ 
      GemmaInstruction instruction;
      if ( args.size() == 3 ){
        if ( args[0].getKind() == gemma::assembler::Token::Kind::FLAG ||
            args[1].getKind() == gemma::assembler::Token::Kind::FLAG ||
            args[2].getKind() == gemma::assembler::Token::Kind::FLAG  ){
          return result::Err( std::string("RHM instruction doesn't expects any flag") );
        }
        long long unsigned int length, host, local;
        auto length_result = std::from_chars( args[0].getLexeme().data(), args[0].getLexeme().data() + args[0].getLexeme().size(), length ) ;
        if ( length_result.ec == std::errc::invalid_argument ){
          return result::Err( std::string("Cannot convert LENGTH into a number") );
        }
        auto host_result = std::from_chars( args[1].getLexeme().data(), args[1].getLexeme().data() + args[1].getLexeme().size(), host ) ;
        if ( host_result.ec == std::errc::invalid_argument ){
          return result::Err( std::string("Cannot convert HOST_ADDRESS into a number") );
        }
        auto local_result = std::from_chars( args[2].getLexeme().data(), args[2].getLexeme().data() + args[2].getLexeme().size(), local ) ;
        if ( local_result.ec == std::errc::invalid_argument ){
          return result::Err( std::string("Cannot convert LOCAL_ADDRESS into a number") );
        }
        instruction.setOpcode( RHM_OPCODE )
                  .setLength( length )
                  .setHostAddress( host )
                  .setLocalAddress( local );
        return result::Ok( instruction );
      } else {
        return result::Err( std::string("RHM expects 3 arguments") );
      }
    }

    result::Result<GemmaInstruction, std::string> WriteHostMemoryInstructionBuilder::build( std::vector<gemma::assembler::Token> args ){
      GemmaInstruction instruction;
      if ( args.size() == 3 ){
        if ( args[0].getKind() == gemma::assembler::Token::Kind::FLAG ||
            args[1].getKind() == gemma::assembler::Token::Kind::FLAG ||
            args[2].getKind() == gemma::assembler::Token::Kind::FLAG  ){
          return result::Err( std::string("RHM instruction doesn't expects any flag") );
        }
        long long unsigned int length, host, local;
        auto length_result = std::from_chars( args[0].getLexeme().data(), args[0].getLexeme().data() + args[0].getLexeme().size(), length ) ;
        if ( length_result.ec == std::errc::invalid_argument ){
          return result::Err( std::string("Cannot convert LENGTH into a number") );
        }
        auto host_result = std::from_chars( args[1].getLexeme().data(), args[1].getLexeme().data() + args[1].getLexeme().size(), host ) ;
        if ( host_result.ec == std::errc::invalid_argument ){
          return result::Err( std::string("Cannot convert HOST_ADDRESS into a number") );
        }
        auto local_result = std::from_chars( args[2].getLexeme().data(), args[2].getLexeme().data() + args[2].getLexeme().size(), local ) ;
        if ( local_result.ec == std::errc::invalid_argument ){
          return result::Err( std::string("Cannot convert LOCAL_ADDRESS into a number") );
        }
        instruction.setOpcode( WHM_OPCODE )
                  .setLength( length )
                  .setHostAddress( host )
                  .setLocalAddress( local );
        return result::Ok( instruction );
      } else {
        return result::Err( std::string("WHM expects 3 arguments") );
      }
    }

    result::Result<GemmaInstruction, std::string> MatrixMultiplyInstructionBuilder::build( std::vector<gemma::assembler::Token> args ){
      GemmaInstruction instruction;
      if ( args.size() == 3 ){
        if ( args[0].getKind() == gemma::assembler::Token::Kind::FLAG ||
            args[1].getKind() == gemma::assembler::Token::Kind::FLAG ||
            args[2].getKind() == gemma::assembler::Token::Kind::FLAG  ){
          return result::Err( std::string("RHM instruction doesn't expects any flag") );
        }
        long long unsigned int length, host, local;
        auto length_result = std::from_chars( args[0].getLexeme().data(), args[0].getLexeme().data() + args[0].getLexeme().size(), length ) ;
        if ( length_result.ec == std::errc::invalid_argument ){
          return result::Err( std::string("Cannot convert LENGTH into a number") );
        }
        auto host_result = std::from_chars( args[1].getLexeme().data(), args[1].getLexeme().data() + args[1].getLexeme().size(), host ) ;
        if ( host_result.ec == std::errc::invalid_argument ){
          return result::Err( std::string("Cannot convert HOST_ADDRESS into a number") );
        }
        auto local_result = std::from_chars( args[2].getLexeme().data(), args[2].getLexeme().data() + args[2].getLexeme().size(), local ) ;
        if ( local_result.ec == std::errc::invalid_argument ){
          return result::Err( std::string("Cannot convert LOCAL_ADDRESS into a number") );
        }
        instruction.setOpcode( MM_OPCODE )
                  .setLength( length )
                  .setHostAddress( host )
                  .setLocalAddress( local );
        return result::Ok( instruction );
      } else {
        return result::Err( std::string("RHM expects 3 arguments") );
      }
    }

    result::Result<GemmaInstruction, std::string> ActivationInstructionBuilder::build( std::vector<gemma::assembler::Token> args ){
      GemmaInstruction instruction;
      if ( args.size() == 3 ){
        if ( args[0].getKind() == gemma::assembler::Token::Kind::FLAG ||
            args[1].getKind() == gemma::assembler::Token::Kind::FLAG ||
            args[2].getKind() == gemma::assembler::Token::Kind::FLAG  ){
          return result::Err( std::string("RHM instruction doesn't expects any flag") );
        }
        long long unsigned int length, host, local;
        auto length_result = std::from_chars( args[0].getLexeme().data(), args[0].getLexeme().data() + args[0].getLexeme().size(), length ) ;
        if ( length_result.ec == std::errc::invalid_argument ){
          return result::Err( std::string("Cannot convert LENGTH into a number") );
        }
        auto host_result = std::from_chars( args[1].getLexeme().data(), args[1].getLexeme().data() + args[1].getLexeme().size(), host ) ;
        if ( host_result.ec == std::errc::invalid_argument ){
          return result::Err( std::string("Cannot convert HOST_ADDRESS into a number") );
        }
        auto local_result = std::from_chars( args[2].getLexeme().data(), args[2].getLexeme().data() + args[2].getLexeme().size(), local ) ;
        if ( local_result.ec == std::errc::invalid_argument ){
          return result::Err( std::string("Cannot convert LOCAL_ADDRESS into a number") );
        }
        instruction.setOpcode( ACT_OPCODE )
                  .setLength( length )
                  .setHostAddress( host )
                  .setLocalAddress( local );
        return result::Ok( instruction );
      } else {
        return result::Err( std::string("RHM expects 3 arguments") );
      }
    }
  
    result::Result<GemmaInstruction, std::string> ConfigureInstructionBuilder::build( std::vector<gemma::assembler::Token> args ){
      GemmaInstruction instruction;
      if ( args.size() == 2 ){
        if ( args[0].getKind() == gemma::assembler::Token::Kind::FLAG &&
            args[1].getKind() == gemma::assembler::Token::Kind::NUMBER ){
          // TODO: define flags and values
          return result::Ok(instruction.setOpcode( CON_OPCODE )
                              .setFlag( 0 )
                              .setLocalAddress( 0 )) ;
        }
      }
      return result::Err( std::string("CON instruction expects only a flag and a value") );
    }
  
    result::Result<GemmaInstruction, std::string> SyncInstructionBuilder::build( std::vector<gemma::assembler::Token> args ){
        GemmaInstruction instruction;
        if ( args.size() == 0 ){
          return result::Ok( instruction.setOpcode( SYN_OPCODE ) ) ;  
        }
        return result::Err( std::string("SYN instruction doesn't expects any arguemnts") );
      }
  
    result::Result<GemmaInstruction, std::string> HaltInstructionBuilder::build( std::vector<gemma::assembler::Token> args ){
        GemmaInstruction instruction;
        if ( args.size() == 0 ){
          return result::Ok( instruction.setOpcode( CON_OPCODE ) ) ;
        }
        return result::Err( std::string("HLT instruction doesn't expects any argument") );
      }
  }
}
