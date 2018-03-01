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

// Verifica se a instrução [ins] é o início de uma marcação de loop.
// Caso for, retorna a primeira instrução do predicado
// Caso não for, retorna a própria instrução
INS CheckLoop(INS ins)
{
  INS insBackup = ins;
  if (!INS_Valid(ins) || !INS_IsNop(ins))
    return insBackup;

  ins = INS_Next(ins);

  if (!INS_Valid(ins) || !INS_IsMov(ins))
    return insBackup;

  ins = INS_Next(ins);

  if (!INS_Valid(ins) || !INS_IsNop(ins))
    return insBackup;

  ins = INS_Next(ins);

  if (!INS_Valid(ins) || !INS_IsMov(ins))
    return insBackup;

  ins = INS_Next(ins);

  if (!INS_Valid(ins) || !INS_IsNop(ins))
    return insBackup;

  return INS_Next(ins);
}

void Routine(RTN rtn, VOID *v)
{
  if (RTN_Name(rtn).compare("main") != 0)
    return;

  RTN_Open(rtn);
  INS ins = RTN_InsHead(rtn);

  while (INS_Valid(ins))
  {
    //TraceFile << hex << INS_Address(ins) << " - " << INS_Disassemble(ins) << endl;
    INS insLoop = CheckLoop(ins);
    if (insLoop == ins)
      ins = INS_Next(ins);
    else
    // Encontrou loop
    {
      ins = insLoop;

      std::vector<INS> loop_predicate;
      std::vector<INS> loop_body;
      std::vector<INS> loop_condition;

      INS x;
      for (x = insLoop; INS_Valid(x) && !INS_IsBranch(x); x = INS_Next(x))
      {
        loop_predicate.push_back(x);
      }
      loop_predicate.push_back(x);

      ADDRINT jmp_addr = INS_DirectBranchOrCallTargetAddress(x);

      for (x = INS_Next(x); INS_Valid(x) && INS_Address(x) != jmp_addr;
           x = INS_Next(x))
      {
        loop_body.push_back(x);
      }

      for (; INS_Valid(x) && !INS_IsBranch(x); x = INS_Next(x))
      {
        loop_condition.push_back(x);
      }
      loop_condition.push_back(x);

      TraceFile << "[Predicate]" << endl;
      for (std::vector<INS>::iterator it = loop_predicate.begin();
           it != loop_predicate.end(); ++it)
      {
        TraceFile << std::hex << INS_Address(*it) << ": ";
        TraceFile << INS_Disassemble(*it) << endl;
      }

      TraceFile << "[Body]" << endl;
      for (std::vector<INS>::iterator it = loop_body.begin();
           it != loop_body.end(); ++it)
      {
        TraceFile << std::hex << INS_Address(*it) << ": ";
        TraceFile << INS_Disassemble(*it) << endl;
      }

      TraceFile << "[Condition]" << endl;
      for (std::vector<INS>::iterator it = loop_condition.begin();
           it != loop_condition.end(); ++it)
      {
        TraceFile << std::hex << INS_Address(*it) << ": ";
        TraceFile << INS_Disassemble(*it) << endl;
      }

      TraceFile << endl;
    }
  }
  RTN_Close(rtn);
}

VOID Fini(INT32 code, VOID *v)
{


  TraceFile.close();
}

int main(int argc, char *argv[])
{
  PIN_InitSymbols();
  PIN_Init(argc, argv);

  TraceFile.open("log.out");

  RTN_AddInstrumentFunction(Routine, 0);
  PIN_AddFiniFunction(Fini, 0);

  PIN_StartProgram();

  return 0;
}
