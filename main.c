#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    void wypisanie(); // wypisuje posortowana liste
    void dodawanie(); // dodaje wpis
    void usuwanie();  //usuwa wpis po indeksie
    void dodajPlik(); // tworzy liste z pliku "lista.txt"
    int czyTele (char wyraz[]); //sprawdza czy to 9-cyfrowa liczba
    int wczytajInta();
    int czyDobry(char wyraz[]);
    void usunPierwszy();
    void usunOstatni();
    void usunSrodek(int numer); // usuwa strukture o danym numerze


struct osoba {
    char nazwisko[25];
    char imie1[25];
    char imie2[25];
    char miasto[25];
    char ulica[25];
    int nrdom[5];
    int nrmie[5];
    char telefon[10];
    struct osoba * nast;
} *poczatek;

int ileosob = 0;
int main()
{
    int a;
    dodajPlik();
    printf("------------- KSIAZKA TELEFONICZNA -------------\n");
    printf("------------- Autor: Michal Kurowski -------------\n\n");
     for (;;)
    {
        printf("Prosze wpisac liczbe:\n1\taby wyswietlic baze.\n2\taby dodac wpis.\n3\taby usunac wpis.\n4\taby zamknac program\n>");
        a = wczytajInta();
        switch (a)
        {
        case 1: wypisanie();
        break;
        case 2: dodawanie();
        break;
        case 3: usuwanie();
        break;
        case 4:
        printf("Koniec programu\n");
        exit(0);
        default: printf("Zla liczba\n>");
        }
    }
    return 0;
}

