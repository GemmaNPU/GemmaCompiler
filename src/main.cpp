#include <iostream>
#include <argparse/argparse.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <streambuf>
#include "assembler/assembler.hpp"
#include "instructions.hpp"

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

  try {
    auto instructions = parser.parse();
    for( auto &i: instructions ){
      gemma::fmt_instruction_raw( output_file, i);
    }
  } catch (...) {
    std::cout << "An expected error occurred" << std::endl;
    return 2;
  }

  return 0;
}