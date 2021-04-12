#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

#define E pow(M_E,-7)

using namespace std;

int evaluateSize()
{
    int x,y;
    cout<<"Podaj ilosc rownan: "; cin>>x;
    cout<<"Podaj ilosc niewiadomych: "; cin>>y;
    if (x != y)
    {
        cout<<"Ilosc rownan musi byc rowna ilosci niewiadomych, przerywam dzialanie programu...";
        return -1;
    }
    else
    {
        if (x<=0 or y<=0)
        {
            cout<<"Ilosc rownan i niewiadomych musi byc wieksza od 0, przerywam dzialanie programu...";
            return -1;
        }
        else
        {
            return x;
        }
    }
}

void enter(double **matrix, int *vectorSolution, int size)
{
    for (int i=0; i<size; i++)
    {
        cout<<endl<<"Rownanie "<<i<<": "<<endl;
        for (int j=0; j<=size; j++)
        {
            if (j<size)
            {
            if (j == 0) cout<<"  ";
            cout<<"x"<<j;
            cout<<" * ";
            cin>>matrix[i][j];
            if (j < size-1) cout<<"+ ";
            }
            if (j == size)
            {
                cout<<"     = ";
                cin>>matrix[i][j];
            }
        }
    }
    for(int i=0; i<size; i++)
    {
        vectorSolution[i]=i;
    }
}

void showMatrix(double **matrix, int *vectorSolution, int size)
{
     cout<<endl<<"Macierz"<<endl;
     for (int i=0; i<size; i++)
     {
         cout<<setw(11)<<"x"<<vectorSolution[i];
     }
     cout<<setw(11)<<"b";
     for (int i=0; i<size; i++)
    {
        cout<<endl;
        for (int j=0; j<=size; j++)
        {
            cout<<setw(12)<<matrix[i][j];
        }
    }
    cout<<endl<<endl;
}

void message()
{
    cout<<"Pojawilo sie a(kk) = 0. Krok nie jest wykonalny - macierz jest osobliwa i nie istnieje dokladnie jedno rozwiazanie ukladu. Przerywam dzialanie programu..."<<endl;
}

void kSwap(double **matrix, int *vectorSolution, int size, int k1, int k2)
{
    double temp;
    for (int i=0; i<size; i++)
    {
        temp = matrix[i][k1];
        matrix[i][k1] = matrix[i][k2];
        matrix[i][k2] = temp;
    }
    temp=vectorSolution[k1];
    vectorSolution[k1]=vectorSolution[k2];
    vectorSolution[k2]=temp;
}

void wSwap(double **matrix, int size, int w1, int w2)
{
    double temp;
    for (int i=0; i<=size; i++)
    {
        temp = matrix[w1][i];
        matrix[w1][i] = matrix[w2][i];
        matrix[w2][i] = temp;
    }
}

bool ifZero(double in)
{
    if (fabs(in) < E) return true;
    else return false;
}


void step(double **matrix, int size, int wk)
{
    double p=1;

    for (int i=wk+1; i<size; i++)
    {
        p=matrix[i][wk] / matrix[wk][wk];
        for (int j=wk; j<=size; j++)
        {
            matrix[i][j] -= p * matrix[wk][j];
        }
    }
}

void reset(double **matrix, int size)
{
    for (int i=1; i<size; i++)
    {
        for (int j=0; j<=size; j++)
        {
            if (ifZero(matrix[i][j])) matrix[i][j] = 0;
        }
    }
}

void resetVector(double *vectorSolution, int size)
{
    for (int j=0; j<size; j++)
    {
        if (ifZero(vectorSolution[j])) vectorSolution[j] = 0;
    }
}

void reverseProcedure(double **matrix, int *vectorSolution, int size)
{
    double result[size],suma=0,temp2;
    int temp,j;
    result[size-1]= matrix[size-1][size] / matrix[size-1][size-1];

    for (int i=size-2; i>=0; i--)
    {
        suma =0;
        for (int j=i+1; j<size; j++)
        {
            suma+= result[j] * matrix[i][j];
        }

        result[i] = (matrix[i][size] - suma) / matrix[i][i];
    }

    resetVector(result,size);

    for (int i=1; i<size; i++)
    {
        j=i;
        while (vectorSolution[j]<vectorSolution[j-1] and j>0)
        {
            temp=vectorSolution[j];
            vectorSolution[j]=vectorSolution[j-1];
            vectorSolution[j-1]=temp;

            temp2=result[j];
            result[j]=result[j-1];
            result[j-1]=temp2;

            j--;
        }
    }


    cout<<endl<<"Rozwiazanie"<<endl;
    for (int i=0; i<size; i++)
    {
        cout<<setw(11)<<"x"<<vectorSolution[i];
    }
    cout<<endl;
    for (int i=0; i<size; i++)
    {
       cout<<setw(12)<<result[i];
    }
    cout<<endl<<endl;


}

