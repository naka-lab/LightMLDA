#pragma once
#include "Rand.h"
#include <deque>

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
	
	std::deque<int> m_large_block;
	std::deque<int> m_small_block;

	CRand m_rand;

	
};

