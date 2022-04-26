// Shawn Sherman Brannon Shelnutt


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "compiler.h"
#define MAX_NUMBER_TOKENS 1000
#define MAX_IDENT_LEN 11
#define MAX_NUMBER_LEN 5

lexeme *list;
int lex_index;

void printlexerror(int type);
void printtokens();


lexeme *lexanalyzer(char *input, int printFlag)
{
	list = malloc(sizeof(lexeme) * MAX_NUMBER_TOKENS);
	lex_index = 0;
	char *str = (char*) malloc(strlen(input) * sizeof(char));
	int length = strlen(input);
	int index = 0;
	int check_control_char;
	int x = 0;
	int y;
	int j;

	while(index < length)
	{

		{
			// printf("%s\n",str);
			// whitespace scenario
			if(input[index] == ' ' || input[index] == ';' || input[index] == '.' || iscntrl(input[index]) || input[index] == ','
				|| input[index] == '<' || input[index] == '>' || input[index] == '!' || input[index] == '(' || input[index] == ')'
				|| input[index] == '+' || input[index] == ',' || input[index] == '=')
			{
				// printf("%s",str);
				// potential lex is a number
				if(isdigit(str[0]))
					{
					// identifer may not start with digit error
					for (int j = 1; j <= strlen(str) - 1;j++)
					{
					if(!isdigit(str[j]))
					{
						printf("Lexical Analyzer Error: Invalid Identifier\n");
						exit(0);
					}
					// more than 5 digits error
						if(strlen(str) > 5)
						{
							printf("Lexical Analyzer Error: Number Length\n");
							exit(0);
						}

				}
						// this token is a number
						list[lex_index].type = 30;
						list[lex_index].value = atoi(str);
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					// it is a potential string or identier
					else if (isalpha(str[0]))
					{
						// reverved word const
						if ((strcmp(str,"const")) == 0)
						{
							list[lex_index].type = 2;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;
						}
						// reserved word var
						else if ((strcmp(str,"var")) == 0)
						{
							list[lex_index].type = 4;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;
						}
						// reserved word procedure
						else if ((strcmp(str,"procedure")) == 0)
						{
							list[lex_index].type = 6;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;
						}
						// reserved word call
						else if ((strcmp(str,"call")) == 0)
						{
							list[lex_index].type = 8;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;
						}
						// reserved word if
						else if ((strcmp(str,"if")) == 0)
						{
							list[lex_index].type = 10;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;
						}
						// reserved word then
						else if ((strcmp(str,"then")) == 0)
						{
							list[lex_index].type = 12;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;
						}
						// reserved word else
						else if ((strcmp(str,"else")) == 0)
						{
							list[lex_index].type = 14;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;
						}
						// reserved word while
						else if ((strcmp(str,"while")) == 0)
						{
							list[lex_index].type = 16;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;
						}
						// reserved word do
						else if ((strcmp(str,"do")) == 0)
						{
							list[lex_index].type = 18;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;
						}
						// reserved word begin
						else if ((strcmp(str,"begin")) == 0)
						{
							list[lex_index].type = 20;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;
						}
						// reserved word end
						else if ((strcmp(str,"end")) == 0)
						{
							list[lex_index].type = 22;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;
						}
						// reserved word read
						else if ((strcmp(str,"read")) == 0)
						{
							list[lex_index].type = 24;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;
						}
						// reserved word write
						else if ((strcmp(str,"write")) == 0)
						{
							list[lex_index].type = 26;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;
						}

						else
						{
							if(strlen(str) > 11)
								{
									printf("Lexical Analyzer Error: Identifier Length\n");
									exit(0);
								}
							else
							{
								list[lex_index].type = 28;
								strcpy(list[lex_index].name, str);
								lex_index++;
								free(str);
								str = (char*) malloc(strlen(input) * sizeof(char));
								x = 0;
							}

						}

					} // here
					// special symbol equal
					else if ((strcmp(str,"==")) == 0)
					{
						list[lex_index].type = 1;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					// special symbol not equal
					else if ((strcmp(str,"!=")) == 0)
					{
						list[lex_index].type = 3;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					// special symbol less than
					else if ((strcmp(str,"<")) == 0)
					{
					if(input[index+1] != '=')
					{
						list[lex_index].type = 5;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					else
					{
					list[lex_index].type = 7;
					lex_index++;
					free(str);
					str = (char*) malloc(strlen(input) * sizeof(char));
					x = 0;
					break;
					}
				}
					// special symbol less then or equal too
					else if ((strcmp(str,"<=")) == 0)
					{
						list[lex_index].type = 7;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					// special symbol greater than
					else if ((strcmp(str,">")) == 0)
					{
					if(input[index+1] != '=')
					{
						list[lex_index].type = 9;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					else
					{
					list[lex_index].type = 11;
					lex_index++;
					free(str);
					str = (char*) malloc(strlen(input) * sizeof(char));
					x = 0;
					break;
					}
				}
					// special symbol greater than or equal too
					else if ((strcmp(str,">=")) == 0)
					{
						list[lex_index].type = 11;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					// special symbol multiply
					else if ((strcmp(str,"*")) == 0)
					{
						list[lex_index].type = 13;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;

					}
					// special symbol divide
					else if ((strcmp(str,"/")) == 0)
					{
							list[lex_index].type = 15;
							lex_index++;
							free(str);
							str = (char*) malloc(strlen(input) * sizeof(char));
							x = 0;

					}
					// special symbol plus
					else if ((strcmp(str,"+")) == 0)
					{
						list[lex_index].type = 17;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					// special symbol minus
					else if ((strcmp(str,"-")) == 0)
					{
						list[lex_index].type = 19;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					// special symbol open parenthesis
					else if ((strcmp(str,"(")) == 0)
					{
						list[lex_index].type = 21;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					// special symbol closing parenthesis
					else if ((strcmp(str,")")) == 0)
					{
						list[lex_index].type = 23;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					// special symbol period
					else if ((strcmp(str,".")) == 0)
					{
						list[lex_index].type = 27;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					// special symbol comma
					else if ((strcmp(str,",")) == 0)
					{
						list[lex_index].type = 25;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					// special symbol semi colon
					else if ((strcmp(str,";")) == 0)
					{
						list[lex_index].type = 29;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					// special symbol assign
					else if ((strcmp(str,":=")) == 0)
					{
						list[lex_index].type = 31;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					else if((strcmp(str,"&&")) == 0)
					{
						list[lex_index].type = 32;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input)*sizeof(char));
						x=0;
					}
					else if((strcmp(str,"||")) == 0)
					{
						list[lex_index].type = 33;
						lex_index++;
						free(str);
						str = (char*)malloc(strlen(input)*sizeof(char));
						x=0;
					}
					else if((strcmp(str,"!")) == 0)
					{
						list[lex_index].type = 34;
						lex_index++;
						free(str);
						str = (char*)malloc(strlen(input)*sizeof(char));
						x=0;
					}


					}
					// potential comment
					else if (input[index] == '/')
					{
						// start of comment
						if(input[index+1] == '*')
						{
							j = index;
							// iterate till you find end of comment
							for(j;j < length;j++)
							{
								if(input[j] == '*' && input[j+1] == '/')
									break;

							}
							if (j == length)
							{
								// never ending comment error
								printf("Lexical Analyzer Error: Never-ending comment\n");
								exit(0);
							}
							index = j + 2;
						}
					}
					if (input[index] == ';')
					{
						list[lex_index].type = 29;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					else if (input[index] == '.')
					{
						list[lex_index].type = 27;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					else if (input[index] == ',')
					{
						list[lex_index].type = 25;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					else if (input[index] == '<')
					{
					if (input[index+1] != '=')
					{
						list[lex_index].type = 5;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
					}
					else
					{
						list[lex_index].type = 7;
						lex_index++;
						free(str);
						str = (char*) malloc(strlen(input) * sizeof(char));
						x = 0;
						index = index + 2;
					}
				}
				else if (input[index] == '>')
				{
				if (input[index+1] != '=')
				{
					list[lex_index].type = 9;
					lex_index++;
					free(str);
					str = (char*) malloc(strlen(input) * sizeof(char));
					x = 0;
				}
				else
				{
					list[lex_index].type = 11;
					lex_index++;
					free(str);
					str = (char*) malloc(strlen(input) * sizeof(char));
					x = 0;
					index = index + 2;
				}
			}
			else if (input[index] == '!')
			{
				if(input[index+1] == '=')
				{
					list[lex_index].type = 3;
					lex_index++;
					free(str);
					str = (char*) malloc(strlen(input) * sizeof(char));
					x = 0;
					index = index + 2;
				}
			}
			if(isdigit(input[index]) || isalpha(input[index]) || input[index] == '=' || input[index] == '!'
			  || input[index] == '*' || input[index] == '(' || input[index] == ')'
			   || input[index] == ':' || input[index] == '/' || input[index] == '-')
			{
			str[x] = input[index];
			x++;
			}
			else if (iscntrl(input[index]) || isspace(input[index]) || input[index] == ';' || input[index] == '.' || input[index] == ','
							|| input[index] == '<' || input[index] == '>')
			{

			}
			else
			{
				printf("Lexical Analyzer Error: Invalid Symbol\n");
				exit(0);
			}


		}
		index++;
	}

	if (printFlag)
		printtokens();

	// these last two lines are really important for the rest of the package to run
	list[lex_index].type = -1;
	return list;
}

void printtokens()
{
	int i;
	printf("Lexeme Table:\n");
	printf("lexeme\t\ttoken type\n");
	for (i = 0; i < lex_index; i++)
	{
		switch (list[i].type)
		{
			case eqlsym:
				printf("%11s\t%d", "==", eqlsym);
				break;
			case neqsym:
				printf("%11s\t%d", "!=", neqsym);
				break;
			case lsssym:
				printf("%11s\t%d", "<", lsssym);
				break;
			case leqsym:
				printf("%11s\t%d", "<=", leqsym);
				break;
			case gtrsym:
				printf("%11s\t%d", ">", gtrsym);
				break;
			case geqsym:
				printf("%11s\t%d", ">=", geqsym);
				break;
			case multsym:
				printf("%11s\t%d", "*", multsym);
				break;
			case divsym:
				printf("%11s\t%d", "/", divsym);
				break;
			case plussym:
				printf("%11s\t%d", "+", plussym);
				break;
			case minussym:
				printf("%11s\t%d", "-", minussym);
				break;
			case lparensym:
				printf("%11s\t%d", "(", lparensym);
				break;
			case rparensym:
				printf("%11s\t%d", ")", rparensym);
				break;
			case commasym:
				printf("%11s\t%d", ",", commasym);
				break;
			case periodsym:
				printf("%11s\t%d", ".", periodsym);
				break;
			case semicolonsym:
				printf("%11s\t%d", ";", semicolonsym);
				break;
			case assignsym:
				printf("%11s\t%d", ":=", assignsym);
				break;
			case beginsym:
				printf("%11s\t%d", "begin", beginsym);
				break;
			case endsym:
				printf("%11s\t%d", "end", endsym);
				break;
			case ifsym:
				printf("%11s\t%d", "if", ifsym);
				break;
			case thensym:
				printf("%11s\t%d", "then", thensym);
				break;
			case elsesym:
				printf("%11s\t%d", "else", elsesym);
				break;
			case whilesym:
				printf("%11s\t%d", "while", whilesym);
				break;
			case dosym:
				printf("%11s\t%d", "do", dosym);
				break;
			case callsym:
				printf("%11s\t%d", "call", callsym);
				break;
			case writesym:
				printf("%11s\t%d", "write", writesym);
				break;
			case readsym:
				printf("%11s\t%d", "read", readsym);
				break;
			case constsym:
				printf("%11s\t%d", "const", constsym);
				break;
			case varsym:
				printf("%11s\t%d", "var", varsym);
				break;
			case procsym:
				printf("%11s\t%d", "procedure", procsym);
				break;
			case identsym:
				printf("%11s\t%d", list[i].name, identsym);
				break;
			case numbersym:
				printf("%11d\t%d", list[i].value, numbersym);
				break;
		}
		printf("\n");
	}
	printf("\n");
	printf("Token List:\n");
	for (i = 0; i < lex_index; i++)
	{
		if (list[i].type == numbersym)
			printf("%d %d ", numbersym, list[i].value);
		else if (list[i].type == identsym)
			printf("%d %s ", identsym, list[i].name);
		else
			printf("%d ", list[i].type);
	}
	printf("\n");
}

void printlexerror(int type)
{
	if (type == 1)
		printf("Lexical Analyzer Error: Invalid Identifier\n");
	else if (type == 2)
		printf("Lexical Analyzer Error: Number Length\n");
	else if (type == 3)
		printf("Lexical Analyzer Error: Identifier Length\n");
	else if (type == 4)
		printf("Lexical Analyzer Error: Invalid Symbol\n");
	else if (type == 5)
		printf("Lexical Analyzer Error: Never-ending comment\n");
	else
		printf("Implementation Error: Unrecognized Error Type\n");

	free(list);
	return;
}