void basicGauss(double **matrix, int *vectorSolution, int size)
{
    cout<<endl<<"Podstawowy Gauss"<<endl;
    for (int k=0; k<size-1; k++)
    {
        if (ifZero(matrix[k][k]))
        {
            message();
            return;
        }
        step(matrix, size, k);
    }

    reset(matrix,size);
    showMatrix(matrix,vectorSolution, size);

    if (matrix[size-1][size-1] == 0)
    {
        if (matrix[size-1][size] != 0) cout<<"Uklad sprzeczny, brak rozwiazan"<<endl;
        else cout<<"Uklad nieoznaczony, nieskonczenie wiele rozwiazan"<<endl;
        return;
    }

    reverseProcedure(matrix,vectorSolution,size);

}

void columnGauss(double **matrix, int *vectorSolution, int size)
{
    cout<<endl<<"Gauss z wyborem elementu maksymalnego w kolumnie"<<endl;
    double maks=0;
    int kolumna=0;
    for (int k=0; k<size-1; k++)
    {
        kolumna=k;
        maks=fabs(matrix[k][k]);
        for (int j=k; j<size; j++)
        {
            if (fabs(matrix[k][j] > maks))
            {
                maks=fabs(matrix[k][j]);
                kolumna=j;
            }
        }
        if (kolumna != k) kSwap(matrix, vectorSolution, size, kolumna, k);
        if (ifZero(matrix[k][k]))
        {
            message();
            return;
        }
        step(matrix, size, k);
    }

    reset(matrix,size);
    showMatrix(matrix,vectorSolution, size);

    if (matrix[size-1][size-1] == 0)
    {
        if (matrix[size-1][size] != 0) cout<<"Uklad sprzeczny, brak rozwiazan"<<endl;
        else cout<<"Uklad nieoznaczony, nieskonczenie wiele rozwiazan"<<endl;
        return;
    }
    reverseProcedure(matrix,vectorSolution,size);
}

void fullGauss(double **matrix, int *vectorSolution, int size)
{
    cout<<endl<<"Gauss z pelnym wyborem elementu maksymalnego"<<endl;
    double maks=0;
    int kolumna=0,wiersz=0;
    for (int k=0; k<size-1; k++)
    {
        kolumna=k;
        wiersz=k;
        maks=fabs(matrix[k][k]);
        for (int j=k; j<size; j++)
        {
            for (int i=k; i<size; i++)
            {
                if (fabs(matrix[j][i]) > maks)
                {
                    maks=fabs(matrix[j][i]);
                    kolumna=i;
                    wiersz=j;
                }
            }
        }

        if (kolumna != k) kSwap(matrix, vectorSolution, size, kolumna, k);
        if (wiersz != k) wSwap(matrix, size, wiersz, k);

        if (ifZero(matrix[k][k]))
        {
            message();
            return;
        }
        step(matrix, size, k);
    }

    reset(matrix,size);
    showMatrix(matrix,vectorSolution, size);

    if (matrix[size-1][size-1] == 0)
    {
        if (matrix[size-1][size] != 0) cout<<"Uklad sprzeczny, brak rozwiazan"<<endl;
        else cout<<"Uklad nieoznaczony, nieskonczenie wiele rozwiazan"<<endl;
        return;
    }
    reverseProcedure(matrix,vectorSolution,size);
}

void example1(double **matrix, int *vectorSolution, int size)
{
    matrix[0][0]=1;
    matrix[0][1]=1;
    matrix[0][2]=0;
    matrix[0][3]=-3;
    matrix[0][4]=1;

    matrix[1][0]=1;
    matrix[1][1]=4;
    matrix[1][2]=-1;
    matrix[1][3]=-4;
    matrix[1][4]=-2;

    matrix[2][0]=0.5;
    matrix[2][1]=0.5;
    matrix[2][2]=-3;
    matrix[2][3]=-5.5;
    matrix[2][4]=1.5;

    matrix[3][0]=1.5;
    matrix[3][1]=3;
    matrix[3][2]=-5;
    matrix[3][3]=-9;
    matrix[3][4]=-0.5;


    for(int i=0; i<size; i++)
    {
        vectorSolution[i]=i;
    }
}

