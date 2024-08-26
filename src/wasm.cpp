#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif
#define export __attribute__((visibility("default")))

#include <string>
#include <sstream>
#include "assembler/scanner.hpp"
#include "assembler/instructions/instructions_set.hpp"
#include "assembler/instructions/nop.hpp"
#include "assembler/instructions/halt.hpp"
#include "assembler/formatters/human_hex_formatter.hpp"

static std::string assembler_result;
static std::string assembler_error;

extern "C" 
{
    EMSCRIPTEN_KEEPALIVE export const char* assemble_line(char* instructions)
    {
        std::string input{ instructions };
        std::stringstream ss;
        gemma::assembler::Scanner<gemma::assembler::InstructionSet<gemma::assembler::NOP, gemma::assembler::HALT>> scanner{ input };
        gemma::assembler::HumanHexInstructionFormatter formatter{ ss };
        auto result = scanner.getNextInstruction();
        if ( result.index() == 0 ){
            assembler_error = "";
            auto instruction = std::get<0>( result );
            if ( instruction.has_value() ){
                formatter.format( instruction.value() );
            }
            assembler_result = ss.str();
            return assembler_result.c_str();
        } else {
            assembler_error = std::get<1>( result );
            assembler_result = "";
            return assembler_result.c_str();
        }

    }

    EMSCRIPTEN_KEEPALIVE export const char* error()
    {
        return assembler_error.c_str();
    }
}