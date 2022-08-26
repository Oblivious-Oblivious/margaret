describe Opcode do
    it "counts opcodes" do
        expect(
            Opcode::STACK_CODES.size +
            Opcode::JUMP_CODES.size +
            Opcode::SEND_CODES.size
        ).to eq 21;
    end

    it "should contain a maximum of 256 opcodes" do
        expect(
            Opcode::STACK_CODES.size +
            Opcode::JUMP_CODES.size +
            Opcode::SEND_CODES.size
        ).to be <= 256;
    end
end
