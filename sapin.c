#include <stdlib.h>
#include <unistd.h>

//Afficher le caractere indiqué en paramètre
void my_putchar(char *c)
{
    write(1, c, 1);
}

//Afficher la branche
//line : nombre de lignes de chaque branche
//column : nombre de caracteres maximum du sapin
//start : position du premier caractere étoile de la premiere ligne de la branche
void print_branches(int line, int column, int start)
{
    int i, j;
    char *c;

    //Texte en Couleur Verte
    write(1, "\033[0;32m", 8);
    //On balaye l'ensemble des lignes du tronc
    for (i = 0 ; i < line ; i++)
    {
        //On balaye l'ensemble des caractères de la base du sapin
        for (j = 0 ; j < column ; j++)
        {
            //On utilise la symétrie axiale du sapin
            //On place le symbole * de la position start jusqu'à son opposé
            if ((j >= start) && (j <= (column - 1 - start))) {
                c = "*";
            }
            else
            {
               c = " ";
            }
            my_putchar(c);
        }
        my_putchar("\n");
        //Temporisation
        usleep(75000);
        //On décrémente de 1 la position de la première occurence * pour la ligne suivante 
        start--; 
    }
    //Retour Couleur Normale
    write(1, "\033[0;37m", 8);
}

//Afficher le tronc
//line : nombre de lignes du tronc
//column : nombre de caracteres maximum du sapin
//start : position du premier caractere | du tronc
void print_trunk(int line, int column, int start)
{
    int i, j;
    char *c;

    //Texte en Couleur Orange
    write(1, "\033[0;33m", 8);
    //On balaye l'ensemble des lignes du tronc
    for (i = 0 ; i < line ; i++)
    {
        //On balaye l'ensemble des caractères de la base du sapin
        for (j = 0 ; j < column ; j++)
        {
            //On utilise la symétrie axiale du sapin
            //On place le symbole | de la position start jusqu'à son opposé
            if ((j >= start) && (j <= (column - 1 - start))) {
                c = "|";
            }
            else
            {
               c = " ";
            }
            my_putchar(c);
        }
        my_putchar("\n");
        //Temporisation
        usleep(75000);
    }
    //Retour Couleur Normale
    write(1, "\033[0;37m", 8);
}

//Nombre de lignes de la branche correspondant à la valeur size
int branches_lines(int size)
{
    return size + 3;
}

//Nombre de lignes du tronc correspondant à la taille du sapin
int trunk_lines(int size)
{
    return size;
}

//Nombre de caractères à afficher sur la premiere ligne d'une branche correspondant à la taille size
int branches_columns(int size)
{
    int line, ret, column, count;

    //Pour une taille de 1, on a une * sur la premiere ligne
    if (size == 1)
    {
        return 1;
    }
    //Pour les tailles autres que taille 1, on remarque que la premiere ligne de la branche n+1 équivaut à la x ieme ligne de la branche n
    ret = size / 2;
    //Détermine le nombre de ligne de la branche n-1
    size--;
    line = branches_lines(size) - ret;
    //Récursivité pour déterminer le nombre de caractères de la première ligne de la branche n qui dépend de la branche n-1
    column = branches_columns(size);    
    //On incrémente le nombre * correspondant à la ligne 
    count = 1;
    while (count < line)
    {
        column += 2;
        count++;
    }
    return column;
}

//Nombre de caracteres maximum du sapin
int sapin_columns(int size)
{
    int line, column, count;

    //On détermine le nombre de caractères de la première ligne de la dernière branche
    column = branches_columns(size);
    //On détermine le nombre de ligne de la dernière branche
    line = branches_lines(size);

    //On ajoute 2 caractères pour chaque lignes jusqu'à la dernière ligne de la branche
    count = 1;
    while(count < line)
    {
        column += 2;
        count++;
    }

    return column;
}


void sapin(int size)
{
    int line, base, start, trunk_size, i;

    //Cas de la taille nulle ou négative : on n'affiche rien
    if (size > 0)
    {
        //Calcul du nombre de caractères maximal du sapin = nb de caracteres de la dernière ligne de la derniere branche
        base = sapin_columns(size);
        
        /**************************************************************
        * BRANCHES
        *************************************************************/
        i = 1;
        //On boucle sur l'ensemble des branches du sapin en commançant par celle du haut (taille 1)
        while (i <= size)
        {
            //Calcul du nombre de lignes de la branche i 
            line = branches_lines(i);
            //Calcul de la position de la la première * de la première ligne de la branche i
            start = (base - branches_columns(i)) / 2;
            //Affichage de la branche i
            print_branches(line, base, start);
            i++;
        }

        /**************************************************************
        * TRONC
        *************************************************************/
        //Si la taille est paire, on ajuste la largeur du tronc à la largeur du nombre impair précédent
        if ((size % 2) == 1)
        {
            trunk_size = size;
        }
        else
        {
            trunk_size = size - 1; 
        }
        //Détermination de la position du premier caractere | du tronc
        start = (base - trunk_size) / 2;
        //Nombre de lignes du tronc
        line = trunk_lines(size);
        //Affichage du tronc
        print_trunk(line, base, start);
    }
    else{
        write(1, "The argument must be positive.\n", 31);
    }
}

int main(int argc, char const *argv[])
{
    int size;

    if (argc < 2)
        write(1, "Sapin takes its size as it first argument.\n", 43);
    else
    {
        size = atoi(argv[1]);
        sapin(size);
    }
    return 0;
}
