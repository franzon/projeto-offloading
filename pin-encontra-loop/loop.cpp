#include "pin.H"
#include <iostream>
#include <fstream>
#include <string>

std::ofstream TraceFile;
unsigned long trace_count = 0;

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

    }
}

VOID Fini(INT32 code, VOID *v) {

    TraceFile.close();
}

int main(int argc, char *argv[]) {
    PIN_InitSymbols();
    PIN_Init(argc, argv);

    TraceFile.open("bb.out");

    RTN_AddInstrumentFunction(Routine, 0);
    PIN_AddFiniFunction(Fini, 0);

    PIN_StartProgram();

    return 0;
}
