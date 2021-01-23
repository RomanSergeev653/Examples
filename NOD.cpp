#include <iostream>
using namespace std;

unsigned long long* common_div(unsigned long long *dx, unsigned long long x, int &size)
{
    if (x==1) 
    {
        dx = new unsigned long long;
        *dx = 1;
        size++;
        return dx;
    }

    for (int i=2; x>1; i++)
    {
        if (x%i == 0)
        {
            x = x/i;
            if (size != 0)
            {
                unsigned long long *cl;
                cl = new unsigned long long [size+1];

                for (int j=0; j<size; j++)
                    cl[j] = dx[j];
                delete [] dx;

                dx=cl;
                dx[size] = i;
            }
            else
            {
                dx = new unsigned long long;
                dx[0] = i;
            }

            size++;
            i--;
        }
    }

    return dx;
}

int main()
{
    system("chcp 65001");
    system("cls");
    unsigned long long n, m, *cn, *cm;
    string e;
    cout << "n = ";
    cin >> n;
    if (n==0) 
    {
        cout << "Введено неверное значение\n";
        delete [] cn;
        delete [] cm;
        system("pause");
        return 0;
    }

    cout << "m = ";
    cin >> m;
    if (m==0)  
    {
        cout << "Введено неверное значение\n";
        delete [] cn;
        delete [] cm;
        system("pause");
        return 0;
    }

    int size_n=0, size_m=0;
    cn = common_div(cn,n,size_n);
    cm = common_div(cm,m,size_m);
    
    int x=0, y=0;
    unsigned long long nod=1;
    while ( (x<size_n) && (y<size_m) )
    {
        if (cn[x]>cm[y])
        {
            y++;
            continue;
        }
        
        if (cm[y]>cn[x])
        {
            x++;
            continue;
        }

        if (cn[x]==cm[y])
        {
            nod=nod*cn[x];
            x++; y++;
            continue;
        }
    }
    cout <<"Наибольший общий делитель: "<< nod << endl;

    system("pause");
    delete [] cn;
    delete [] cm;
    return 0;
}
