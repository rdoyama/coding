#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

vector<int> PRIMES{2, 3};
int LAST_INDEX = 1;

bool isPrime(int n)
{
    int root = (int)sqrt((double)n);
    for (int i = 1; PRIMES[i] <= root; i++)
    {
        if (n % PRIMES[i] == 0)
            return false;
    }
    return true;
}

void fill_primes(int m, int n)
{
    if (PRIMES[LAST_INDEX] < n)
    {
        for (int i = PRIMES[LAST_INDEX] + 2; i <= n; i += 2)
        {
            if (((i + 1) % 6 != 0) && ((i - 1) % 6 != 0))
                continue;
            if (isPrime(i))
            {
                PRIMES.push_back(i);
                LAST_INDEX++;
            }
        }
    }
}

void print_primes(int m, int n)
{
    int i = 0;
    while ((PRIMES[i] != '\0') || (PRIMES[i] != 0))
    {
        if (PRIMES[i] == 0)
            break;
        if (m <= PRIMES[i] && PRIMES[i] <= n)
            cout << PRIMES[i] << endl;
        i++;
    }
}


int main() {
	int t;
	
	cin >> t;

    int m[t], n[t];
	for (int i = 0; i < t; i++)
	{
		cin >> m[i] >> n[i];
		fill_primes(m[i], n[i]);
    }
    for (int i = 0; i < t; i++)
	{
        print_primes(m[i], n[i]);
        cout << endl;
	}

	return 0;
}