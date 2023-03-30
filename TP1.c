// compiler :
// mpicc -o nomexec nomfich.c
//mpirun -np nbreproc nomexec       peut-etre ./ si pbm

//EXEMPLE 1

/*#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int rang, nb_proc, code;
    code=MPI_Init(&argc,&argv);
    code=MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code=MPI_Comm_rank(MPI_COMM_WORLD,&rang);
    if(code!=MPI_SUCCESS)
        printf("erreur \n");
    else
        printf("je suis le processeur %d parmi %d \n", rang, nb_proc);
    code=MPI_Finalize();
    exit(0);
}
*/


//EXEMPLE 2


/*
#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int rang, nb_proc, code, valeur, tag ,i;
    MPI_Status statut;
    code=MPI_Init(&argc,&argv);
    code=MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code=MPI_Comm_rank(MPI_COMM_WORLD,&rang);
    tag=100;
    valeur=1000;

    if(rang == 0)
    {
        MPI_Send(&valeur,1,MPI_INT,1,tag, MPI_COMM_WORLD);
        printf("Moi, processus %d jai envoyé %d au processus 1 \n", rang,valeur);
    }
    else if (rang==1)
    {
        MPI_Recv(&valeur,1,MPI_INT,0,tag,MPI_COMM_WORLD,&statut);
        printf("Moi, processus %d jai reçu %d au processus 1 \n", rang,valeur);

    }

    code=MPI_Finalize();
    exit(0);

}
*/

//EXERCICE 1-----------------------------------------------------------------------------------------------------------------------------------
/*
#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

    int rang, nb_proc, code, valeur, tag ,i;

    MPI_Status statut;
    code=MPI_Init(&argc,&argv);
    code=MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code=MPI_Comm_rank(MPI_COMM_WORLD,&rang);
    tag=100;
    valeur=1000;

    int N=100;

    double debut = MPI_Wtime();

    for(int j = 0; j<N;j++)
    {
            if(rang == 0)
        {
            MPI_Send(&valeur,1,MPI_INT,1,tag, MPI_COMM_WORLD);
            //printf("Moi, processus %d jai envoyé %d au processus 1 \n", rang,valeur);
        }
        else if (rang==1)
        {
            MPI_Recv(&valeur,1,MPI_INT,0,tag,MPI_COMM_WORLD,&statut);
            //printf("Moi, processus %d jai reçu %d au processus 1 \n", rang,valeur);

        }

    }

    double fin = MPI_Wtime();

    //printf("début = %f  \n", debut);
    //printf("fin = %f \n", fin);
    printf("temp tot = %f \n", fin-debut);

    code=MPI_Finalize();
    exit(0);

}
*/

//EXERCICE 2-----------------------------------------------------------------------------------------------------------------------------------

/*
#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

    int rang, nb_proc, code, valeur, tag ,i;

    MPI_Status statut;
    code=MPI_Init(&argc,&argv);
    code=MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code=MPI_Comm_rank(MPI_COMM_WORLD,&rang);
    tag=100;
    

    int N=10;

    double debut = MPI_Wtime();

    valeur = 0;

    for(int j = 0; j<N;j++)
    {
        valeur+=1;
        
            if(rang == 0)
        {
            MPI_Send(&j,1,MPI_INT,1,tag, MPI_COMM_WORLD);
            printf("Moi, processus %d jai envoyé %d au processus 1 \n", rang,valeur);
            MPI_Recv(&j,1,MPI_INT,1,tag,MPI_COMM_WORLD,&statut);
            printf("Moi, processus %d jai reçu %d au processus 1 \n", rang,valeur);
        }
        else if (rang==1)
        {
            MPI_Recv(&j,1,MPI_INT,0,tag,MPI_COMM_WORLD,&statut);
            printf("Moi, processus %d jai reçu %d au processus 1 \n", rang,valeur);
            MPI_Send(&j,1,MPI_INT,0,tag, MPI_COMM_WORLD);
            printf("Moi, processus %d jai envoyé %d au processus 1 \n", rang,valeur);

        }

    }

    double fin = MPI_Wtime();

    printf("temp tot = %f \n", fin-debut);

    code=MPI_Finalize();
    exit(0);

}
*/


//EXERCICE 3-----------------------------------------------------------------------------------------------------------------------------------


