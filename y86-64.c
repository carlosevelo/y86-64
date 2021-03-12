#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

const int MAX_MEM_SIZE  = (1 << 13);

void fetchStage(int *icode, int *ifun, int *rA, int *rB, wordType *valC, wordType *valP) {
  //Series of if statements (icode)
  byteType mask = 0x0f;
  byteType pcByte = getByteFromMemory(getPC());
  *icode = pcByte >> 4;

  if (*icode == HALT) { //Halt 1 byte
    setStatus(STAT_HLT);
    return;
  }
  else if (*icode == NOP) { //No op 1 byte
    *valP = getPC() + 1;

  }
  else if (*icode == RRMOVQ) { //rrmovq 2 bytes
    pcByte = getByteFromMemory(getPC() + 1);
    *rA = pcByte >> 4;
    *rB = pcByte & mask;
    *valP = getPC() + 2;
    return;
  }
  else if (*icode == IRMOVQ) { //irmovq 10 bytes
    pcByte = getByteFromMemory(getPC() + 1);
    *rA = pcByte >> 4;
    *rB = pcByte & mask;
    *valC = getWordFromMemory(getPC() + 2);
    *valP = getPC() + 10;
    return;
  }
  else if (*icode == RMMOVQ) { //rmmovq 10 bytes
    pcByte = getByteFromMemory(getPC() + 1);
    *rA = pcByte >> 4;
    *rB = pcByte & mask;
    *valC = getWordFromMemory(getPC() + 2);
    *valP = getPC() + 10;
    return;
  }
  else if (*icode == MRMOVQ) { //mrmovq 10 bytes
    *valP = getPC() + 10;

  }
  else if (*icode == OPQ) { //int op 2 bytes
    *ifun = pcByte & mask;
    pcByte = getByteFromMemory(getPC() + 1);
    *rA = pcByte >> 4;
    *rB = pcByte & mask;
    *valP = getPC() + 2;
    return;
  }
  else if (*icode == JXX) { //jump 9 bytes
    *valP = getPC() + 9;
    *ifun = pcByte & mask;

  }
  else if (*icode == CALL) { //call 9 bytes
    *valP = getPC() + 9;

  }
  else if (*icode == RET) { //ret 1 byte
    *valP = getPC() + 1;

  }
  else if (*icode == PUSHQ) { //pushq 2 bytes
    *valP = getPC() + 2;

  }
  else if (*icode == POPQ) { //popq 2 bytes
    *valP = getPC() + 2;

  }
}

void decodeStage(int icode, int rA, int rB, wordType *valA, wordType *valB) {
  if (icode == HALT) { //Halt
    return;
  }
  else if (icode == NOP) { //No op
    return;
  }
  else if (icode == RRMOVQ) { //rrmovq
    *valA = getRegister(rA);
    return;
  }
  else if (icode == IRMOVQ) { //irmovq
    return;
  }
  else if (icode == RMMOVQ) { //rmmovq
    *valA = getRegister(rA);
    *valB = getRegister(rB);
    return;
  }
  else if (icode == MRMOVQ) { //mrmovq
    
  }
  else if (icode == OPQ) { //int op
    *valA = getRegister(rA);
    *valB = getRegister(rB);
    return;
  }
  else if (icode == JXX) { //jump
    
  }
  else if (icode == CALL) { //call
    
  }
  else if (icode == RET) { //ret
    
  }
  else if (icode == PUSHQ) { //pushq
    
  }
  else if (icode == POPQ) { //popq
    
  }
}

void executeStage(int icode, int ifun, wordType valA, wordType valB, wordType valC, wordType *valE, bool *Cnd) {
  if (icode == HALT) { //Halt
    return;
  }
  else if (icode == NOP) { //No op
    return;
  }
  else if (icode == RRMOVQ) { //rrmovq
    *valE = 0 + valA;
    return;
  }
  else if (icode == IRMOVQ) { //irmovq
    *valE = 0 + valC;
    return;
  }
  else if (icode == RMMOVQ) { //rmmovq
    *valE = valB + valC;
    return;
  }
  else if (icode == MRMOVQ) { //mrmovq
    
  }
  else if (icode == OPQ) { //int op
    if (ifun == ADD) {
      *valE = valB + valA;
    }
    else if (ifun == SUB) {
      *valE = valB - valA;
    }
    else if (ifun == XOR) {
      *valE = valB ^ valA;
    }
    else if (ifun == AND) {
      *valE = valB & valA;
    }
    //Set CC?
  }
  else if (icode == JXX) { //jump
    
  }
  else if (icode == CALL) { //call
    
  }
  else if (icode == RET) { //ret
    
  }
  else if (icode == PUSHQ) { //pushq
    
  }
  else if (icode == POPQ) { //popq
    
  }
}

