# Gemma Assembler
This is just an alpha version of a compiler for the GemmaTPU project

# Contributing
See [Contributing file](CONTRIBUTING.md)

# ISA 
The assembly format for most instructions (RHM, WHM, MMC, ACT) is
    INSTRUCTION SRC, DEST, LENGTH 
For RW, it is
    RW SRC
for HLT, it is
    HLT

=== Binary Encoding ====

| opcode | flags | length | addr | ub addr |
|   1    |   1   |   1    |  8   |    3    |
|13    13|12   12|11    11|10   3|2       0|

All numbers above are expressed in BYTES.
The 'addr' field is used for host memory address (for RHM and WHM),
weight DRAM address (for RW), and accumulator address (for MMC and ACT).
For the later two, the field is larger than necessary, and only the lower bits are used.
'ub addr' is always a Unified Buffer address.
'length' is the number of vectors to read/write/process.

FLAG field is r|r|f|f|f|o|s|c, r stands for reserved bit, s for switch bit,
c for convolve bit, f for function select bits, and o for override bit.

No Op               NOP
Read_Host_Memory    RHM
MatrixMultiply      MM
Activate            ACT
Write_Host_Memory   WHM
Set_Config          CON
Sync                SYN
Halt                HLT



Instruction has the following format:
    INST: OP, SRC, TAR, LEN (or FUNC), FLAG
    LENGTH: 1B, VAR, VAR, 1B, 1B

OPCODE may define flags by using dot (.) separator following
opcode string.

For ACT instruction, function byte is defined using the following
mapping:
    0x0 -> ReLU
    0x1 -> Sigmoid
    0x2 -> MaxPooling

Comments start with #.

EXAMPLES:
    # example program
    RHM 1, 2, 3 # first instruction
    WHM 1, 2, 3
    RW 0xab
    MMC 100, 2, 3
    MMC.C 100, 2, 3
    ACT 0xab, 12, 1
    NOP
    HLT

===binary encoding====

INST is encoded in a little-endian format.
OPCODE values are defined in OPCODE2BIN.
FLAG field is r|r|r|r|r|o|s|c, r stands for reserved bit, s for switch bit,
c for convolve bit, and o for override bit.

SRC and TAR are addresses. They can be of variable length defined in
global dict OPCODE2BIN.

SRC/TAR takes 5B for memory operations to support at least 8GB addressing,
3B for Unified Buffer addressing (96KB), 2B for accumulator buffer addressing
(4K).
