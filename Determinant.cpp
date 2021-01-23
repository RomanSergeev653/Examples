#include <iostream>
#include <fstream>
using namespace std;

int N;

int **change(int **B, int M)
{
    int **G;
    G = new int* [M];
    for (int i=0; i<M; i++)
        *(G+i)=new int [M];
        
    for (int i=0; i<M; i++)
        for (int j=0; j<M; j++)
            *(*(G+j)+i) = *(*(B+j)+i);

    B=G;

    return B;
}

int det(int M, int **B)
{
    B=change(B,M);

    int ans;
    if (M==1)
    {
        ans=**B;
    }
    if (M==2)
    {
        ans=(**B) * (*( *(B+1)+1 ) );//B[0][0]*B[1][1]
        ans=ans-(**(B+1) * (*( *(B+0) + 1 )));//B[0][1]*B[1][0]
    }
    if (M==3)
    {
        ans=          (**B) * (*(*(B+1)+1)) * (*(*(B+2)+2));//B[0][0]*B[1][1]*B[2][2]
        ans=ans+( (**(B+1)) * (*(*(B+2)+1)) * (*(*B+2)));//B[0][1]*B[1][2]*B[0][2]
        ans=ans+( (**(B+2)) * (*( *(B)+1) ) * (*(*(B+1)+2)));//B[0][2]*B[1][0]*B[2][1]

        ans=ans-( (**(B+2)) * (*(*(B+1)+1)) * (*( (*B)+2 )));//B[0][2]*B[1][1]*B[2][0]
        ans=ans-( (**(B+1)) * (*( (*B)+1 )) * (*(*(B+2)+2)));//B[0][1]*B[1][0]*B[2][2]
        ans=ans-(     (**B) * (*(*(B+2)+1)) * (*(*(B+1)+2)));//B[0][0]*B[1][2]*B[2][1]
    }

    for (int i=0; i<M; i++)
        delete [] *(B+i);
    delete [] B;
    return ans;
}

int laplas(int M,int **B)
{
    B=change(B,M);
    if ( (M==N)&&(M==1) )
    {
        int ans=**B;
        delete [] B;
        return ans;
    }

    int mn=0,mp=0,c;
    for (int i=0;i<M;i++)
    {
        c=0;
        for(int j=0;j<M;j++)
            if (*(*(B+j)+i)==0) 
                c++;
        if (c>mn)
        {
            mn=c;
            mp=i;
        }
    }
    bool t=0;
    for (int j=0;j<M;j++)
    {
        c=0;
        for(int i=0;i<M;i++)
            if (*(*(B+j)+i)==0) 
                c++;
        if (c>mn)
        {
            mn=c;
            mp=j;
            t=1;
        }
    }

    int d=0;
    bool lol=0;
    if (t)
    {
        for (int j=0;j<M;j++)
        {
            int **C;// создание масива для минора
            C=new int* [M-1];
            for (int k=0;k<M-1;k++)
                *(C+k)=new int [M-1];
            
            int kk=0;
            for (int k=0;k<M;k++) //минор
            {
                if (k==mp) continue;
                int ll=0;
                for (int l=0;l<M;l++)
                {
                    if (l==j) continue;
                    *(*(C+ll)+kk)=*(*(B+l)+k);
                    ll++;
                }
                kk++;
            }

            if ((M==N)&&(!lol)) //вывод первого минора
            {
                lol=1;
                for (int z = 0; z < M-1; z++)
                {
                    for (int x = 0; x < M-1; x++)
                        cout << *(*(C+x)+z) << " ";
                    cout << endl;
                }
            }

            if (M>5)
            {
                if ((j+mp)%2==1)
                    d= d - (*(*(B+mp)+j) * det(M-1,C));
                else
                    d= d + (*(*(B+mp)+j) * det(M-1,C));
            }

            else
            {
                if ((j+mp)%2==1)
                    d= d - (*(*(B+mp)+j) * laplas(M-1,C));
                else
                    d= d + (*(*(B+mp)+j) * laplas(M-1,C));
            }
            
            for (int k=0;k<M-1;k++) //удаление массива для минора
                delete [] *(C+k);
            delete [] C; 
        }
    }
    
    else
    {
        for (int j=0;j<M;j++)
        {
            int **C;// создание масива для минора
            C=new int* [M-1];
            for (int k=0;k<M-1;k++)
                *(C+k)=new int [M-1];

            int kk=0;
            for (int k=0;k<M;k++) //минор
            {
                if (k==mp) continue;
                int ll=0;
                for (int l=0;l<M;l++)
                {
                    if (l==j) continue;
                    *(*(C+ll)+kk)=*(*(B+l)+k);
                    ll++;
                }
                kk++;
            }

            if ((M==N)&&(!lol)) //вывод первого минора
            {
                lol=1;
                for (int z = 0; z < M-1; z++)
                {
                    for (int x = 0; x < M-1; x++)
                        cout << *(*(C+x)+z) << " ";
                    cout << endl;
                }
            }

            if (M<5)
            {
                if ((j+mp)%2==1)
                    d= d - (*(*(B+j)+mp) * det(M-1,C));
                else
                    d= d + (*(*(B+j)+mp) * det(M-1,C));
            }

            else
            {
                if ((j+mp)%2==1)
                    d= d - (*(*(B+j)+mp) * laplas(M-1,C));
                else
                    d= d + (*(*(B+j)+mp) * laplas(M-1,C));
            }
            
            
            for (int k=0;k<M-1;k++) //удаление массива для минора
                delete [] *(C+k);
            delete [] C; 
        }
    }
    
    for (int i=0; i<M; i++)
        delete [] *(B+i);
    delete [] B;

    return d;
}

