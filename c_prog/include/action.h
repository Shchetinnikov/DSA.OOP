#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "interface.h"

typedef struct Array
{
	void* buffer;  // coefficients
	int degree;
	int count_element;
	int el_size;
} Array;

void DisposePolinom(Array* Polinom)
{
	free(Polinom->buffer);
	free(Polinom);
}

void OutputPolinom(Array* Polinom)
{
	int i;
	printf("P(%d)(x) = ", Polinom->degree);
	switch (Polinom->el_size)
	{
		case sizeof(int) :
		{
			for (i = Polinom->degree; i >= 0; i--)
				if (*((int*)Polinom->buffer + i) < 0)
				{
					printf("(%d) * x^%d", *((int*)Polinom->buffer + i), i);
					printf(i ? " + " : "");
				}
				else
				{
					printf("%d * x^%d", *((int*)Polinom->buffer + i), i);
					printf(i ? " + " : "");
				}
			break;
		}
		case sizeof(double) :
		{
			for (i = Polinom->degree; i >= 0; i--)
				if (*((double*)Polinom->buffer + i) < 0)
				{
					printf("(%lf) * x^%d", *((double*)Polinom->buffer + i), i);
					printf(i ? " + " : "");
				}
				else
				{
					printf("%lf * x^%d", *((double*)Polinom->buffer + i), i);
					printf(i ? " + " : "");
				}
			break;
		}
	}
	printf("\n\n");
}

void ReadCoefficients(Array* Polinom)
{
	int error_code;
	do 
	{
		printf("Please, input polynomial coefficients a(0), a(1) ...a(n-1), a(n) by Space : ");
		error_code = 1;

		switch(Polinom->el_size)
		{
			case sizeof(int):
			{
				for (int i = 0; i < Polinom->count_element; i++)
				{
					error_code = scanf("%d", (int*)Polinom->buffer + i);
					if (!error_code)
					{
						CleanCh();
						break;
					}
				}
				error_code ? CleanCh(), printf("Successfully completed\n\n") : printf("InputError: expected integer polynomial coefficients. "
																			 "Please, try again.\n\n");
				break;
			}
			case sizeof(double):
			{
				for (int i = 0; i < Polinom->count_element; i++)
				{
					error_code = scanf("%lf", (double*)Polinom->buffer + i);
					if (!error_code)
					{
						CleanCh();
						break;
					}
				}
				CleanCh();
				error_code ? printf("Successfully completed\n\n") : printf("InputError: expected double polynomial coefficients. " 
																		     "Please, try again.\n\n");				
				break;
			}
		}
	} while (!error_code);
}

// delete coefficients of zero of highest x-degree
void ZeroCoefficients(Array* Polinom) 
{
	switch (Polinom->el_size)
	{
		case sizeof(int):
		{
			while (*((int*)Polinom->buffer + Polinom->degree) == 0 && Polinom->degree > 0)
			{
				Polinom->degree--;
				Polinom->count_element--;
			}
		}
		case sizeof(double):
		{
			while (*((double*)Polinom->buffer + Polinom->degree) == 0 && Polinom->degree > 0)
			{
				Polinom->degree--;
				Polinom->count_element--;
			}
		}
	}
}


Array* Create(int el_size, int num)  
{									
	int degree;
	int error_code;
	Array* Polinom = (Array*)malloc(sizeof(Array));
	
	do  // read polinom degree 
	{
		num ? printf("Please, input degree 'n' of polinomial %d: ", num) : printf("Please, input degree 'n' of polinomial: ");
		
		error_code = scanf("%d", &degree);
		CleanCh();
		if (!error_code || degree <= 0) 
		{
			printf("InputError: expected natural argument. Please, try again.\n\n");
			continue;
		}
	} while (!error_code || degree <= 0);
	printf("Your input: %d\n\n", degree);

	Polinom->degree = degree;
	Polinom->count_element = degree + 1;
	Polinom->el_size = el_size;
	Polinom->buffer = malloc(Polinom->el_size * (Polinom->count_element));

	ReadCoefficients(Polinom);
	ZeroCoefficients(Polinom);
	OutputPolinom(Polinom);
	
	return Polinom;
}

