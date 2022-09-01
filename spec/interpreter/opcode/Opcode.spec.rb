describe Opcode do
    it "counts runtime opcodes" do
        expect(
            Opcode::STACK_CODES.size +
            Opcode::JUMP_CODES.size +
            Opcode::SEND_CODES.size
        ).to eq 33;
    end

    it "should contain a maximum of 256 runtime opcodes" do
        expect(
            Opcode::STACK_CODES.size +
            Opcode::JUMP_CODES.size +
            Opcode::SEND_CODES.size
        ).to be <= 256;
    end

    it "counts compile time opcodes" do
        expect(Opcode::COMPILE_TIME.size).to eq 1;
    end
end
