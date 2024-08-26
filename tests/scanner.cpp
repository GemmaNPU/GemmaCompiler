#include <gtest/gtest.h>
#include <string>

#include "assembler/scanner.hpp"
#include "assembler/instructions/instructions_set.hpp"
#include "assembler/instructions/nop.hpp"

TEST(ScannerTest, EmptyString){
  std::string program = "";
  
  gemma::assembler::Scanner<gemma::assembler::InstructionSet<>> scanner( program );
  ASSERT_FALSE(std::get<0>( scanner.getNextInstruction() ).has_value());
  ASSERT_FALSE(std::get<0>( scanner.getNextInstruction() ).has_value());
}

TEST(ScannerTest, EmptyStringMultiLine){
  std::string program = "\n\n\n";
  
  gemma::assembler::Scanner<gemma::assembler::InstructionSet<>> scanner( program );
  ASSERT_FALSE(std::get<0>( scanner.getNextInstruction() ).has_value());
  ASSERT_FALSE(std::get<0>( scanner.getNextInstruction() ).has_value());
}

TEST(ScannerTest, SingleComment){
  std::string program = "; hello";
  
  gemma::assembler::Scanner<gemma::assembler::InstructionSet<>> scanner( program );
  ASSERT_FALSE(std::get<0>( scanner.getNextInstruction() ).has_value());
  ASSERT_FALSE(std::get<0>( scanner.getNextInstruction() ).has_value());
}

TEST(ScannerTest, MultipleComments){
  std::string program = "; hello\n; world";
  
  gemma::assembler::Scanner<gemma::assembler::InstructionSet<>> scanner( program );
  ASSERT_FALSE(std::get<0>( scanner.getNextInstruction() ).has_value());
  ASSERT_FALSE(std::get<0>( scanner.getNextInstruction() ).has_value());
}

TEST(ScannerTest, SingleInstruction){
  std::string program = "NOP";
  
  gemma::assembler::Scanner<gemma::assembler::InstructionSet<gemma::assembler::NOP>> scanner( program );
  ASSERT_TRUE(std::get<0>( scanner.getNextInstruction() ).has_value());
  ASSERT_FALSE(std::get<0>( scanner.getNextInstruction() ).has_value());
}

TEST(ScannerTest, SingleInstructionWithComment){
  std::string program = "NOP ; comment";
  
  gemma::assembler::Scanner<gemma::assembler::InstructionSet<gemma::assembler::NOP>> scanner( program );
  ASSERT_TRUE(std::get<0>( scanner.getNextInstruction() ).has_value());
  ASSERT_FALSE(std::get<0>( scanner.getNextInstruction() ).has_value());
}

TEST(ScannerTest, SingleInstructionWithEmptyInstructionSet){
  std::string program = "NOP";
  
  gemma::assembler::Scanner<gemma::assembler::InstructionSet<>> scanner( program );
  ASSERT_NO_THROW(std::get<1>( scanner.getNextInstruction() ) );
  ASSERT_FALSE(std::get<0>( scanner.getNextInstruction() ).has_value());
}

TEST(ScannerTest, MultipleInstructions){
  std::string program = "NOP\nNOP\nNOP";
  
  gemma::assembler::Scanner<gemma::assembler::InstructionSet<gemma::assembler::NOP>> scanner( program );
  ASSERT_TRUE(std::get<0>( scanner.getNextInstruction() ).has_value());
  ASSERT_TRUE(std::get<0>( scanner.getNextInstruction() ).has_value());
  ASSERT_TRUE(std::get<0>( scanner.getNextInstruction() ).has_value());
  ASSERT_FALSE(std::get<0>( scanner.getNextInstruction() ).has_value());
}

TEST(ScannerTest, MultipleInstructionsWithComments){
  std::string program = "NOP ; comment\nNOP; another\nNOP";
  
  gemma::assembler::Scanner<gemma::assembler::InstructionSet<gemma::assembler::NOP>> scanner( program );
  ASSERT_TRUE(std::get<0>( scanner.getNextInstruction() ).has_value());
  ASSERT_TRUE(std::get<0>( scanner.getNextInstruction() ).has_value());
  ASSERT_TRUE(std::get<0>( scanner.getNextInstruction() ).has_value());
  ASSERT_FALSE(std::get<0>( scanner.getNextInstruction() ).has_value());
}