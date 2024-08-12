#pragma once

namespace gemma {
  const unsigned int OPCODE_SIZE = 8;
  
  /**
   * Each instruction must have a unique opcode.
   * The opcode field is 8 bit long but only 5 are used to allow extensions and custom instructions in future 
   */
  enum OPCODES {
    NOP =  0x00,
    HALT = 0x01,
    RHM =  0x02,
    WHM =  0x04,
    MM =   0x08,
    ACT =  0x10,
  };
}