Array* Addition(Array* Polinom1, Array* Polinom2)
{
	if (Polinom1->el_size != Polinom2->el_size)
		ParameterError();
	int i;
	int min_count = min(Polinom1->count_element, Polinom2->count_element);
	int max_count = max(Polinom1->count_element, Polinom2->count_element);

	Array* MaxPolinom;
	if (max_count == Polinom1->count_element)
		MaxPolinom = Polinom1;
	else
		MaxPolinom = Polinom2;

	Array* Polinom = malloc(sizeof(Array));
	Polinom->buffer = malloc(Polinom1->el_size * max_count);
	Polinom->el_size = Polinom1->el_size;
	Polinom->degree = max_count - 1;
	Polinom->count_element = max_count;

	switch (Polinom1->el_size)
	{
		case sizeof(int) :
		{
			for (i = 0; i < min_count; i++)
				*((int*)Polinom->buffer + i) = *((int*)Polinom1->buffer + i) + *((int*)Polinom2->buffer + i);
			for (; i < max_count; i++)
				*((int*)Polinom->buffer + i) = *((int*)MaxPolinom->buffer + i);
			break;
		}
		case sizeof(double) :
		{
			for (i = 0; i < min_count; i++)
				*((double*)Polinom->buffer + i) = *((double*)Polinom1->buffer + i) + *((double*)Polinom2->buffer + i);
			for (; i < max_count; i++)
				*((double*)Polinom->buffer + i) = *((double*)MaxPolinom->buffer + i);
			break;
		}
	}
	ZeroCoefficients(Polinom);
	printf("Result of polinomial addition:\n");
	OutputPolinom(Polinom);
	return Polinom;
}

Array* Multiplication(Array* Polinom1, Array* Polinom2)
{
	if (Polinom1->el_size != Polinom2->el_size)
		ParameterError();
	int degree = Polinom1->degree + Polinom2->degree;
	Array* Polinom = malloc(sizeof(Array));

	Polinom->buffer = malloc(Polinom1->el_size * (degree + 1));
	Polinom->el_size = Polinom1->el_size;
	Polinom->degree = degree;
	Polinom->count_element = degree + 1;

	switch (Polinom->el_size)
	{
		case sizeof(int):
		{
			int a;

			for (int i = 0; i <= Polinom->degree; i++)
				*((int*)Polinom->buffer + i) = 0;
			
			for(int i = 0; i <= Polinom2->degree; i++)
				for (int j = 0; j <= Polinom1->degree; j++)
				{
					a = *((int*)Polinom1->buffer + j) * *((int*)Polinom2->buffer + i);
					degree = j + i;
					*((int*)Polinom->buffer + degree) += a;
				}
			break;
		}
		case sizeof(double):
		{
			double a;

			for (int i = 0; i <= Polinom->degree; i++)
				*((double*)Polinom->buffer + i) = 0;

			for (int i = 0; i <= Polinom2->degree; i++)
				for (int j = 0; j <= Polinom1->degree; j++)
				{
					a = *((double*)Polinom1->buffer + j) * *((double*)Polinom2->buffer + i);
					degree = j + i;
					*((double*)Polinom->buffer + degree) += a;
				}
			break;
		}
	}
	ZeroCoefficients(Polinom);
	printf("Result of polinomial multiplication:\n");
	OutputPolinom(Polinom);
	return Polinom;
}

void MultiplicationbyConstant(Array* Polinom, void* alpha)
{
	switch (Polinom->el_size)
	{
		case sizeof(int) :
		{
			for (int i = 0; i <= Polinom->degree; i++)
				*((int*)Polinom->buffer + i) *= *((int*)alpha);
			break;
		}
		case sizeof(double) :
		{
			for (int i = 0; i <= Polinom->degree; i++)
				*((double*)Polinom->buffer + i) *= *((double*)alpha);
			break;
		}
	}
	ZeroCoefficients(Polinom);
	printf("Result of polinomial multiplication by constant:\n");
	OutputPolinom(Polinom);
}