/*
#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int rang, nb_proc, code, valeur, tag ,i;
    MPI_Status statut;
    code=MPI_Init(&argc,&argv);
    code=MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code=MPI_Comm_rank(MPI_COMM_WORLD,&rang);
    tag=100;
    valeur=1000;

    if(rang == 0)
    {
        for(int j = 1 ; j<nb_proc; j++)
        {
            valeur = 1; // 1 signifie prêt
            MPI_Recv(&valeur,1,MPI_INT,j,tag,MPI_COMM_WORLD,&statut);
            printf("Moi, processus %d jai reçu %d au processus %d \n", rang,valeur,j);

        }

        for(int j = 1 ; j<nb_proc; j++)
        {
            valeur = 2; // 2 signifie synchrone
            MPI_Send(&valeur,1,MPI_INT,j,tag, MPI_COMM_WORLD);
            printf("Moi, processus %d jai envoyer %d au processus %d \n", rang,valeur,j);

        }

    }
    else
    {



            valeur = 1;
            MPI_Send(&valeur,1,MPI_INT,0,tag, MPI_COMM_WORLD);
            printf("Moi, processus %d jai envoyer %d  \n", rang,valeur);

            valeur = 2;
            MPI_Recv(&valeur,1,MPI_INT,0,tag,MPI_COMM_WORLD,&statut);
            printf("Moi, processus %d jai reçu %d au processus 0 \n", rang,valeur);
        


    }

    code=MPI_Finalize();
    exit(0);

}*/


//EXERCICE 4-----------------------------------------------------------------------------------------------------------------------------------


/* #include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

    int rang, nb_proc, code, valeur, tag ,i;

    MPI_Status statut;
    code=MPI_Init(&argc,&argv);
    code=MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code=MPI_Comm_rank(MPI_COMM_WORLD,&rang);
    tag=100;
    valeur=0;

    if(rang == 0)
    {
        MPI_Send(&valeur,1,MPI_INT,1,tag, MPI_COMM_WORLD);
        printf("Moi, processus %d jai envoyer %d au processus 1 \n", rang,valeur);
    }
    else if(rang == nb_proc-1)
    {
        MPI_Recv(&valeur,1,MPI_INT,rang-1,tag,MPI_COMM_WORLD,&statut);
        printf("Moi, processus %d jai reçu %d \n", rang,valeur);

        valeur = valeur +1;

        MPI_Send(&valeur,1,MPI_INT,0,tag, MPI_COMM_WORLD);
        printf("Moi, processus %d jai envoyer %d au processus 0 \n", rang,valeur);

    }
    else
    {

        MPI_Recv(&valeur,1,MPI_INT,rang-1,tag,MPI_COMM_WORLD,&statut);
        printf("Moi, processus %d jai reçu %d \n", rang,valeur);

        valeur = valeur +1;

        MPI_Send(&valeur,1,MPI_INT,rang+1,tag, MPI_COMM_WORLD);
        printf("Moi, processus %d jai envoyer %d au processus %d \n", rang,valeur,rang+1);

    }

    code=MPI_Finalize();
    exit(0);

}*/


//EXERCICE 5-----------------------------------------------------------------------------------------------------------------------------------

/* #include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

    int rang, nb_proc, code, valeur, tag ,i;

    MPI_Status statut;
    code=MPI_Init(&argc,&argv);
    code=MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code=MPI_Comm_rank(MPI_COMM_WORLD,&rang);
    tag=100;
    valeur=0;

    int tabSuivant[] = {1,4,3,5,6,0,7,2};
    int tabPrecedent[] = {5,0,7,2,1,3,4,6};


    if(rang == 0)
    {
        MPI_Send(&valeur,1,MPI_INT,tabSuivant[rang],tag, MPI_COMM_WORLD);
        printf("Moi, processus %d jai envoyer %d au processus 1 \n", rang,valeur);

        MPI_Recv(&valeur,1,MPI_INT,tabPrecedent[rang],tag,MPI_COMM_WORLD,&statut);
        printf("Moi, processus %d jai reçu %d \n", rang,valeur);
    }
    else
    {

        MPI_Recv(&valeur,1,MPI_INT,tabPrecedent[rang],tag,MPI_COMM_WORLD,&statut);
        printf("Moi, processus %d jai reçu %d \n", rang,valeur);

        valeur = valeur +1;

        MPI_Send(&valeur,1,MPI_INT,tabSuivant[rang],tag, MPI_COMM_WORLD);
        printf("Moi, processus %d jai envoyer %d au processus %d \n", rang,valeur,tabSuivant[rang]);

    }

    code=MPI_Finalize();
    exit(0);

}
*/

