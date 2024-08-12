#pragma once

#include "instructions/flag.hpp"
#include "instructions/opcodes.hpp"

#include <bitset>
#include <string>
#include <vector>
#include <cstdint>

namespace gemma
{
  const unsigned int LENGTH_SIZE = 8;
  const unsigned int HOST_ADDRESS_SIZE = 64;
  const unsigned int LOCAL_ADDRESS_SIZE = 24;
  const unsigned int INSTRUCTION_SIZE = OPCODE_SIZE + FLAG_SIZE + LENGTH_SIZE + HOST_ADDRESS_SIZE + LOCAL_ADDRESS_SIZE ;

  /**
   * An abstraction over the concept of instruction for the NPU. Each instruction is made of 5 components:
   *  * The OPCODE which identifies uniquely the instruction
   *  * The FLAG that is used to specify the behavior of the instruction
   *  * The LENGTH, HOST_ADDRESS, LOCAL_ADDRESS used to manage i/o memory operations
   */
  class Instruction {
  protected:
    /**
     * The OPCODE identifies uniquely the instruction
     */
    std::bitset<OPCODE_SIZE> m_opcode;

    /**
     * The FLAG that is used to specify the behavior of the instruction
     */
    std::bitset<FLAG_SIZE> m_flag;
    
    // TODO: abstract LENGTH, HOST_ADDRESS, LOCAL_ADDRESS into a Memory class

    /**
     * The LENGTH tells how many byte should be used in the i/o operation
     */
    std::bitset<LENGTH_SIZE> m_length;

    /**
     * Indicates a position in the host memory
     */
    std::bitset<HOST_ADDRESS_SIZE> m_host_address;

    /**
     * Indicatesa position in the local memory
     */
    std::bitset<LOCAL_ADDRESS_SIZE> m_local_address;
  public:
    /**
     * Create an empty instruction
     */
    explicit Instruction() = default;
    
    /**
     * The opcode of the instruction
     */
    [[ nodiscard ]] std::bitset<OPCODE_SIZE> getOpcode() const noexcept { return m_opcode; }

    /**
     * The flag of the instruction
     */
    [[ nodiscard ]] std::bitset<FLAG_SIZE> getFlag() const noexcept { return m_flag; }

    /**
     * The length of the instruction
     */
    [[ nodiscard ]] std::bitset<LENGTH_SIZE> getLength() const noexcept { return m_length; }
    
    /**
     * The host address of the instruction
     */
    [[ nodiscard ]] std::bitset<HOST_ADDRESS_SIZE> getHostAddress() const noexcept { return m_host_address; }

    /**
     * The local address of the instruction
     */
    [[ nodiscard ]] std::bitset<LOCAL_ADDRESS_SIZE> getLocalAddress() const noexcept { return m_local_address; }

    /**
     * Set the opcode
     */
    Instruction& setOpcode( std::bitset<OPCODE_SIZE> opcode ){ m_opcode = opcode; return *this; }

    /**
     * Set the flag
     */
    Instruction& setFlag( std::bitset<FLAG_SIZE> flag ){ m_flag = flag; return *this; }

    /**
     * Set the flag
     */
    Instruction& setFlag( Flag &flag ){ m_flag = flag.getValue(); return *this; }

    /**
     * Set the length
     */
    Instruction& setLength( std::bitset<LENGTH_SIZE> length ){ m_length = length; return *this; }

    /**
     * Set the host address
     */
    Instruction& setHostAddress( std::bitset<HOST_ADDRESS_SIZE> host_address ){ m_host_address = host_address; return *this; }

    /**
     * Set the local address
     */
    Instruction& setLocalAddress( std::bitset<LOCAL_ADDRESS_SIZE> local_address ){ m_local_address = local_address; return *this; }
  };
}
