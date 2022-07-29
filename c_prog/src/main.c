#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include "action.h"

int CountPolinom()
{
	int n;
	int error_code;
	do {
		printf("Input count of polinomials: ");
		error_code = scanf("%d", &n);
		CleanCh();
		if (!error_code || n <= 0)
		{
			printf("InputError: expected natural argument. Please, try again.\n\n");
			continue;
		}
		printf("Your input : %d\n\n", n);
	} while (!error_code || n <= 0);
	
	return n;
}

void main() 
{
	int n;
	int item;
	int el_size;
	Array* PolinomRes;
	Array* PolinomH;

	printf("**Starting running the programme**\n\n");
	Instroduce();

	while (1)
	{
		do // selection of data type and menu item
		{ 
			el_size = ElementType();
			item = Menu();
		} while (item == '6');
		
		switch (item)
		{
			case '1': // Polinomial addition
			{
				n = CountPolinom();

				Array* Polinom = Create(el_size, 1);

				for (int i = 2; i <= n; i++) 
				{
					Array* PolinomI = Create(el_size, i);
					printf("Step: %d\n", i - 1);
					PolinomRes = Addition(Polinom, PolinomI);
					DisposePolinom(PolinomI);
					PolinomH = Polinom;
					DisposePolinom(PolinomH);
					Polinom = PolinomRes;
				}
				DisposePolinom(Polinom);
				break;
			}
			case '2': // Polinomial multiplication
			{
				n = CountPolinom();

				Array* Polinom = Create(el_size, 1);

				for (int i = 2; i <= n; i++) 
				{
					Array* PolinomI = Create(el_size, i);	
					printf("Step: %d\n", i - 1);
					PolinomRes = Multiplication(Polinom, PolinomI);
					DisposePolinom(PolinomI);
					PolinomH = Polinom;
					DisposePolinom(PolinomH);
					Polinom = PolinomRes;
				}
				DisposePolinom(Polinom);
				break;
			}
			case '3': // Polinomial multiplication by constant				
			{
				void* alpha = malloc(el_size);
				Array* Polinom = Create(el_size, 0);

				InputControl(alpha, el_size);
				MultiplicationbyConstant(Polinom, alpha);
				DisposePolinom(Polinom);
				free(alpha);
				break;
			}
			case '4': // Calculating polinomial by argument
			{
				void* x = malloc(el_size);
				Array* Polinom = Create(el_size, 0);
				
				InputControl(x, el_size);
				Calculate(Polinom, x);
				DisposePolinom(Polinom);
				free(x);
				break;
			}
			case '5': // Composition of functions
			{
				printf("Create function-argument\n");
				Array* PolinomA = Create(el_size, 0);
				printf("Create function-function\n");
				Array* PolinomF = Create(el_size, 0);
				Array* PolinomRes = PolinomF;
				PolinomRes = Composition(PolinomA, PolinomRes);
				DisposePolinom(PolinomA);
				DisposePolinom(PolinomF);
				DisposePolinom(PolinomRes);
				break;
			}
			case '7': // exit
			{
				printf("End of running the programme...\n\n");
				exit(0);
			}
			default: // unexpected
			{
				printf("InputError: item doesn't exist. Please, try again.\n\n");
				break;
			}
		}
	}
}

