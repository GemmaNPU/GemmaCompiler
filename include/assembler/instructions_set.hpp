#pragma once

#include <optional>
#include <array>
#include <variant>
#include <cstring>

#include "parser.hpp"
#include "instructions/instruction.hpp"
#include "instructions/opcodes.hpp"

#define ERROR_IF_FLAG( flag ) if ( flag.has_value() ){ return std::variant<Instruction, std::string>{ std::string{ "Instruction don't require flags" } }; } 
#define ERROR_IF_ARGS( args ) for(size_t i = 0; i  < 3; ++i){ if ( args[i].has_value() ) { return std::variant<Instruction, std::string> { "Instruction doesn't require arguments" }; }  };

namespace gemma {
  namespace assembler {

    /**
     * Utility class to define a group of Instructions
     */
    template<typename ...Instructions>
    class UnionInstructionSet: public Instructions... {
    public:
      /**
       * Given the list of Instructions register all the instructions to the parser list of instructions
       */
      static void registerInstructions( Parser& parser ) noexcept {
        (Instructions::registerInstructions( parser ), ...);
      }
    };

    /** 
     *  Class for the NOP instruction
     */
    class NopInstruction {
    public:
    /**
     * Register the instruction 'NOP'. This instruction requires neither flags nor arguments, so it returns an error if those are provided.
     */
      static void registerInstructions( Parser& parser ) noexcept {
        parser.addInstructionBuilder( "NOP", []( std::optional<std::string_view> flag , std::array<std::optional<u_int64_t>, 3> args ){
            ERROR_IF_FLAG( flag )
            ERROR_IF_ARGS( args )
            Instruction nop;
            return std::variant<Instruction, std::string> { nop };
          } 
        );
      }
    };

    /**
     * Class for the HALT instruction
     */
    class HaltInstruction {
    public:
    /**
     * Register the instruction 'NOP'. This instruction requires neither flags nor arguments, so it returns an error if those are provided.
     */
      static void registerInstructions( Parser& parser ) noexcept {
        parser.addInstructionBuilder( "HALT", []( std::optional<std::string_view> flag, std::array<std::optional<u_int64_t>, 3> args){
            ERROR_IF_FLAG( flag )
            ERROR_IF_ARGS( args )
            Instruction hlt;
            hlt.setOpcode( OPCODES::HALT );
            return std::variant<Instruction, std::string> { hlt };
          } 
        );
      }
    };

    /** Class for the READ instruction */
    class ReadHostMemory{
    public:
    /**
     * Register the instruction 'READ'. This instruction requires all 3 arguments, but no flags. 
     */
      static void registerInstructions( Parser& parser ) noexcept {
        parser.addInstructionBuilder( "READ", []( std::optional<std::string_view> flag, std::array<std::optional<u_int64_t>, 3> args){
            ERROR_IF_FLAG( flag )
            Instruction rhm;
            rhm.setOpcode( OPCODES::RHM );
            if ( args[0].has_value() ){
              rhm.setLength( args[0].value() );
            } else {
              return std::variant<Instruction, std::string>{ std::string("Read Host Memory requires the Length argument") };
            }
            if ( args[1].has_value() ){
              rhm.setHostAddress( args[1].value() );
            } else {
              return std::variant<Instruction, std::string>{ std::string("Read Host Memory requires the Host Memory Address argument") };
            }
            if ( args[2].has_value() ){
              rhm.setLocalAddress( args[2].value() );
            } else {
              return std::variant<Instruction, std::string>{ std::string("Read Host Memory requires the Local Memory Address argument") };
            }
            return std::variant<Instruction, std::string> { rhm };
          } 
        );
      }
    };

