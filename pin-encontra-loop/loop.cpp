#include "pin.H"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::ofstream TraceFile;

<<<<<<< HEAD
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
=======
// todo: melhorar esse código
int isLoopSig(INS ins) {
    if (INS_IsNop(ins)) {
        INS n1 = INS_Next(ins);

        if (INS_Valid(n1)) {
            INS n2 = INS_Next(n1);
            if (INS_Valid(n2)) {
                INS n3 = INS_Next(n2);
                if (INS_Valid(n3)) {
                    if (INS_IsMov(n1) && INS_OperandCount(n1) == 2) {
                        if (INS_OperandIsReg(n1, 0) && INS_OperandIsReg(n1, 1) &&
                            INS_OperandReg(n1, 0) == INS_OperandReg(n1, 1)) {

                            if (INS_IsMov(n2) && INS_OperandCount(n2) == 2) {
                                if (INS_OperandIsReg(n2, 0) && INS_OperandIsReg(n2, 1) &&
                                    INS_OperandReg(n2, 0) == INS_OperandReg(n2, 1)) {
                                    if (INS_IsNop(n3))
                                        if (INS_Valid(INS_Next(n3)))
                                            return INS_Address(INS_Next(n3));
                                }
                            }
                        }

                    }
                }
            }
        }


    }
    return 0;
}

void Routine(RTN rtn, VOID *v) {
    if (RTN_Valid(rtn) && RTN_Name(rtn).compare("loop_signature") != 0) {
        RTN_Open(rtn);
        int is_loop;
        int print_fn = 0;
        for (INS ins = RTN_InsHead(rtn); INS_Valid(ins); ins = INS_Next(ins)) {


            is_loop = isLoopSig(ins);
            if (is_loop) {
                print_fn = 1;
                TraceFile << "Loop start: " << std::hex << is_loop << endl;
            }

            // INS_IsMovFullRegRegSame não está funcionando
        }


        if (print_fn) {

            for (INS ins = RTN_InsHead(rtn); INS_Valid(ins); ins = INS_Next(ins)) {
                TraceFile << INS_Address(ins) << ": " << INS_Disassemble(ins);
                TraceFile << endl;

            }

            TraceFile << endl << endl;
        }

        RTN_Close(rtn);

>>>>>>> e065af4c7e2ec60a785e591c5ec2692384123ce0
    }
  }
  return ins;
}

<<<<<<< HEAD
string ADDRINTToHexString(ADDRINT a)
{
    ostringstream temp;
    temp << "0x" << hex <<a;
    return temp.str();
}

void Routine(RTN rtn, VOID *v) {
=======
VOID Fini(INT32 code, VOID *v) {
>>>>>>> e065af4c7e2ec60a785e591c5ec2692384123ce0

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

<<<<<<< HEAD
VOID Fini(INT32 code, VOID *v) { TraceFile.close(); }

int main(int argc, char *argv[]) {
  PIN_InitSymbols();
  PIN_Init(argc, argv);
=======
int main(int argc, char *argv[]) {
    PIN_InitSymbols();
    PIN_Init(argc, argv);
>>>>>>> e065af4c7e2ec60a785e591c5ec2692384123ce0

  TraceFile.open("bb.out");

  RTN_AddInstrumentFunction(Routine, 0);
  PIN_AddFiniFunction(Fini, 0);

  PIN_StartProgram();

  return 0;
}