int gaus(int **B)
{
    B=change(B,N);
    
    int r=1;
    for (int i=0; i<N-1; i++) //ступенчатый вид
    {
        for (int j=i+1; j<N; j++)
        {
            if ( *(*(B+i)+j) % *(*(B+i)+i) != 0) //домножение
                {
                    r = r * (*(*(B+i)+i));
                    for(int k=0; k<N; k++)
                    {
                        *(*(B+k)+j) = *(*(B+k)+j) * (*(*(B+i)+i));
                    }
                    cout << "(" << j << ") * " << *(*(B+i)+i) << endl;
                }

            cout <<"(" << j << ") - "<<*(*(B+i)+j) / *(*(B+i)+i)<< " * (" <<i<<")"<<endl;

            int io=(*(*(B+i)+j) / *(*(B+i)+i));
            for (int k=0; k<N; k++)
            {
                *(*(B+k)+j) -= *(*(B+k)+i) * io ;
            }
        }

        for(int x=0;x<N;x++)
        {
            for(int y=0;y<N;y++)
            {
                cout << *(*(B+y)+x) << " ";
            }
            cout << endl;
        }
        
    }
    
    int f=1;
    for (int i=0; i<N ; i++)
        f = f * (*(*(B+i)+i));

    for (int i=0; i<N; i++)
        delete [] *(B+i);
    delete [] B;
    
    return f/r;
}

int main()
{
    ifstream doc;
    doc.open("Test42.txt");
    if (!doc.is_open())
    {
        cout << "Error: file can't be opened";
        cin.get();
        return 0;
    }

    doc >> N;
    int **A;
    A=new int* [N];
    for (int i=0;i<N;i++)
        *(A+i)=new int [N];
    
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            doc >> *(*(A+j)+i);

    for (int i=0;i<N;i++) //вывод массива
    {
        for (int j=0;j<N;j++)
            cout << *(*(A+j)+i)<< " ";
    cout << endl; 
    }

    cout << endl << laplas(N,A) << endl << endl;

    if (N<4) cout << det(N,A) << endl << endl;

    cout << gaus(A) << endl << endl;

    for (int i=0; i<N; i++)
    {
        delete [] (*(A+i));
    }
    delete [] A;
    system("pause");
    return 0;
}
