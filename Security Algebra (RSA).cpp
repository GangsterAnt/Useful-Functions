#include < iostream>
#include <random>
#include <cmath>
#include <ctime>
#include <bitset>
#include <vector>
using namespace std;

/*
basic gcd computation,
euclid extended gcd ( Line 81) : for get multiply inverse (used  in m_inv : line 137)
2진 모듈로 거듭제곱법 ( binary modulo exponentiation) for fast a^b mod cal
Miller_Rabin test function Line : 198 ( prime test : line 166 )
keyverify (  Is P & Q are prime?    gcd(  pi_(P*Q) (오일러 파이.. == ( p-1) * (q-1)) , e) == 1 ( e 와 pi_n 이 서로소인가)
sign (Line 241  ,  m ^d (d is private key , m is plain text or text wants to be signatured ) mod n
verify (Line 246 ,   s^ e ( s is ciphertext or signatured text , e is public key) mod n == m  mod n ? 1: -3 )

*/
 int gcd( int a,  int b)
{
	if (a < b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	else if (a == b)
		return a;
	else if (b == 0)
		return a;
	else
		return gcd(b, a%b);
}

  unsigned int exp(int a,unsigned int b,int n)		//cal a^b mod n
{
	  unsigned int A = a;
	  unsigned int N = n;
	  A = A%n;

	  unsigned int arr[32] = { 0, };
		  int c = 0; long long f = 1;
		  unsigned int len = 0;
		  unsigned int temp = b;
		  while (1)
		  {
			  temp = temp >> 1;

			  if (temp > 0)
				  len++;
			  else
				  break;
			  
		  }

		 for (int i = 0; i < len+1; i++)
		  {
			  if  ( (b >> (len - i)&1))
			  arr[i] =1 ;
		  }


		  for (int i = 0; i < len+1; i++)
		  {
			   c = 2 * c;
			   f = (f*f) % N;

			   if ( arr[i] ==1)
			   {
			    c = c + 1;
			    f = (f*a) % N;
			   }
		  }

		
		  return f;
	  




	}



	




  long long* extended_euclid(unsigned int a, unsigned int b) //a >b
{
	  long long arr[3];
	if ( (a == b) || (b ==0))
	{
		arr[0] = 1;
		arr[1] = 0;
		arr[2] = a;

		return arr;
	}
	
	else
	{
		
		 long long x_1 = 1;
		 long long y_1 = 0;
		 long long r_1 = a;

		 long long x_2 = 0;
		 long long y_2 = 1;
		 long long r_2 = b;

		 long long q = r_1 / r_2;

		 long long x_t = x_1 - q * x_2;
		 long long y_t = y_1 - q * y_2;
		 long long r_t = r_1 - q * r_2;

		while( r_2 != 0)
		{
			
			q = r_1 / r_2;

			x_t = x_1 - q * x_2;
			y_t = y_1 - q * y_2;
			r_t = r_1 - q * r_2;

			x_1 = x_2;
			y_1 = y_2;
			r_1 = r_2;

			x_2 = x_t;
			y_2 = y_t;
			r_2 = r_t;

			
		}
		arr[0] = x_1;
		arr[1] = y_1;
		arr[2] = r_1;

		return arr;
	}
}

 unsigned int m_inv(unsigned int a, unsigned int n)
{
	 long long * arr;
	
	arr = extended_euclid(n, a%n); // n > a%n
	if (arr[2] != 1)//r_1 != 1
	{
		//cout << "No multiplication inverse\n";
		cout << "-2\n";
		exit(1);
	}

	else
	{
		while(1)
		{
			if (arr[1] < 0)
			{
				arr[1] = arr[1] + n;

			}
			return arr[1] % n;
		}
		
	}

}


bool test(int a, int n)
{
	int bits = n - 1;
	int temp = bits;

	int k = 0;
	int t = 0;

	while(temp >0)
	{ 
		k++;
		if (temp | 0 == 0)
			t++;
		temp = temp >> 1;
	}

	int u = (n - 1) >> t;
	//cout << a << " " << u << " " << n;
	unsigned int x = exp(a, u, n);
	for (int i = 0; i < t; i++)
	{
		unsigned int _x = x;
		x = (_x * _x) % n;
		if ((x == 1) && (_x != 1) && (_x != n - 1))
			return 1;
		if (x != 1)
			return 1;
		else
			return 0;
	}

}
bool miller_rabin(int n, int s)	//s 는 검사 횟수
{

	//prime == 0 composite ==1;
	if (n == 2)
		return 0;
	else if (n % 2 == 0)
		return 1;
	srand(( int)time(0));
	bool result;
	for (int i = 0; i < s; i++)
	{
		int a = (rand()%(n-2))+ 1;
		result = test(a, n);
		if (result == true)
			return 1;

	}
	return 0;
}



 unsigned int keyverify(unsigned int p, unsigned int q, unsigned int e)
{
	if (miller_rabin(p, 100) == 1 || miller_rabin(q, 100) == 1)
	{
		//P or Q is not prime
		cout << "-1\n";
		exit(1);
	}

	
	unsigned int pi_n = (p - 1)*(q - 1);
	if (1 == gcd(e, pi_n))
	{
		cout << '\n-2\n';
		exit(2);
	}
	 unsigned int d = m_inv(e, pi_n);
		return d;
}

 unsigned int sign(int m, unsigned int d, int n)
 {
	 return exp(m, d, n);
 }

  int verify(unsigned int m, unsigned int s,unsigned int e, int n)
 {
	 if (m% n == exp(s, e, n))
		 return 1;
	 else
	 {
		 return -3;
	 }
 }