    /** Class for the WRITE instruction */
    class WriteHostMemory{
    public:
    /**
     * Register the instruction 'WRITE'. This instruction requires all 3 arguments, but no flags. 
     */
      static void registerInstructions( Parser& parser ) noexcept {
        parser.addInstructionBuilder( "WRITE", []( std::optional<std::string_view> flag, std::array<std::optional<u_int64_t>, 3> args){
            ERROR_IF_FLAG( flag )
            Instruction whm;
            whm.setOpcode( OPCODES::WHM );
            if ( args[0].has_value() ){
              whm.setLength( args[0].value() );
            } else {
              return std::variant<Instruction, std::string>{ std::string("Read Host Memory requires the Length argument") };
            }
            if ( args[1].has_value() ){
              whm.setHostAddress( args[1].value() );
            } else {
              return std::variant<Instruction, std::string>{ std::string("Read Host Memory requires the Host Memory Address argument") };
            }
            if ( args[2].has_value() ){
              whm.setLocalAddress( args[2].value() );
            } else {
              return std::variant<Instruction, std::string>{ std::string("Read Host Memory requires the Local Memory Address argument") };
            }
            return std::variant<Instruction, std::string> { whm };
          } 
        );
      }
    };

    /** Class for the MULTIPLY instruction */
    class MatrixMultiply{
    public:
    /**
     * Register the instruction 'MULTIPLY'. This instruction requires all 3 arguments, but no flags. 
     */
      static void registerInstructions( Parser& parser ) noexcept {
        parser.addInstructionBuilder( "MULTIPLY", []( std::optional<std::string_view> flag, std::array<std::optional<u_int64_t>, 3> args){
            ERROR_IF_FLAG( flag )
            Instruction mm;
            mm.setOpcode( OPCODES::MM );
            if ( args[0].has_value() ){
              mm.setLength( args[0].value() );
            } else {
              return std::variant<Instruction, std::string>{ std::string("Read Host Memory requires the Length argument") };
            }
            if ( args[1].has_value() ){
              mm.setHostAddress( args[1].value() );
            } else {
              return std::variant<Instruction, std::string>{ std::string("Read Host Memory requires the Host Memory Address argument") };
            }
            if ( args[2].has_value() ){
              mm.setLocalAddress( args[2].value() );
            } else {
              return std::variant<Instruction, std::string>{ std::string("Read Host Memory requires the Local Memory Address argument") };
            }
            return std::variant<Instruction, std::string> { mm };
          } 
        );
      }
    };

    /** Class for the ACTIVATE instruction */
    class Activate{
    public:
    /**
     * Register the instruction 'ACTIVATE'. This instruction requires all 3 arguments, and a flag (opions are RELU, SIGMOID). 
     */
      static void registerInstructions( Parser& parser ) noexcept {
        parser.addInstructionBuilder( "ACTIVATE", []( std::optional<std::string_view> flag, std::array<std::optional<u_int64_t>, 3> args){
            Instruction act;
            act.setOpcode( OPCODES::ACT );
            if ( !flag.has_value() ){
              return std::variant<Instruction, std::string>{ std::string("Activate requires a flag that can be 'RELU' or 'SIGMOID'") };
            } else {
              if ( strcmp(flag.value().data(), "RELU") ){ act.setFlag( 0 ); }
              else if ( strcmp(flag.value().data(), "SIGMOID") ){ act.setFlag( 1 ); }
              else { return std::variant<Instruction, std::string>{ std::string("Activate requires a flag that can be 'RELU' or 'SIGMOID'") }; }
            }
            if ( args[0].has_value() ){
              act.setLength( args[0].value() );
            } else {
              return std::variant<Instruction, std::string>{ std::string("Read Host Memory requires the Length argument") };
            }
            if ( args[1].has_value() ){
              act.setHostAddress( args[1].value() );
            } else {
              return std::variant<Instruction, std::string>{ std::string("Read Host Memory requires the Host Memory Address argument") };
            }
            if ( args[2].has_value() ){
              act.setLocalAddress( args[2].value() );
            } else {
              return std::variant<Instruction, std::string>{ std::string("Read Host Memory requires the Local Memory Address argument") };
            }
            return std::variant<Instruction, std::string> { act };
          } 
        );
      }
    };

    using BaseInstructionSet = UnionInstructionSet<NopInstruction, HaltInstruction, ReadHostMemory, WriteHostMemory, MatrixMultiply, Activate>;
  
  }
}

#undef ERROR_IF_FLAG
#undef ERROR_IF_ARGS