#include <iostream>
#include <ctime> //do losowania liczb pseudolosowych
#include <fstream> //do zapisu wyniku do pliku
#include <stdio.h> //do liczenia czasu
#include <chrono> // do liczenia czasu


using namespace std;

void wypelnianieTablicy(int t[], int rozmiar);
void sortowanieBabelkowe (int t[], int rozmiar);
void sortowanieZliczanie (int t[],int rozmiar);

ofstream plik;


int main()
{
    int rozmiarPobrany;
    cout<<"Podaj ilosc elementow do posortowania: "<<endl;
    cin>>rozmiarPobrany;
    const int rozmiar=rozmiarPobrany; //constans, bo rozmiar jest staly przez caly program
    int t[rozmiar];

    plik.open("wyniki.txt");

    wypelnianieTablicy(t,rozmiar);
    plik<<endl<<endl;
    sortowanieBabelkowe(t,rozmiar);
    plik<<endl;
    sortowanieZliczanie (t,rozmiar);


    plik.close();

    return 0;
}


// ** WYPE£NIANIE TABLICY LICZBAMI PSEUDOLOSOWYMI **
void wypelnianieTablicy(int t[], int rozmiar)
{
    srand(time(NULL)); // do losowania liczb pseudolosowych

    plik<<"Wylosowana tablica liczb:"<<endl;

    //wypelnienie tablicy liczbami losowymi z zakresu 1 - rozmiar-1
    for(int i = 0; i<rozmiar; i++)
    {
        t[i]=rand()%(rozmiar-1)+1;
        plik<<t[i]<<" ";
    }
}

void sortowanieBabelkowe (int t[], int rozmiar)
{
    auto begin = std::chrono::high_resolution_clock::now(); //poczatek liczenia czasu

    for(int i = 0; i < rozmiar - 1; i++)
        for(int j = 0; j < rozmiar - 1; j++)
            if(t[j] > t[j + 1])     //za pomoca petli for przegladamy elementy, jesli element o indeksie j-tym jest wiekszy od elementu od indeksie j-tym+1
                swap(t[j], t[j + 1]); // to zamieniamy je miejscami

    auto end = std::chrono::high_resolution_clock::now(); //koniec liczenia czasu
    double elapsed = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()); //czas obliczen - roznica konca i poczatku


// Wyświetlamy wynik sortowania
    plik<< "Sortowanie babelkowe:"<<endl;
    for(int i = 0; i < rozmiar; i++) plik<< t[i]<<" ";
    plik<<endl<<"Wykonano w: "<< elapsed/(1e9)<<" dla "<<rozmiar<<" elementow"<<endl;

    plik << endl;
}


void sortowanieZliczanie (int t[],int rozmiar)
{

    auto begin = std::chrono::high_resolution_clock::now(); //poczatek liczenia czasu

    int L[rozmiar]={0};
    int S[rozmiar]={0};

    for(int i = 0 ; i < rozmiar ; i++)
    L[t[i]]++;                              //tablica L-licznikow zlicza ile razy wystapil w tablicy element o indeksie i

    for(int i = 0 ; i < rozmiar ; i++)      //za pomoca tablicy L[i] ustalamy ostatnia pozycje w posortowanej tablicy
    L[i] = L[i] + L[i-1];                   //elementu z pod indeksu i - teraz stan licznika L nie jest iloscia wystepowania danej liczby
                                            // tylko ostatnia pozycja w tablicy

    for(int i = rozmiar-1 ; i >= 0 ; --i)   // wstawiamy elementu na odpowiednią pozycję do tablicy S
      S[--L[t[i]]] = t[i];                  // zmniejszajac ilosc Licznikow danej liczby z pod indeksu i


     auto end = std::chrono::high_resolution_clock::now(); //koniec liczenia czasu
    double elapsed = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()); //czas obliczen - roznica konca i poczatku


     plik<< "Sortowanie przez zliczanie:"<<endl;
    for(int i = 0; i < rozmiar; i++) plik<< S[i]<<" ";
    plik<<endl<<"Wykonano w: "<< elapsed/(1e9)<<" dla "<<rozmiar<<" elementow"<<endl;

    plik << endl;
}
