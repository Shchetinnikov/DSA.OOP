#pragma once

/*
	The fast merge algorithm
	(connectivity problem)
*/

#include <iostream>
using namespace std;
static const int N = 10000;

void quickunion()
{
	int i, j, p, q, id[N];
	for (i = 0; i < N; i++) id[i] = i;
	while (cin >> p >> q)
	{
		for (i = p; i != id[i]; i = id[i]); // доходим до корня
		for (j = q; j != id[j]; j = id[j]); // доходим до корня
		if (i == j) continue;
		id[i] = j;
		cout << " " << p << " " << q << endl;
	}
}