//EXERCICE 6-1-----------------------------------------------------------------------------------------------------------------------------------

/*
#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

    int rang, nb_proc, code, valeur, tag ,i;

    MPI_Status statut;
    code=MPI_Init(&argc,&argv);
    code=MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code=MPI_Comm_rank(MPI_COMM_WORLD,&rang);
    tag=100;
    valeur=0;

    int tab[10] = {4,85,48,221,326,589,41,12,32,14};


    for (i=0;i<5;i++)
    {
        if(rang == 0)
        {
            MPI_Send(&tab[i],1,MPI_INT,1,tag, MPI_COMM_WORLD);
            printf("Moi, processus %d jai envoyer %d au processus 1 \n", rang, tab[i]);
        }
        else
        {

            MPI_Recv(&tab[i],1,MPI_INT,0,tag,MPI_COMM_WORLD,&statut);
            printf("Moi, processus %d jai reçu %d du processus 0 \n", rang, tab[i]);


        }
    }



    code=MPI_Finalize();
    exit(0);

}
*/

//EXERCICE 6-2-----------------------------------------------------------------------------------------------------------------------------------

/*
#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{

    int rang, nb_proc, code, valeur, tag ,i;

    MPI_Status statut;
    code=MPI_Init(&argc,&argv);
    code=MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code=MPI_Comm_rank(MPI_COMM_WORLD,&rang);
    tag=100;
    valeur=0;

    int N = 24;
    int tab[N];

    for(i=0 ; i<N ; i++)
    {
        tab[i] = rand() % 101;
    }

    int div2 = floor(N/nb_proc);
    int debut = 0;
    int fin = div2;
    int receveur = 0;

    for (i=0;i<N;i++)
    {
        receveur +=1;

        if (receveur >= nb_proc)
        {
            receveur = nb_proc-1;
        }



        for (i=debut; i<fin; i++)
        {
            

            if(rang == 0)
            {
                MPI_Send(&tab[i],1,MPI_INT,receveur,tag, MPI_COMM_WORLD);
                printf("Moi, processus %d jai envoyer %d au processus %d \n", rang, tab[i],receveur);
            }
            else
            {

                MPI_Recv(&tab[i],1,MPI_INT,0,tag,MPI_COMM_WORLD,&statut);
                printf("Moi, processus %d jai reçu %d du processus 0 \n", rang, tab[i]);


            }
        }

        debut = fin;
        fin =fin + div2;

        if(fin >= N)
        {
            fin = N-1;
        }

    }



    code=MPI_Finalize();
    exit(0);

}

*/

//Exemple de Diffusion

/*
#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{

    int rang, nb_proc, code, valeur;

    MPI_Status statut;
    code=MPI_Init(&argc,&argv);
    code=MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code=MPI_Comm_rank(MPI_COMM_WORLD,&rang);

    if(rang==0)
    {
        valeur=100;
    }

    MPI_Bcast(&valeur,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("Moi le proc %d j'ai reçu %d de 0 \n", rang,valeur);
    MPI_Finalize();
    return(0);

}
*/


//Exemple de Distribution

#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{

    int rang, nb_proc, code, nbre_valeur,taille,i;
    float somme, *valeurs, *donnees;
    MPI_Status statut;
    code=MPI_Init(&argc,&argv);
    code=MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code=MPI_Comm_rank(MPI_COMM_WORLD,&rang);
    nbre_valeur = 32;
    taille=nbre_valeur/nb_proc;
    donnees=(float*)malloc(taille*sizeof(float));
    if(rang==0)
    {
        valeurs = (float*)malloc(nbre_valeur*sizeof(float));
        for(i=0;i<nbre_valeur;i++)
        {
            valeurs[i]=(float)(100+i);
        }
        free(valeurs);
    }

    MPI_Scatter(valeurs,taille,MPI_FLOAT,donnees,taille,MPI_FLOAT,0,MPI_COMM_WORLD);
    somme = 0;
    for(i=0;i<taille;i++)
    {
        somme = somme + donnees[i];
        printf("moi proc %d j'ai reçu %.0fÃ %.0f du proc 0 et la somme est %.0f\n", rang, donnees[0],donnees[taille-1],somme);
    }
    
    free(donnees);

    MPI_Finalize();
    return(0);

}
