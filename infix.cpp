#include <iostream>
#include <string>

using namespace std;

int numb(string s, int step)
{
	int z=0;
	if ((s[step]>47)&&(s[step]<58))
	{
		z++;
		z=z+numb(s,step+1);
	}
	return z;
}

int prior(char s)
{
	int z=0;
	if ((s==43)||(s==45)) z=1;// + -
	if ((s==42)||(s==47)) z=2;// * /
	return z;
}

int main()
{
	string str;
	cin >> str;
	char *stack=new char [str.length()];
	char *queue=new char [str.length()*2];
	int top=-1,step=0,q=0;

	for (step;step<str.length();step++)
	{
		if (numb(str,step)>0)
		{
			for (int i=0; i<numb(str,step);i++)
			{
				*(queue+q)=str[step+i];
				q++;
			}
			*(queue+q)=32;
			q++;
			step=step+numb(str,step)-1;
			continue;
		}
		
		if (prior(str[step])>0)
		{
			if ((top==-1)||( *(stack+top)==40 ))
			{
				top++;
				*(stack+top)=str[step];
				continue;
			}

			if ( prior(str[step]) > prior( *(stack+top) ) )
			{
				top++;
				*(stack+top)=str[step];
				continue;
			}

			if (prior(str[step]) <= prior( *(stack+top) ) )
			{
				*(queue+q)=*(stack+top);
				q++; top--;step--;
				*(queue+q)=32;
				q++;
				continue;
			}

		}

		if (str[step]==40) 
		{
			top++;
			*(stack+top)=str[step];
			continue;
		}
		
		if (str[step]==41)
		{
			while (*(stack+top)!=40)
			{
				*(queue+q)=*(stack+top);
				q++;top--;
				*(queue+q)=32;
				q++;
			}
			top--;
			continue;
		}
	}

	for (top;top>-1;top--)
	{
		*(queue+q)=*(stack+top);
		q++;
		*(queue+q)=32;
		q++;
	}

	for (int i=0;i<q;i++)
	cout<<*(queue+i);

	delete [] stack;
	delete [] queue;
	system("pause");
	return 0;
}