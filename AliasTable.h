#pragma once
#include "Rand.h"

class CAliasTable
{
public:
	CAliasTable();
	~CAliasTable();

	void BuildTable(double *prob, int len);
	int sample();


protected:
	int m_len;
	double* m_pprobs;
	int* m_palias;

	CRand m_rand;

	
};

