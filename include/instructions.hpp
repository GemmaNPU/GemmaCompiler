#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#define BYTE( bits ) (bits * 8)
#define GETTER( ty, name, prop ) ty get##name(){ return this->prop; };
#define SETTER( ty, name, prop ) GemmaInstruction &set##name( ty value ){ this->prop = value; return *this; };
#define OPCODE_SIZE        BYTE(1)
#define FLAG_SIZE          BYTE(1)
#define LENGTH_SIZE        BYTE(1)
#define HOST_ADDRESS_SIZE  BYTE(8)
#define LOCAL_ADDRESS_SIZE BYTE(3)

/**
 * @{ \name Instruction opcodes.
 */
/**
 * \brief These macros define the opcodes of the GemmaISA.
 *
 * The list of instructions can be fiund here: https://example.com
 */
#define NOP_OPCODE 0
#define RHM_OPCODE 1 
#define WHM_OPCODE 2
#define MM_OPCODE  4
#define ACT_OPCODE 8
#define CON_OPCODE 16
#define SYN_OPCODE 32
#define HLT_OPCODE 64
/**
 * @}
 */

#include <bitset>
#include <iostream>
#include <iomanip>

namespace gemma {

  using opcode_t        = std::bitset<OPCODE_SIZE>;
  using flag_t          = std::bitset<FLAG_SIZE>;
  using length_t        = std::bitset<LENGTH_SIZE>;
  using host_address_t  = std::bitset<HOST_ADDRESS_SIZE>;
  using local_address_t = std::bitset<LOCAL_ADDRESS_SIZE>;

/**
 * \brief Utility class to generate instructions
 * 
 */
  class GemmaInstruction {
    opcode_t opcode;
    flag_t flag;
    length_t length;
    host_address_t host_address;
    local_address_t local_address;
  public:

    GemmaInstruction( opcode_t _opcode, flag_t _flag, length_t _length,
                      host_address_t _host_address, local_address_t _local_address ) 
      : opcode( _opcode ), flag( _flag ), length( _length ), 
        host_address( _host_address ), local_address( _local_address ) {};
    GemmaInstruction() = default;

    GETTER( opcode_t, Opcode, opcode)
    SETTER( opcode_t, Opcode, opcode)

    GETTER( flag_t, Flag, flag)
    SETTER( flag_t, Flag, flag)

    GETTER( length_t, Length, length)
    SETTER( length_t, Length, length)

    GETTER( host_address_t, HostAddress, host_address)
    SETTER( host_address_t, HostAddress, host_address)

    GETTER( local_address_t, LocalAddress, local_address)
    SETTER( local_address_t, LocalAddress, local_address)

  };

  std::ostream& fmt_instruction_raw( std::ostream&, GemmaInstruction&);
  std::ostream& fmt_instruction_hex( std::ostream&, GemmaInstruction&);
  std::ostream& fmt_instruction_bin( std::ostream&, GemmaInstruction&);
}

#endif