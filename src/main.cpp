#include <iostream>
#include <argparse/argparse.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <streambuf>

#include "assembler/assembler.hpp"
#include "instructions/opcodes.hpp"
#include "instructions/instruction.hpp"
#include "instructions/flag.hpp"

int main( int argc, char *argv[] ){
  argparse::ArgumentParser program("gemmas");
  program.set_prefix_chars("-+/");

  program.add_argument("-o")
    .default_value(std::string("ga.out"));
  program.add_argument("-v")
    .default_value(false);
  program.add_argument("files")
    .remaining();

  try {
    program.parse_args(argc, argv);
  }
  catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  std::string output_file_name = program.get("-o");
  auto input_files = program.get<std::vector<std::string>>("files");

  std::string input_string;
  for( auto &input_file: input_files){
    std::ifstream t(input_file);
    std::string str((std::istreambuf_iterator<char>(t)),
                  std::istreambuf_iterator<char>());
    input_string.append( str );
  }

  std::ofstream output_file{ output_file_name, std::ios::binary };

  auto lexer = gemma::assembler::Lexer{ input_string.c_str() };
  auto parser = gemma::assembler::Parser{ lexer };
  auto assembler = gemma::assembler::Assembler{ parser };
  assembler.loadInstructionSet<gemma::assembler::BaseInstructionSet>();
  
  auto instructions = assembler.assemble();
  if ( instructions.index() == 1 ){
    std::string error = std::get<std::string>( instructions );
    std::cout << error << std::endl;
    exit( 1 );
  }
  for( auto &i: std::get<0>(instructions) ){
    for( size_t j = ( gemma::OPCODE_SIZE / 8) - 1; j != SIZE_MAX; j-- ){
      output_file << (char)((i.getOpcode() & ( std::bitset<gemma::OPCODE_SIZE>{ 0xff } << (j * 8))) >> (j * 8)).to_ulong();
    }
    for( size_t j = ( gemma::FLAG_SIZE / 8) - 1; j != SIZE_MAX; j-- ){
      output_file << (char)((i.getFlag() & ( std::bitset<gemma::FLAG_SIZE>{ 0xff } << (j * 8))) >> (j * 8)).to_ulong();
    }
    for( size_t j = ( gemma::LENGTH_SIZE / 8) - 1; j != SIZE_MAX; j-- ){
      output_file << (char)((i.getLength() & ( std::bitset<gemma::LENGTH_SIZE>{ 0xff } << (j * 8))) >> (j * 8)).to_ulong();
    }
    for( size_t j = ( gemma::HOST_ADDRESS_SIZE / 8) - 1; j != SIZE_MAX; j-- ){
      output_file << (char)((i.getHostAddress() & ( std::bitset<gemma::HOST_ADDRESS_SIZE>{ 0xff } << (j * 8))) >> (j * 8)).to_ulong();
    }
    for( size_t j = ( gemma::LOCAL_ADDRESS_SIZE / 8) - 1; j != SIZE_MAX; j-- ){
      output_file << (char)((i.getLocalAddress() & ( std::bitset<gemma::LOCAL_ADDRESS_SIZE>{ 0xff } << (j * 8))) >> (j * 8)).to_ulong();
    }
  }


  return 0;
}