#include <iostream>
#include <argparse/argparse.hpp>
#include "assembler/assembler.hpp"
#include "assembler/scanner.hpp"
#include "assembler/formatters/human_hex_formatter.hpp"
#include "assembler/instructions/instructions_set.hpp"
#include "assembler/instructions/nop.hpp"
#include "assembler/instructions/halt.hpp"

int main(){

  argparse::ArgumentParser program("gemmas");
  program.set_prefix_chars("-+/");
  program.add_argument("-i")
    .help("Run the assembler in interactive mode")
    .default_value(false);


  gemma::assembler::Assembler assembler;
  using ISA = gemma::assembler::InstructionSet<gemma::assembler::NOP, gemma::assembler::HALT>;
  assembler.interactive< gemma::assembler::Scanner<ISA>, gemma::assembler::HumanHexInstructionFormatter >( std::cin, std::cout );

  return 0;
}