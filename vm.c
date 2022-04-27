#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"
#define MAX_REG_LENGTH 10
#define MAX_DATA_LENGTH 50
#define MAX_PROGRAM_LENGTH 150




void print_execution(int line, char *opname, instruction IR, int PC, int BP, int SP, int RP, int *data_stack, int *register_stack)
{
	int i;
	// print out instruction and registers
	printf("%2d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t\t", line, opname, IR.l, IR.m, PC, BP, SP, RP);

	// print register stack
	// I modified the print function such that it print to for (i = MAX_REG_LENGTH; to i > RP; as opposed to
	// for (i = MAX_REG_LENGTH - 1; i >= RP)
	for (i = MAX_REG_LENGTH; i > RP; i--)
		printf("%d ", register_stack[i]);
	printf("\n");

	// print data stack
	printf("\tdata stack : ");
	for (i = 0; i <= SP; i++)
		printf("%d ", data_stack[i]);
	printf("\n");
}

int base(int L, int BP, int *data_stack)
{
	int ctr = L;
	int rtn = BP;
	while (ctr > 0)
	{
		rtn = data_stack[rtn];
		ctr--;
	}
	return rtn;
}

void execute_program(instruction *code, int printFlag)
{
	if (printFlag)
	{

		int *register_s;
		int *data_s;
		register_s = (int*) calloc(sizeof(int), MAX_REG_LENGTH);
		data_s = (int*) calloc(sizeof(int), MAX_DATA_LENGTH);




		// default values
		int BP = 0, SP = BP - 1, PC = 0, RP =  MAX_REG_LENGTH, halt = 1;
		instruction *IR = malloc(sizeof(struct instruction));
		int line = -1;
		printf("\t\t\t\tPC\tBP\tSP\tRP\n");
		printf("Initial values:\t\t\t%d\t%d\t%d\t%d\n", PC, BP, SP, RP);
		while(halt == 1){
			// fetch cycle;
			line = PC;
			IR = &code[PC];
			PC++;

			// execution cycle
			switch(IR->opcode) {
					case(1): //LIT
						register_s[RP] = IR->m;
						RP--;
						print_execution(line, "LIT",*IR, PC, BP,SP,RP, data_s,register_s);
						break;

					case(2): //OPR
						switch(IR->m){
							case(0): // RET
								SP = BP - 1;
								PC = data_s[BP + 2];
								BP = data_s[BP + 1];

								print_execution(line, "RET",*IR, PC, BP,SP,RP, data_s,register_s);
								break;

							case(1): //NEG
								register_s[RP+1] = register_s[RP+1] * -1;
								print_execution(line, "NEG",*IR, PC, BP,SP,RP, data_s,register_s);
								break;
							case(2): //ADD
								register_s[RP+2] = register_s[RP+2] + register_s[RP+1];
								RP++;
								print_execution(line, "ADD",*IR, PC, BP,SP,RP, data_s,register_s);
								break;
							case(3): //SUB
								register_s[RP+2] = register_s[RP+2] - register_s[RP+1];
								RP++;
								print_execution(line, "SUB",*IR, PC, BP,SP,RP, data_s,register_s);
								break;
							case(4): //MUL
								register_s[RP+2] = register_s[RP+2] * register_s[RP+1];
								RP++;
								print_execution(line, "MUL",*IR, PC, BP,SP,RP, data_s,register_s);
								break;
							case(5): //DIV
								register_s[RP+2] = register_s[RP+2] / register_s[RP+1];
								RP++;
								print_execution(line, "DIV",*IR, PC, BP,SP,RP, data_s,register_s);
								break;
							case(6): //EQL
									if(register_s[RP+2] == register_s[RP+1])
										register_s[RP+2] = 1;
									else
										register_s[RP+2] = 0;
									RP++;
									print_execution(line, "EQL",*IR, PC, BP,SP,RP, data_s,register_s);
								break;
							case(7): //NEQ
								if(register_s[RP+2] != register_s[RP+1])
									register_s[RP+2] = 1;
								else
									register_s[RP+2] = 0;
								RP++;
								print_execution(line, "NEQ",*IR, PC, BP,SP,RP, data_s,register_s);
								break;
							case(8): //LSS
								if(register_s[RP+2] < register_s[RP+1])
									register_s[RP+2] = 1;
								else
									register_s[RP+2] = 0;
									RP++;
								print_execution(line, "LSS",*IR, PC, BP,SP,RP, data_s,register_s);
								break;
							case(9): //LEQ
								if(register_s[RP+2] <= register_s[RP+1])
									register_s[RP+2] = 1;
								else
									register_s[RP+2] = 0;
								RP++;
								print_execution(line, "LEQ",*IR, PC, BP,SP,RP, data_s,register_s);
								break;
							case(10): //GTR
								if(register_s[RP+2] > register_s[RP+1])
									register_s[RP+2] = 1;
								else
									register_s[RP+2] = 0;
								RP++;
								print_execution(line, "GTR",*IR, PC, BP,SP,RP, data_s,register_s);
								break;
							case(11): //GEQ
								if(register_s[RP+2] >= register_s[RP+1])
									register_s[RP+2] = 1;
								else
									register_s[RP+2] = 0;
								RP++;
								print_execution(line, "GEQ",*IR, PC, BP,SP,RP, data_s,register_s);
								break;
							case(12): //AND
								if(register_s[RP+2] == 1 && register_s[RP+1] == 1)
									register_s[RP+2] = 1;
								else
									register_s[RP+2] = 0;

								RP++;	
								print_execution(line, "AND", *IR, PC,BP,SP,RP,data_s,register_s);
								break;
							case(13): // ORR
								if(register_s[RP+2] == 1 || register_s[RP+1] == 1)
									register_s[RP+2] = 1;
								else 
									register_s[RP+2] = 0;

								RP++;
								print_execution(line,"ORR",*IR,PC,BP,SP,RP,data_s,register_s);
								break;
							case(14): //NOT
								if(register_s[RP+1] == 1)
									register_s[RP+1] = 0;
								else
									register_s[RP+1] = 1;

								print_execution(line,"NOT",*IR,PC,BP,SP,RP,data_s,register_s);
								break;
							}
						break;
					case(3): // LOD
						register_s[RP] = data_s[base(IR->l,BP,&data_s[0]) + IR->m]; // &data_s[0] might be wrong
						RP--;
						print_execution(line, "LOD",*IR, PC, BP,SP,RP, data_s,register_s);
						break;
					case(4): // STO
						data_s[base(IR->l,BP,&data_s[0]) + IR->m] = register_s[RP+1];
						RP++;
						print_execution(line, "STO",*IR, PC, BP,SP,RP, data_s,register_s);
						break;
					case(5): // CAL
						SP++;
						data_s[SP] = base(IR->l,BP,&data_s[0]); //static link
						SP++;
						data_s[SP] = BP; //dynamic link
						SP++;
						data_s[SP] = PC; //return address
						BP = SP - 2; // static link of the new activation record
						PC = IR->m; // PC = M
						SP = SP-3;
						print_execution(line, "CAL",*IR, PC, BP,SP,RP, data_s,register_s);
						break;
					case(06): //INC
						SP = SP + IR->m;
						print_execution(line, "INC",*IR, PC, BP,SP,RP, data_s,register_s);
						break;
					case(7): // JMP
						PC = IR->m;
						print_execution(line, "JMP",*IR, PC, BP,SP,RP, data_s,register_s);
						break;
					case(8): // JPC
						if(register_s[RP+1] == 0)
							PC = IR->m;
						RP++;
						print_execution(line, "JPC",*IR, PC, BP,SP,RP, data_s,register_s);
						break;
					case(9):
					 	switch(IR->m){
							case(1):	// WRT
							printf("Top of Stack Value: %d\n",register_s[RP+1]);
							RP++;
							print_execution(line, "WRT",*IR, PC, BP,SP,RP, data_s,register_s);
							break;
							case(2): // RED
							printf("Please Enter an Integer: ");
							printf("\n");
							scanf("%d",&register_s[RP]);
							RP--;
							print_execution(line, "RED",*IR, PC, BP,SP,RP, data_s,register_s);
							break;
							case(3): //HAL
								halt = 0;
								print_execution(line, "HAL",*IR, PC, BP,SP,RP, data_s,register_s);
								printf(" ");
								break;

				}

					}


						}
	}
}