void example2(double **matrix, int *vectorSolution, int size)
{
    matrix[0][0]=2.25;
    matrix[0][1]=-2.5;
    matrix[0][2]=4;
    matrix[0][3]=-5.25;
    matrix[0][4]=-1;

    matrix[1][0]=-3;
    matrix[1][1]=-7.5;
    matrix[1][2]=6.5;
    matrix[1][3]=0;
    matrix[1][4]=17;

    matrix[2][0]=-6.25;
    matrix[2][1]=-12.5;
    matrix[2][2]=0.25;
    matrix[2][3]=5.25;
    matrix[2][4]=24.25;

    matrix[3][0]=9;
    matrix[3][1]=10;
    matrix[3][2]=7;
    matrix[3][3]=-21;
    matrix[3][4]=-33;

    for(int i=0; i<size; i++)
    {
        vectorSolution[i]=i;
    }
}

void exercise2(double **matrix, int *vectorSolution, int size)
{
    matrix[0][0]=1;
    matrix[0][1]=2;
    matrix[0][2]=-1;
    matrix[0][3]=2;
    matrix[0][4]=0;

    matrix[1][0]=1;
    matrix[1][1]=0;
    matrix[1][2]=-2;
    matrix[1][3]=4;
    matrix[1][4]=4;

    matrix[2][0]=0;
    matrix[2][1]=-3;
    matrix[2][2]=1.5;
    matrix[2][3]=7;
    matrix[2][4]=0;

    matrix[3][0]=0;
    matrix[3][1]=-1;
    matrix[3][2]=1;
    matrix[3][3]=6;
    matrix[3][4]=-1;

    for(int i=0; i<size; i++)
    {
        vectorSolution[i]=i;
    }

}

void exercise3(double **matrix, int *vectorSolution, int size)
{
    matrix[0][0]=14;
    matrix[0][1]=-13;
    matrix[0][2]=3;
    matrix[0][3]=-16;
    matrix[0][4]=-42;
    matrix[0][5]=-37;

    matrix[1][0]=3.5;
    matrix[1][1]=-18;
    matrix[1][2]=13;
    matrix[1][3]=-23.75;
    matrix[1][4]=-21;
    matrix[1][5]=-5.5;

    matrix[2][0]=3.5;
    matrix[2][1]=3;
    matrix[2][2]=-5.25;
    matrix[2][3]=9.25;
    matrix[2][4]=10.5;
    matrix[2][5]=12.5;

    matrix[3][0]=2;
    matrix[3][1]=14.5;
    matrix[3][2]=-10.5;
    matrix[3][3]=18.5;
    matrix[3][4]=21;
    matrix[3][5]=23.5;

    matrix[4][0]=1.5;
    matrix[4][1]=6.75;
    matrix[4][2]=-9.25;
    matrix[4][3]=17;
    matrix[4][4]=-10.5;
    matrix[4][5]=-45.25;


    for(int i=0; i<size; i++)
    {
        vectorSolution[i]=i;
    }

}