Array* Composition(Array* PolinomA, Array* PolinomF)
{
	if (PolinomA->el_size != PolinomF->el_size)
		ParameterError();

	int i;
	int j;
	int degree;
	Array* PolinomH;
	Array* PolinomH2;
	Array* PolinomRes;
	Array* polinom;

	degree = PolinomA->degree * PolinomF->degree;

	if (PolinomA->degree == 0)
		degree = PolinomF->degree;
	if (PolinomF->degree == 0)
		degree = 0;

	PolinomRes = malloc(sizeof(Array));
	PolinomRes->buffer = malloc(PolinomA->el_size * (degree + 1));
	PolinomRes->el_size = PolinomA->el_size;
	PolinomRes->degree = degree;
	PolinomRes->count_element = degree + 1;

	switch (PolinomA->el_size)
	{
		case sizeof(int) :
		{
			for (i = 0; i <= PolinomRes->degree; i++)
				*((int*)PolinomRes->buffer + i) = 0;

			for (i = 0; i <= PolinomF->degree; i++)
			{
				PolinomH = malloc(sizeof(Array));
				PolinomH->buffer = malloc(PolinomA->el_size * (degree + 1));
				PolinomH->el_size = PolinomA->el_size;
				PolinomH->degree = 0;
				PolinomH->count_element = degree + 1;

				*((int*)PolinomH->buffer) = 1;
				for (int k = 1; k <= PolinomH->count_element - 1; k++)
					*((int*)PolinomH->buffer + k) = 0;

				for (j = 1; j <= i; j++)
				{
					PolinomH2 = Multiplication(PolinomH, PolinomA);
					polinom = PolinomH;
					DisposePolinom(polinom);
					PolinomH = PolinomH2;
				}
				MultiplicationbyConstant(PolinomH, (int*)PolinomF->buffer + i);

				polinom = PolinomRes;
				PolinomRes = Addition(PolinomRes, PolinomH);
				DisposePolinom(polinom);
				DisposePolinom(PolinomH);
			}
			break;
		}
		case sizeof(double) :
		{
			for (i = 0; i <= PolinomRes->degree; i++)
				*((double*)PolinomRes->buffer + i) = 0;

			for (i = 0; i <= PolinomF->degree; i++)
			{
				PolinomH = malloc(sizeof(Array));
				PolinomH->buffer = malloc(PolinomA->el_size * (degree + 1));
				PolinomH->el_size = PolinomA->el_size;
				PolinomH->degree = 0;
				PolinomH->count_element = degree + 1;

				*((double*)PolinomH->buffer) = 1;
				for (int k = 1; k <= PolinomH->count_element - 1; k++)
					*((double*)PolinomH->buffer + k) = 0;

				for (j = 1; j <= i; j++)
				{
					PolinomH2 = Multiplication(PolinomH, PolinomA);
					polinom = PolinomH;
					DisposePolinom(polinom);
					PolinomH = PolinomH2;
				}
				MultiplicationbyConstant(PolinomH, (double*)PolinomF->buffer + i);

				polinom = PolinomRes;
				PolinomRes = Addition(PolinomRes, PolinomH);
				DisposePolinom(polinom);
				DisposePolinom(PolinomH);
			}
			break;
		}
		
	}
	ZeroCoefficients(PolinomRes);
	printf("Result of composition:\n");
	OutputPolinom(PolinomRes);
	return PolinomRes;
}

void Calculate(Array* Polinom, void* x)
{
	int i;
	switch (Polinom->el_size)
	{
		case sizeof(int) :
		{
			int xh;
			int result = 0;
			
			for (i = Polinom->degree; i >= 0; i--)
			{
				xh = (int)pow(*((int*)x), i);
				result += *((int*)Polinom->buffer + i) * xh;
			}
			printf("Result of calculating: P(%d)(%d) = %d\n\n", Polinom->degree, *((int*)x), result);
			break;
		}
		case sizeof(double) :
		{
			double xh;
			double result = 0;

			for (i = Polinom->degree; i >= 0; i--)
			{
				xh = (double)pow(*((double*)x), i);
				result += *((double*)Polinom->buffer + i) * xh;
			}
			printf("Result of calculating: P(%d)(%lf) = %lf\n\n", Polinom->degree,  *((double*)x), result);
			break;
		}
	}
}