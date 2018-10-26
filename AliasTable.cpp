#define _CRT_SECURE_NO_WARNINGS 1
#include "AliasTable.h"
#include "array.h"
#include <deque>


CAliasTable::CAliasTable()
{
	m_pprobs = NULL;
	m_palias = NULL;

	m_rand.Init();
}


CAliasTable::~CAliasTable()
{
	delete[] m_pprobs;
	delete[] m_palias;
}

int CAliasTable::sample()
{
	double rnd = m_rand.GetRandF() * m_len;
	int idx = int(rnd);
	double p = rnd - idx;

	if ( p<m_pprobs[idx] )
	{
		return idx;
	}
	else
	{
		return m_palias[idx];
	}
}


void CAliasTable::BuildTable(double *prob, int len)
{
	std::deque<int> large_block;
	std::deque<int> small_block;
	m_len = len;

	//double *norm_prob = new double[len];
	delete[] m_pprobs;
	delete[] m_palias;
	m_pprobs = new double[len];
	m_palias = new int[len];

	Normalize( prob, len, len, m_pprobs );

	// �傫���v�f�Ə������v�f�ɕ���
	for (int i = 0; i < len; i++)
	{
		if (m_pprobs[i] >= 1.0)
		{
			large_block.push_back( i );
		}
		else
		{
			small_block.push_back( i );
		}
	}

	// �T�C�Y��1�̃e�[�u�������
	while ( large_block.size()!=0 && small_block.size()!=0  )
	{
		int l = large_block.front();
		int s = small_block.front();


		large_block.pop_front();
		small_block.pop_front();

		// s��l�̈ꕔ�𑫂���1�ɂȂ�悤����
		m_palias[s] = l;
		m_pprobs[l] -= (1.0 - m_pprobs[s]);

		if (m_pprobs[l] < 1.0 )
		{
			small_block.push_back(l);
		}
		else
		{
			large_block.push_back(l);
		}
	}
}