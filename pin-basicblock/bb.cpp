#include "pin.H"
#include <iostream>
#include <fstream>

std::ofstream TraceFile;
unsigned long trace_count = 0;

void Trace(TRACE trace, VOID *v)
{
    trace_count++;
    unsigned long bb_count = 0;
    for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl))
    {
        bb_count++;
    }
    TraceFile << "[Trace] Number of BBs: " << bb_count << endl;
}

VOID Fini(INT32 code, VOID *v)
{
    TraceFile << "Total number of traces: " << trace_count << endl;
    TraceFile.close();
}

int main(int argc, char *argv[])
{
    PIN_InitSymbols();
    PIN_Init(argc, argv);

    TraceFile.open("bb.out");

    TRACE_AddInstrumentFunction(Trace, 0);
    PIN_AddFiniFunction(Fini, 0);

    PIN_StartProgram();

    return 0;
}
