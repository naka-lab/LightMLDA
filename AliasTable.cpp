#define _CRT_SECURE_NO_WARNINGS 1
#include "AliasTable.h"
#include "array.h"



CAliasTable::CAliasTable()
{
	m_pprobs = NULL;
	m_palias = NULL;
	m_len = 0;

	m_rand.Init();
}


CAliasTable::~CAliasTable()
{
	delete[] m_pprobs;
	delete[] m_palias;
}

int CAliasTable::sample()
{
	double rnd = m_rand.GetRandF() * (m_len-0.00001);
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
	m_large_block.clear();
	m_small_block.clear();

	//double *norm_prob = new double[len];
	if( m_len!=len )
	{
		delete[] m_pprobs;
		delete[] m_palias;
		m_pprobs = new double[len];
		m_palias = new int[len];
		m_len = len;
	}

	Normalize( prob, len, len, m_pprobs );

	// 大きい要素と小さい要素に分類
	for (int i = 0; i < len; i++)
	{
		if (m_pprobs[i] >= 1.0)
		{
			m_large_block.push_back( i );
		}
		else
		{
			m_small_block.push_back( i );
		}
	}

	// サイズが1のテーブルを作る
	while ( m_large_block.size()!=0 && m_small_block.size()!=0  )
	{
		int l = m_large_block.front();
		int s = m_small_block.front();

		m_large_block.pop_front();
		m_small_block.pop_front();

		// sにlの一部を足して1になるようする
		m_palias[s] = l;
		m_pprobs[l] -= (1.0 - m_pprobs[s]);

		if (m_pprobs[l] < 1.0 )
		{
			m_small_block.push_back(l);
		}
		else
		{
			m_large_block.push_back(l);
		}
	}
}