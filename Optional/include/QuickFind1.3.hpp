#pragma once

/*
	Fast search algorithm
	(connectivity problem)
*/


#include <iostream>
using namespace std;
static const int N = 10000;

void quickfind()
{
	int i, p, q, id[N];
	for (i = 0; i < N; i++) id[i] = i;
	while (cin >> p >> q)
	{
		int t = id[p];
		if (t == id[q]) continue;
		for (i = 0; i < N; i++)
			if (id[i] == t)
				id[i] = id[q];
		cout << " " << p << " " << q << endl;
	}
}