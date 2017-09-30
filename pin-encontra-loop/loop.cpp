#include "pin.H"
#include <iostream>
#include <fstream>
#include <string>

std::ofstream TraceFile;
unsigned long trace_count = 0;

void Routine(RTN rtn, VOID *v)
{
    // Descartar as outras funções para teste
    if (RTN_Name(rtn).compare("main") == 0)
    {
        RTN_Open(rtn);

        // Percorre as instruções
        for (INS ins = RTN_InsHead(rtn); INS_Valid(ins); ins = INS_Next(ins))
        {
            TraceFile << std::hex << INS_Address(ins) << " : " << INS_Disassemble(ins);

            // Se for uma instrução do tipo branch condicional  
            if (INS_Category(ins) == XED_CATEGORY_COND_BR)
            {
                unsigned long target = INS_DirectBranchOrCallTargetAddress(ins);
                bool found_target = false;

                // Certifica que existe o destino do branch.
                for (INS target_ins = ins; INS_Valid(target_ins); target_ins = INS_Prev(target_ins))
                {
                    if (INS_Address(target_ins) == target)
                    {
                        found_target = true;
                        break;
                    }
                }

                if (found_target)
                {
                    TraceFile
                            << " -- HERE -- Target: " << std::hex << target;
                }
            }
            TraceFile << endl;
        }
        RTN_Close(rtn);
    }
}

VOID Fini(INT32 code, VOID *v)
{

    TraceFile.close();
}

int main(int argc, char *argv[])
{
    PIN_InitSymbols();
    PIN_Init(argc, argv);

    TraceFile.open("bb.out");

    RTN_AddInstrumentFunction(Routine, 0);
    PIN_AddFiniFunction(Fini, 0);

    PIN_StartProgram();

    return 0;
}
