#include "instructions.hpp"

namespace gemma {
  std::ostream& fmt_instruction_bin( std::ostream &o, GemmaInstruction &instruction){
    #define PRINT( SIZE, func, COUNTER) o  << instruction.func();

      PRINT( OPCODE_SIZE, getOpcode, 0 )
      PRINT( FLAG_SIZE, getFlag, 1 )
      PRINT( LENGTH_SIZE, getLength, 2 )
      PRINT( HOST_ADDRESS_SIZE, getHostAddress, 3 )
      PRINT( LOCAL_ADDRESS_SIZE, getLocalAddress, 4 )

      #undef PRINT
      return o;
  }

  std::ostream& fmt_instruction_raw( std::ostream &o, GemmaInstruction &instruction){
    #define PRINT( SIZE, func, COUNTER)                                                                \
        std::bitset<SIZE> mask##COUNTER{ 0xff };  \
        std::bitset<SIZE> data##COUNTER = instruction.func(); \
        /* when i reaches -1 it got interpreted as size_t::MAX so checking i > -1 is the same as i != size_t::MAX */ \
        for( size_t i = (SIZE / 8) - 1; i != SIZE_MAX; i-- ){ \
          o << (char)((data##COUNTER & (mask##COUNTER << (i * 8))) >> (i * 8)).to_ulong(); \
        }

      PRINT( OPCODE_SIZE, getOpcode, 0 )
      PRINT( FLAG_SIZE, getFlag, 1 )
      PRINT( LENGTH_SIZE, getLength, 2 )
      PRINT( HOST_ADDRESS_SIZE, getHostAddress, 3 )
      PRINT( LOCAL_ADDRESS_SIZE, getLocalAddress, 4 )

      #undef PRINT
      return o;
  }

  std::ostream& fmt_instruction_hex( std::ostream &o, GemmaInstruction &instruction){
    #define PRINT( SIZE, func, COUNTER)                                                                \
        std::bitset<SIZE> mask##COUNTER{ 0xff };  \
        std::bitset<SIZE> data##COUNTER = instruction.func(); \
        /* when i reaches -1 it got interpreted as size_t::MAX so checking i > -1 is the same as i != size_t::MAX */ \
        for( size_t i = (SIZE / 8) - 1; i != SIZE_MAX; i-- ){ \
          o <<  std::hex << (unsigned int)((data##COUNTER & (mask##COUNTER << (i * 8))) >> (i * 8)).to_ulong(); \
        }

      PRINT( OPCODE_SIZE, getOpcode, 0 )
      PRINT( FLAG_SIZE, getFlag, 1 )
      PRINT( LENGTH_SIZE, getLength, 2 )
      PRINT( HOST_ADDRESS_SIZE, getHostAddress, 3 )
      PRINT( LOCAL_ADDRESS_SIZE, getLocalAddress, 4 )

      #undef PRINT
      return o;
  }
}