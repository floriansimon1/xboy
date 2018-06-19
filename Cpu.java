state = State.OPCODE;
operandIndex = 0;
interruptManager.onInstructionFinished();
int operando = operand[0] | (operand[1] << 8);
if (pc > 0x100) {
    System.out.printf("PC: %02X, AF: %02X, BC: %02X, DE: %02X, HL: %02X, SP: %02X, (SP): %02X%02X, (HL): %02X%02X, ($d600): %02X - %s\n",
        registers.getPC(),
        registers.getAF(),
        registers.getBC(),
        registers.getDE(),
        registers.getHL(),
        registers.getSP(),
        addressSpace.getByte(registers.getSP() + 1),
        addressSpace.getByte(registers.getSP()),
        registers.getHL() < 65535 ? addressSpace.getByte(registers.getHL() + 1) : 0,
        registers.getHL() < 65536 ? addressSpace.getByte(registers.getHL()) : 0,
        addressSpace.getByte(0xd600),
        currentOpcode.toString()
    );
}
return;
