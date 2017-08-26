#include "pin.H"
#include <iostream>
#include <fstream>

std::ofstream TraceFile;

VOID PrintfBefore()
{
    TraceFile << "Printf chamado!" << endl;
}

VOID Image(IMG img, VOID *v)
{
    RTN printfRtn = RTN_FindByName(img, "printf");
    if (RTN_Valid(printfRtn))
    {
        RTN_Open(printfRtn);
        RTN_InsertCall(printfRtn, IPOINT_BEFORE, (AFUNPTR)PrintfBefore, IARG_END);
        RTN_Close(printfRtn);
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

    TraceFile.open("printftrace.out");
    
    IMG_AddInstrumentFunction(Image, 0);
    PIN_AddFiniFunction(Fini, 0);

    PIN_StartProgram();

    return 0;
}
