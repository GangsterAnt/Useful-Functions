#include<vector>
#include<string>
#include<iostream>

using namespace std;

vector<int> getPartialMatch(const string & N)
{
	int m = N.size();
	vector<int> pi(m, 0);

	int begin = 1;
	int matched = 0;

	while( begin + matched < m)
	{
		if (N[begin + matched] == N[matched])
		{
			++matched;
			pi[begin+matched-1 ]=matched;
		}
		else
		{
			if (matched == 0)
				++begin;
			else
			{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}

	}
	return pi;
}

vector<int> KMPsearch(const string & H, const string & N)
{
	int H_size = H.size(),	N_size = N.size();
	vector<int> pi = getPartialMatch(N);
	vector<int> ret;

	int begin = 0, matched = 0;

	while (begin + N_size <= H_size)
	{
		if (H[begin + matched] == N[matched])
		{
			++matched;
			if (matched == N_size)
				pi.push_back(begin);
		}

		else
		{
			if (matched == 0)
			{
				++begin; break;
			}

			else
			{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}

		}

	}

	return ret;

}
