#pragma once

#include <string>
#include <bitset>

namespace gemma {
  const unsigned int FLAG_SIZE = 8;

  /**
   * This is is an abstraction over the string attribute of the isntructions. 
   * Once a flag is build it's no longer possible to edit
   */
  class Flag {
    
    /**
     * A string associated to the flag
     */
    std::string m_name;

    /**
     * The value of the flag
     */
    std::bitset<FLAG_SIZE> m_value;
  public:
    /** 
     * Build a flag specifying the name and the value
     */
    Flag( std::string& name, std::bitset<FLAG_SIZE> value): m_name{ std::move(name) }, m_value{ value } {}

    /**
     * Get the name used as an identifier for the flag
     * 
     * @returns the string with the name associated to the flag
     */
    [[ nodiscard ]] std::string const getName() const noexcept { return m_name; }

    /**
     * Get the value of the flag
     * 
     * @returns the value of the flag
     */
    [[ nodiscard ]] std::bitset<FLAG_SIZE> const getValue() const noexcept { return m_value; }
  };
}