void dodajPlik() {
    struct osoba *aktualny, *poprzedni;
    FILE *fp;
    char buf[256];
       fp=fopen("lista.txt", "r");
    if( fp == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
   aktualny = (struct osoba *)malloc(sizeof(struct osoba));
   poczatek = aktualny;
  while (fgets (buf, sizeof(buf), fp))
    {
        ileosob++;
        strcpy(aktualny->nazwisko, strtok(buf, ","));
        strcpy(aktualny->imie1, strtok(NULL, ","));
        strcpy(aktualny->imie2, strtok(NULL, ","));
        strcpy(aktualny-> miasto, strtok(NULL, ","));
        strcpy(aktualny->ulica, strtok(NULL, ","));
        strcpy(aktualny->nrdom, strtok(NULL, ","));
        strcpy(aktualny->nrmie, strtok(NULL, ","));
        strcpy(aktualny->telefon, strtok(NULL, ","));

        poprzedni = aktualny;
        aktualny = (struct osoba *)malloc(sizeof(struct osoba));
        poprzedni ->nast = aktualny;

    }
    free(aktualny);
        poprzedni->nast = NULL;
    fclose(fp);
}

void wypisanie() {
    int i = 1;
    struct osoba *aktualny;
    aktualny = poczatek;
    while (aktualny != NULL) {
    printf ("---------------------------------------------\n");
    printf ("ID: %d\n",i);
    printf ("nazwisko:\t%s\n", aktualny->nazwisko);
    printf ("imie/ imiona:\t%s\t%s\n",aktualny->imie1, aktualny->imie2);
    printf ("Miejscowosc:\t%s\n",aktualny->miasto);
    printf ("Adres:\t\t%s\t%s\tm.%s\n",aktualny->ulica, aktualny->nrdom, aktualny->nrmie);
    printf ("Telefon:\t%s\n",aktualny->telefon);
    printf ("---------------------------------------------\n\n\n");
        aktualny = aktualny->nast;
    i++;
    }
}

void dodawanie()
{
    char napis[25];
    int liczba;
    struct osoba *aktualny,*nowy;
    nowy = (struct osoba *)malloc(sizeof(struct osoba));
        do // sprawdzenie czy nazwisko poprawne
    {
        printf("Podaj nazwisko. ( Zacznij wielka litera, uzyj do 24 znakow )\n>");
        fgets(napis, sizeof (napis), stdin);
    } while(czyDobry(napis));

    strcpy(nowy->nazwisko, napis);//kopiowanie nazwiska do struktury
        do // sprawdzenie czy imie1 poprawne
    {
        printf("Podaj pierwsze imie. ( Zacznij wielka litera, uzyj do 24 znakow )\n>");
        fgets(napis, sizeof (napis), stdin);
    } while(czyDobry(napis));
    strcpy(nowy->imie1, napis);//kopiowanie imienia do struktury

    do // sprawdzenie czy IMIE2 poprawne
        {
        printf("Podaj drugie imie. (Opcjonalne) ( Zacznij wielka litera, uzyj do 24 znakow )\n>");
        fgets(napis, sizeof (napis), stdin);
            if (napis[0] == '\n') //jesli enter to nie wpisuje imienia2
            {
                napis[0] = '\0';
                break;
            }

        } while(czyDobry(napis));
    strcpy(nowy->imie2, napis);//kopiowanie imienia do struktury

            do // sprawdzenie czy nazwisko poprawne
    {
        printf("Podaj miasto. ( Zacznij wielka litera, uzyj do 24 znakow )\n>");
        fgets(napis, sizeof (napis), stdin);
    } while(czyDobry(napis));
    strcpy(nowy->miasto, napis);//kopiowanie imienia do struktury

            do // sprawdzenie czy nazwisko poprawne
    {
        printf("Podaj ulice. ( Zacznij wielka litera, uzyj do 24 znakow )\n>");
        fgets(napis, sizeof (napis), stdin);
    } while(czyDobry(napis));
    strcpy(nowy->ulica, napis);//kopiowanie imienia do struktury

     do // wczytanie numeru domu
    {
        printf("Podaj numer domu ( uzyj do 4 cyfr)\n>");
        liczba = wczytajInta();
    } while(liczba<1 || liczba>9999);
    sprintf((nowy->nrdom), "%d", liczba); // zamiana liczby calkowitej na napis

     do // wczytanie numeru domu
    {
        printf("Podaj numer mieszkania ( uzyj do 4 cyfr)\n>");
        liczba = wczytajInta();
    } while(liczba<1 || liczba>9999);
    sprintf((nowy->nrmie), "%d", liczba); // zamiana liczby calkowitej na napis

    do // sprawdzenie czy ULICA poprawne
    {
        printf("Podaj telefon. ( napisz 9 cyfr )\n>");
        fgets(napis, sizeof (napis), stdin);
    } while(czyTele(napis));
    strcpy(nowy->telefon, napis);

    aktualny = poczatek;
    while(aktualny->nast != NULL && strcmp(nowy->nazwisko, aktualny->nast->nazwisko )>=0) //sprawdza czy kolejna struktura jest wieksza od nowej
    {
    aktualny = aktualny -> nast;
    }
    if (aktualny == poczatek) //dodawanie pierwszego wyrazu
        {
        nowy->nast = poczatek;
        poczatek = nowy;
        ileosob++;
        }
        else //dodawanie kolejnych wyrazow
            {
            nowy->nast = aktualny -> nast;
            aktualny ->nast = nowy;
            ileosob++;
            }

}

void usuwanie()
{
    int a;
    if (ileosob>0)
    {

    do{
    printf("Ktory wpis chcesz usunac? Wpisz liczbe od 1 do %d\n",ileosob);
    a = wczytajInta();
    }while (a<1 || a>ileosob);
    if (a==1) {usunPierwszy();} //usuwanie pierwszego
    else if (a==ileosob) {usunOstatni();}   //usuwanie ostatniego
    else usunSrodek(a);//usuwanie srodkowego wyrazu
    }
    else printf("baza jest pusta, nie ma co kasowac.\n");
}

int wczytajInta()
{
	int wejscie, flaga=0;

	while(!flaga) //wykonuj dopoki dane nie beda poprawne
	{
		if(!scanf("%d", &wejscie)) //jesli napis nie jest liczba to wyswietl
		{
			printf("Podaj dane ponownie.\n");
			while(getchar()!='\n');
		}
		else //jesli napis to liczba
		{
			char nastepny=getchar();
			if((nastepny<'0' || nastepny>'9')&& nastepny!='\n')  //sprawdzanie czy nie wpisano blednych znakow
			{
				printf("Mozliwy blad wejscia (wczytano %c).\nPodaj dane ponownie.\n", nastepny);
				while(getchar()!='\n');
			}
			else
			{
				flaga = 1;//konczenie petli while. wynik to wejscie
			}
		}
	}
	return wejscie;
};

int czyDobry(char wyraz[])
{
    int l=1;
	if (wyraz[0] >= 'A' && wyraz[0] <= 'Z' )
    {
        while (wyraz[l]!='\n')
            {
                if (wyraz[l] < 'a' || wyraz[l] > 'z' || l>24)
                {
                    printf("Uzywaj tylko liter a-z. Mozesz uzyc tylko 24 liter.\n");
                    return 1;
                }
                l++;
            }
    wyraz[l] ='\0';
    return 0;
    }
	else
	{
	printf ("Zacznij z duzej litery.\n");
    return 1;
	}
};

int czyTele(char wyraz[])
{
    int l=1;
	if (wyraz[9] == '\n' )//sprawdzenie czy ma 9 znakow
    {
        wyraz[9] = '\0';
        while (wyraz[l]!='\0') // sprawdzanie znakow az do dziewiatego
            {
                if (wyraz[l] < '0' || wyraz[l] > '9' ) //sprawdzenie czy to sa cyfry
                {
                    printf("Uzywaj tylko liczb.");
                    return 1; //jest zle
                }
                l++;
            }
    return 0;//jest dobrze
    }
	else // jesli nie ma dokladnie 9 znakow
	{
	printf ("Uzyj 9 cyfr.\n");
    return 1;//jest zle
	}
};

    void usunPierwszy()
    {
        struct osoba *zmienna;
        zmienna = (poczatek->nast); //bierze 2 strukture
        free (poczatek); //kasuje pierwsza strukture
        poczatek = zmienna; // ustawia poczatek na druga strukture
        ileosob = ileosob -1;
    }

    void usunOstatni()
    {
        struct osoba *aktualny, *usun;
        aktualny = poczatek;
        while (aktualny->nast->nast != NULL) //zatrzymuje sie na przedostatnim wyrazie
        {
        aktualny = aktualny -> nast;
        }
        usun = aktualny ->nast; //bierze ostatnia strukture
        free(usun);//usuwa ostatnia strukture
        aktualny ->nast = NULL;//w przedostatniej strukturze daje wskazanie na NULL
        ileosob = ileosob -1;
    }

    void usunSrodek(int numer)
    {
        struct osoba *aktualny, *usun;
        aktualny = poczatek;
        while (numer > 2) //zatrzymuje sie na wczesniejszej strukturze niz ta do usuniecia
        {
        aktualny = aktualny->nast;
        numer = numer -1;
        }
        usun = aktualny ->nast;
        aktualny ->nast = aktualny ->nast->nast;
        free (usun);
        ileosob = ileosob -1;
    }
