#include "split-commit/split-commit.h"

void SplitCommit::LoadCode(uint32_t msg_bits) {
  if (msg_bits == 1) {
    // code.loadTxtFile(std::string("matrices/40-rep-code.txt")); //No code is loaded due to SplitCommit::BitEncode(uint8_t data, uint8_t check_bits[])
    parity_bytes = 5;
    cword_bytes = 5; //the value bit is included
    msg_in_cword_offset = 0;
  } else if (msg_bits == 128) {
    code.loadTxtFile(std::string("matrices/bch-128x134.txt"));
    parity_bytes = code.codewordU8Size();
    cword_bytes = code.codewordU8Size() + code.plaintextU8Size();
    msg_in_cword_offset = code.plaintextU8Size();
  } else {
    throw std::runtime_error("Message size not supported at this time");
  }

  this->msg_bits = msg_bits;
  msg_bytes = BITS_TO_BYTES(msg_bits);
  cword_bits = cword_bytes * CHAR_BIT;
  parity_bits = parity_bytes * CHAR_BIT;
}

void SplitCommit::BitEncode(uint8_t data, uint8_t check_bits[]) {
  std::fill(check_bits, check_bits + cword_bytes, BIT_TO_BYTE[data]);
}