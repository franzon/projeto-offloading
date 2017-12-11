#include "pin.H"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::ofstream TraceFile;

/* marcação loop

{
  asm("nop \n\
      movl %eax, %eax \n\
        nop \n\
        movl %eax, %eax \n\
        nop \n\
");
}
*/

INS GetLoopStart(INS ins) {
  if (INS_Valid(ins) && INS_IsNop(ins)) {
    INS i1 = INS_Next(ins);
    if (INS_Valid(i1) && INS_IsMov(i1)) {
      INS i2 = INS_Next(i1);
      if (INS_Valid(i2) && INS_IsNop(i2)) {
        INS i3 = INS_Next(i2);
        if (INS_Valid(i3) && INS_IsMov(i3)) {
          INS i4 = INS_Next(i3);
          if (INS_Valid(i4) && INS_IsNop(i4)) {

            return INS_Next(i4);
          }
        }
      }
    }
  }
  return ins;
}

void Routine(RTN rtn, VOID *v) {

  RTN_Open(rtn);
  if ((RTN_Name(rtn).compare("__loop")) == 0) {

    RTN_Close(rtn);
    return;
  }

  for (INS ins = RTN_InsHead(rtn); INS_Valid(ins); ins = INS_Next(ins)) {

    INS loop_start = GetLoopStart(ins);
    if (loop_start != ins) {

      std::vector<INS> loop_predicate;
      std::vector<INS> loop_body;
      std::vector<INS> loop_condition;

      INS x;
      for (x = loop_start; INS_Valid(x) && !INS_IsBranch(x); x = INS_Next(x)) {
        loop_predicate.push_back(x);
      }
      loop_predicate.push_back(x);

      ADDRINT jmp_addr = INS_DirectBranchOrCallTargetAddress(x);

      for (x = INS_Next(x); INS_Valid(x) && INS_Address(x) != jmp_addr;
           x = INS_Next(x)) {
        loop_body.push_back(x);
      }

      for (; INS_Valid(x) && !INS_IsBranch(x); x = INS_Next(x)) {
        loop_condition.push_back(x);
      }
      loop_condition.push_back(x);

      TraceFile << "[Predicate]" << endl;
      for (std::vector<INS>::iterator it = loop_predicate.begin();
           it != loop_predicate.end(); ++it) {
        TraceFile << std::hex << INS_Address(*it) << ": ";
        TraceFile << INS_Disassemble(*it) << endl;
      }

      TraceFile << "[Body]" << endl;
      for (std::vector<INS>::iterator it = loop_body.begin();
           it != loop_body.end(); ++it) {
        TraceFile << std::hex << INS_Address(*it) << ": ";
        TraceFile << INS_Disassemble(*it) << endl;
      }

      TraceFile << "[Condition]" << endl;
      for (std::vector<INS>::iterator it = loop_condition.begin();
           it != loop_condition.end(); ++it) {
        TraceFile << std::hex << INS_Address(*it) << ": ";
        TraceFile << INS_Disassemble(*it) << endl;
      }

      TraceFile << endl;
    }
  }
  RTN_Close(rtn);
}

VOID Fini(INT32 code, VOID *v) { TraceFile.close(); }

int main(int argc, char *argv[]) {
  PIN_InitSymbols();
  PIN_Init(argc, argv);

  TraceFile.open("bb.out");

  RTN_AddInstrumentFunction(Routine, 0);
  PIN_AddFiniFunction(Fini, 0);

  PIN_StartProgram();

  return 0;
}