int main()
{
    int choice, size;

    cout<<"*********************************\n";
    cout<<"|                               |\n";
    cout<<"|  1. Dane zawarte w programie  |\n";
    cout<<"|  2. Wlasne dane wejsciowe     |\n";
    cout<<"|  3. Wyjscie                   |\n";
    cout<<"|                               |\n";
    cout<<"*********************************\n\n";
    cout<<"Wybor: ";
    cin>>choice;
    system("CLS");
    while(choice<1 || choice>3){
        cout<<"***** Wybierz poprawna opcje ****\n";
        cout<<"*********************************\n";
        cout<<"|                               |\n";
        cout<<"|  1. Dane zawarte w programie  |\n";
        cout<<"|  2. Wlasne dane wejsciowe     |\n";
        cout<<"|  3. Wyjscie                   |\n";
        cout<<"|                               |\n";
        cout<<"*********************************\n\n";
        cout<<"Wybor: ";
        cin>>choice;
        system("CLS");
    }
    if (choice == 2)
    {
        size = evaluateSize();
        if (size == -1) return 0;
        double **matrix = new double *[size];
        int *vectorSolution = new int[size];
        for (int i=0; i<size; i++)
        {
            matrix[i] = new double[size+1];
        }

        choice=0;
        cout<<"********************************************************\n";
        cout<<"|                                                      |\n";
        cout<<"|  1. Gauss Podstawowy                                 |\n";
        cout<<"|  2. Gauss z wyborem elementu maksymalnego w wierszu  |\n";
        cout<<"|  3. Gauss z pelnym wyborem elementu maksymalnego     |\n";
        cout<<"|                                                      |\n";
        cout<<"********************************************************\n\n";
        cout<<"Wybor: ";
        cin>>choice;
        system("CLS");
        while(choice<1 || choice>3){
            cout<<"************* Wybierz poprawna opcje *******************\n";
            cout<<"********************************************************\n";
            cout<<"|                                                      |\n";
            cout<<"|  1. Gauss Podstawowy                                 |\n";
            cout<<"|  2. Gauss z wyborem elementu maksymalnego w wierszu  |\n";
            cout<<"|  3. Gauss z pelnym wyborem elementu maksymalnego     |\n";
            cout<<"|                                                      |\n";
            cout<<"********************************************************\n\n";
            cout<<"Wybor: ";
            cin>>choice;
            system("CLS");
        }
        enter(matrix, vectorSolution, size);
        showMatrix(matrix, vectorSolution, size);
        if (choice == 1) basicGauss(matrix,vectorSolution, size);
        if (choice == 2) columnGauss(matrix,vectorSolution, size);
        if (choice == 3) fullGauss(matrix,vectorSolution, size);
        choice = 0;


        for (int i=0; i<size; i++)
        {
            delete [] matrix[i];
        }
        delete *matrix;
        return 0;
    }

    if (choice == 1)
    {
        choice=0;
        cout<<"************************\n";
        cout<<"|                      |\n";
        cout<<"|  1. Przyklad 10.1    |\n";
        cout<<"|  2. Przyklad 10.2    |\n";
        cout<<"|  3. Zadanie 10.2     |\n";
        cout<<"|  4. Zadanie 10.3     |\n";
        cout<<"|                      |\n";
        cout<<"************************\n\n";
        cout<<"Wybor: ";
        cin>>choice;
        system("CLS");
        while(choice<1 || choice>4){
            cout<<"*** Wybierz poprawna opcje ***\n";
            cout<<"******************************\n";
            cout<<"|                            |\n";
            cout<<"|      1. Przyklad 10.1      |\n";
            cout<<"|      2. Przyklad 10.2      |\n";
            cout<<"|      3. Zadanie 10.2       |\n";
            cout<<"|      4. Zadanie 10.3       |\n";
            cout<<"|                            |\n";
            cout<<"******************************\n\n";
            cout<<"Wybor: ";
            cin>>choice;
            system("CLS");
        }
        if (choice == 1) size=4;
        if (choice == 2) size=4;
        if (choice == 3) size=4;
        if (choice == 4) size=5;

        double **matrix = new double *[size];
        int *vectorSolution = new int[size];
        for (int i=0; i<size; i++)
        {
            matrix[i] = new double[size+1];
        }

        if (choice == 1) example1(matrix,vectorSolution,size);
        if (choice == 2) example2(matrix,vectorSolution,size);
        if (choice == 3) exercise2(matrix,vectorSolution,size);
        if (choice == 4) exercise3(matrix,vectorSolution,size);

        choice=0;
        cout<<"********************************************************\n";
        cout<<"|                                                      |\n";
        cout<<"|  1. Gauss Podstawowy                                 |\n";
        cout<<"|  2. Gauss z wyborem elementu maksymalnego w wierszu  |\n";
        cout<<"|  3. Gauss z pelnym wyborem elementu maksymalnego     |\n";
        cout<<"|                                                      |\n";
        cout<<"********************************************************\n\n";
        cout<<"Wybor: ";
        cin>>choice;
        system("CLS");
        while(choice<1 || choice>3){
            cout<<"************* Wybierz poprawna opcje *******************\n";
            cout<<"********************************************************\n";
            cout<<"|                                                      |\n";
            cout<<"|  1. Gauss Podstawowy                                 |\n";
            cout<<"|  2. Gauss z wyborem elementu maksymalnego w wierszu  |\n";
            cout<<"|  3. Gauss z pelnym wyborem elementu maksymalnego     |\n";
            cout<<"|                                                      |\n";
            cout<<"********************************************************\n\n";
            cout<<"Wybor: ";
            cin>>choice;
            system("CLS");
        }
        showMatrix(matrix, vectorSolution, size);
        if (choice == 1) basicGauss(matrix,vectorSolution, size);
        if (choice == 2) columnGauss(matrix,vectorSolution, size);
        if (choice == 3) fullGauss(matrix,vectorSolution, size);
        choice=0;

        for (int i=0; i<size; i++)
        {
            delete [] matrix[i];
        }
        delete *matrix;
        return 0;
    }
    if (choice == 3) return 0;
    return 0;
}