void memoryStage(int icode, wordType valA, wordType valP, wordType valE, wordType *valM) {
  if (icode == HALT) { //Halt
    return;
  }
  else if (icode == NOP) { //No op
    return;
  }
  else if (icode == RRMOVQ) { //rrmovq
    return;
  }
  else if (icode == IRMOVQ) { //irmovq
    return;
  }
  else if (icode == RMMOVQ) { //rmmovq
    setWordInMemory(valE, valA);
    return;
  }
  else if (icode == MRMOVQ) { //mrmovq
    
  }
  else if (icode == OPQ) { //int op
    return;
  }
  else if (icode == JXX) { //jump
    
  }
  else if (icode == CALL) { //call
    
  }
  else if (icode == RET) { //ret
    
  }
  else if (icode == PUSHQ) { //pushq
    
  }
  else if (icode == POPQ) { //popq
    
  }
}

void writebackStage(int icode, wordType rA, wordType rB, wordType valE, wordType valM) {
  if (icode == HALT) { //Halt
    return;
  }
  else if (icode == NOP) { //No op
    return; 
  }
  else if (icode == RRMOVQ) { //rrmovq
    setRegister(rB, valE);
    return;
  }
  else if (icode == IRMOVQ) { //irmovq
    setRegister(rB, valE);
    return;
  }
  else if (icode == RMMOVQ) { //rmmovq
    return;
  }
  else if (icode == MRMOVQ) { //mrmovq
    
  }
  else if (icode == OPQ) { //int op
    setRegister(rB, valE);
    return;
  }
  else if (icode == JXX) { //jump
    
  }
  else if (icode == CALL) { //call
    
  }
  else if (icode == RET) { //ret
    
  }
  else if (icode == PUSHQ) { //pushq
    
  }
  else if (icode == POPQ) { //popq
    
  }
}

void pcUpdateStage(int icode, wordType valC, wordType valP, bool Cnd, wordType valM) {
  if (icode == HALT) { //Halt
    return;
  }
  else if (icode == NOP) { //No op
    setPC(valP);
    return;
  }
  else if (icode == RRMOVQ) { //rrmovq
    setPC(valP);
    return;
  }
  else if (icode == IRMOVQ) { //irmovq
    setPC(valP);
    return;
  }
  else if (icode == RMMOVQ) { //rmmovq
    setPC(valP);
  }
  else if (icode == MRMOVQ) { //mrmovq
    setPC(valP);
  }
  else if (icode == OPQ) { //int op
    setPC(valP);
    return;
  }
  else if (icode == JXX) { //jump
    
  }
  else if (icode == CALL) { //call
    setPC(valC);
  }
  else if (icode == RET) { //ret
    setPC(valM);
  }
  else if (icode == PUSHQ) { //pushq
    setPC(valP);
  }
  else if (icode == POPQ) { //popq
    setPC(valP);
  }
}

void stepMachine(int stepMode) {
  /* FETCH STAGE */
  int icode = 0, ifun = 0; //intruction type
  int rA = 0, rB = 0; //instruction registers
  wordType valC = 0; //instruction value
  wordType valP = 0; //next intruction address
 
  /* DECODE STAGE */
  wordType valA = 0; //value from register A
  wordType valB = 0; //value from register B

  /* EXECUTE STAGE */
  wordType valE = 0; //Resulting value
  bool Cnd = 0; //Condition

  /* MEMORY STAGE */
  wordType valM = 0; //Value read from memory

  fetchStage(&icode, &ifun, &rA, &rB, &valC, &valP);
  applyStageStepMode(stepMode, "Fetch", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);

  decodeStage(icode, rA, rB, &valA, &valB);
  applyStageStepMode(stepMode, "Decode", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  executeStage(icode, ifun, valA, valB, valC, &valE, &Cnd);
  applyStageStepMode(stepMode, "Execute", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  memoryStage(icode, valA, valP, valE, &valM);
  applyStageStepMode(stepMode, "Memory", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  writebackStage(icode, rA, rB, valE, valM);
  applyStageStepMode(stepMode, "Writeback", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  pcUpdateStage(icode, valC, valP, Cnd, valM);
  applyStageStepMode(stepMode, "PC update", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);

  incrementCycleCounter();
}

/** 
 * main
 * */
int main(int argc, char **argv) {
  int stepMode = 0;
  FILE *input = parseCommandLine(argc, argv, &stepMode);

  initializeMemory(MAX_MEM_SIZE);
  initializeRegisters();
  loadMemory(input);

  applyStepMode(stepMode);
  while (getStatus() != STAT_HLT) {
    stepMachine(stepMode);
    applyStepMode(stepMode);
#ifdef DEBUG
    printMachineState();
    printf("\n");
#endif
  }
  printMachineState();
  return 0;
}