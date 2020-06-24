#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
ifstream f("DFA.in");
ofstream g ("DFA.out");

struct automat
{

    int nr_stari_finale,nr_stari,cardinal_alfabet,nr_tranzitii;
    char alfabet[1000],stari[1000],stari_finale[1000],stare_initiala;
    int mat_tranzitie[100][1000];
    int cod_alfabet[10000],cod_stare[10000];

} DFA;

bool evaluate(automat DFA,char cuv[])
{
    if(strcmp(cuv,"$")==0)
        return 1;
    else
    {
        int stare_curenta;
        bool e_stare_finala[1000],ok=1;

        for(int i=0; i<DFA.nr_stari_finale; i++)
            e_stare_finala[DFA.cod_stare[DFA.stari_finale[i]]]=1;
        stare_curenta=DFA.cod_stare[DFA.stare_initiala];
        for(int i=0; i<strlen(cuv); i++)
        {

            stare_curenta=DFA.mat_tranzitie[stare_curenta][DFA.cod_alfabet[cuv[i]]];

            if(stare_curenta==-1) ///Daca matricea de tranzitie nu este initializata in acest punct
            {
                ///putem sa ne oprim,cuvantul nu va fi acceptat
                ok=0;
                break;
            }
        }
        if(e_stare_finala[stare_curenta]==0) ///Daca starea pe care ne-am uprit nu este finala,
            ///cuvantul nu va fi acceptat
            ok=0;
        return ok;
    }

}
char c,cuvant[10000];
char x,y;
int main()
{
    f>>DFA.nr_stari;
    for(int i=0; i<DFA.nr_stari; i++)
    {
        f>>DFA.stari[i];
        DFA.cod_stare[DFA.stari[i]]=i; ///Codificam literele cu cifre pentru a ne fi mai usor
        ///sa cream matricea de tranzitie
    }

    f>>DFA.cardinal_alfabet;

    for(int i=0; i<DFA.cardinal_alfabet; i++)
    {

        f>>DFA.alfabet[i];
        DFA.cod_alfabet[DFA.alfabet[i]]=i;
    }

    for(int i=0; i<DFA.nr_stari; i++)
        for(int j=0; j<DFA.cardinal_alfabet; j++)
            DFA.mat_tranzitie[i][j] = -1;

    f>>DFA.stare_initiala;

    f>>DFA.nr_stari_finale;


    for(int i=0; i<DFA.nr_stari_finale; i++)
        f>>DFA.stari_finale[i];



    f>>DFA.nr_tranzitii;
    for(int i=0; i<DFA.nr_tranzitii; i++)
    {
        f>>x>>c>>y;
        DFA.mat_tranzitie[DFA.cod_stare[x]][DFA.cod_alfabet[c]]=DFA.cod_stare[y];


    }


    while(f>>cuvant)
    {


        if(evaluate(DFA,cuvant)==1)
            g<<cuvant<<" - Este acceptat.\n";
        else
            g<<cuvant<<" - Nu este acceptat.\n";

    }


}
