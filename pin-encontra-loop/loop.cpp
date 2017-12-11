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

string ADDRINTToHexString(ADDRINT a)
{
    ostringstream temp;
    temp << "0x" << hex <<a;
    return temp.str();
}

void Routine(RTN rtn, VOID *v) {

  RTN_Open(rtn);
  for (INS ins = RTN_InsHead(rtn); INS_Valid(ins); ins = INS_Next(ins)) {

    INS loop_start = GetLoopStart(ins);
    if (loop_start != ins) {

      std::vector<INS> loop_predicate;
      std::vector<INS> loop_body;
      std::vector<INS> loop_condition;

      INS x;
      for (x = loop_start; INS_Valid(x) && !INS_IsBranch(x); x = INS_Next(x)) {
        TraceFile << std::hex << INS_Address(x) << ": ";
        TraceFile << INS_Disassemble(x) << endl;
      }

      ADDRINT jmp_addr = INS_DirectBranchOrCallTargetAddress(x);
      TraceFile << ADDRINTToHexString(jmp_addr);
      
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
