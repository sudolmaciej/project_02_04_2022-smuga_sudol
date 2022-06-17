#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>


void generowanie_liczb(int n);

int wykladnicze_wysz(int *pInt, int n, int szukana);

int binarne_wysz(int *pInt, int i, int n, int szukana);

int main() {
    //Generowanie liczb i zapisywanie do tablicy
    printf("Podaj ilosc liczb w tablicy: ");
    int n;
    scanf("%d",&n);
    generowanie_liczb(n);
    //Wczytanie szukanej liczby

    printf("Podaj szukana liczbe: ");
    int szukana;
    scanf("%d",&szukana);
    //Otwarcie pliku w trybie odczytywania
    FILE *fp;
    fp = fopen("xd.txt", "r");
    int x;
    //tworzenie tablicy dynamicznej
    int *tab2 = NULL;
    tab2 = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        fscanf(fp,"%d",&x);
        tab2[i] = x;
    }
    //petla odczytujaca liczby z pliku i zapisujaca do tablicy
    
    //rozpoczecie mierzenia czasu
    int wynik;
    struct timeval begin, end;
    gettimeofday(&begin, 0);

    wynik = wykladnicze_wysz(tab2,n,szukana);

    gettimeofday(&end, 0);
    //zakonczenie mierzenia czasu
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    //podanie wyniku wyszukiwania
    if (wynik == -1)
        printf("Szukana liczba nie znajduje sie na liscie.\n");
    else
        printf("Szukana liczba znajduje sie na pozycji: %d.\n",wynik);

    printf("Operacja wyszukiwania trwala: %f sekund.",elapsed);
    //podanie wyniku wyszukiwania




    /*for (int i = 0; i < n; i++)
    {
        printf("%d  %d\n",i,tab2[i]);

    }*/

    fclose(fp);
    free(tab2);
    tab2 = NULL;
    return 0;
}


//funkcja void generujaca liczby i zapsisujaca do dynamicznej tablicy a nastepnie do pliku tekstowego
//otwieranie pliku tekstowego w trybie zapisywania
void generowanie_liczb(int n)
{

    srand(time(NULL));
    FILE *fp;
    fp = fopen("xd.txt","w");
    // tworzenie tablicy dynamicznej
    int *tab = NULL;
    tab = malloc(n * sizeof(int));
    //petla generujaca liczby z zakresu od 0 do 10 000 000
    for (int i = 0; i< n; i++)
    {
        int a = rand()%1001;
        int b = rand()%10000+1;
        tab[i] = a*b;
    }
    for (int i = 0; i < n; i++)
        //petla generujaca liczby z zakresu od 0 do 10 000 000
    {
        for (int j = 1; j < n-i; j++)
        {
            if (tab[j-1]>tab[j])
            {
                int tmp;
                tmp = tab[j];
                tab[j] = tab[j-1];
                tab[j-1] = tmp;
            }
        }
    }
    //petla generujaca liczby z zakresu od 0 do 10 000 000
    for (int i = 0; i < n; i++)
    {
        fprintf(fp,"%d\n",tab[i]);
    }
    //zamkniecie pliku i wyzerowanie tablicy dynamicznej
    fclose(fp);
    free(tab);
    tab = NULL;

}

//algorytm wyszukiwania oparty na Exponential Search
int wykladnicze_wysz(int tab2[],int n, int szukana)
{
    if (tab2[0] == szukana) //sprawdzenie czy pierwsza liczba w tablicy nie jest nasza szukana
        return 0;
    int poz = 1;    //pomocnicza zmienna dzieki ktorej bedziemy sprawdzac czy nasza szukana jest zmniejsza czy wieksza
    while (poz < n && tab2[poz] <= szukana) //petla ktora mnozy pomocnicza zmienna razy 2 dopoki nie bedzie wieksza od szukanej
    {
        poz = poz *2;
    }
    if (poz > n)    //sprawdzenie czy pomocnicza liczba nie wykracza poza ilosc naszych liczb w tablicy
        return binarne_wysz(tab2, poz/2, n,szukana);    //jezeli wykracza to zakres szukania binarnego jest od poz/2 do n
    else
        return binarne_wysz(tab2, poz/2, poz,szukana);  //jezeli nie to od poz/2 do poz
}


int binarne_wysz(int tab2[],int left, int right, int szukana)      //algorytm wyszukiwania binarnego
{
    //printf("left: %d right: %d",left,right);
    if (right >= left)
    {
        int sr = (left+right)/2;
        if (tab2[sr] == szukana)
            return sr;
        if (tab2[sr]> szukana)
            return binarne_wysz(tab2,left, sr-1, szukana);
        else
            return binarne_wysz(tab2, sr+1, right, szukana);
    }
    return -1;
}

int dod(int a, int b, FILE fp)
{

    printf("xd");
    int x;
    x = a+b;
    fprintf(&fp,"%d",x);
    return x;

}


