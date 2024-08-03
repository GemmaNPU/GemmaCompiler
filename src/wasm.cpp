#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif
#define export __attribute__((visibility("default")))

#include "assembler/assembler.hpp"
#include <string>
#include <sstream>

extern "C" 
{
    EMSCRIPTEN_KEEPALIVE export const char* assemble(char* instructions)
    {
        gemma::assembler::Lexer lexer = gemma::assembler::Lexer( instructions );
        gemma::assembler::Parser parser = gemma::assembler::Parser( lexer );
        gemma::assembler::Assembler assembler = gemma::assembler::Assembler( parser );
        std::stringstream stream; 

        auto result = assembler.assemble();
        for( auto i: result ){
            gemma::fmt_instruction_hex( stream, i);
        }
        const std::string str = stream.str();
        return str.c_str();
    }
}