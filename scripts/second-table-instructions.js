#!/usr/bin/node

const instructions = ['GetBit', 'Clear', 'Set'];

const baseOpcode = 0x40;

const makeSharedParameters = [
  "&Cpu::bc, false",
  "&Cpu::bc, true",
  "&Cpu::de, false",
  "&Cpu::de, true",
  "&Cpu::hl, false",
  "&Cpu::hl, true",
  "",
  "&Cpu::af, false"
];

instructions.forEach((baseInstruction, i) => {
  const instructionBaseOpcode = baseOpcode + i * 0x40;

  for (let i = 0; i < 4; i++) {
    for (let j = 0; j < 16; j++) {
      const bit    = i * 2 + (j >= 8 ? 1 : 0);
      const opcode = instructionBaseOpcode + i * 16 + j;

      const assignee = `twoBytesOpcodes[0x${opcode.toString(16)}]`;

      const instruction = (
        j === 6 || j === 0xe
        ? `RegisterInstructionOnDereferencedHl<${baseInstruction}<${bit}>>`
        : `${baseInstruction}<${bit}>`
      );

      console.log(`  ${assignee} = std::make_shared<${instruction}>(${makeSharedParameters[j % 8]});`)
    }

    console.log();
  }
});
