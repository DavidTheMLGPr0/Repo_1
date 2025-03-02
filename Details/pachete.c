#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct cartiere{
    int id;
    char *nume;
};

struct pachet{
    int id, adr[18], idCartier, str, nr, prio, codif;
    float weight;
    char *mesaj;
};

struct postas{
    int id, nrPachete, dist[101];
};

void citire(int *nrC, int *nrP, struct cartiere c[], struct pachet p[]){
    int cart, packets, i, j, l;
    char msj[101][101], name[101][101];
    //Numarul de cartiere
    scanf("%d", &cart);
    *nrC = cart;
    // Numele Cartierelor si completarea id-urilor cartierelor
    for(i = 0; i < cart; i++){
        scanf("%s\n", name[i]);
        l = strlen(name[i]);
        c[i].nume = (char *)malloc((l + 1)*sizeof(char));
        strcpy(c[i].nume, name[i]);
        c[i].id = i;
    }
    //Numarul Pachetelor
    scanf("%d", &packets);
    *nrP = packets;
    //Adresele, prioritatea, greutatea, mesajul si completarea id-urilor pachetelor
    for(i = 0; i < packets; i++){
        for(j = 0; j <= 17; j++){
            scanf("%d", &p[i].adr[j]);
        }
        scanf("%d%f", &p[i].prio, &p[i].weight);
        getchar();
        fgets(msj[i], 101, stdin);
        p[i].id = i;
        l = strlen(msj[i]);
        p[i].mesaj = (char *)malloc((l + 1)*sizeof(char));
        strcpy(p[i].mesaj, msj[i]);
    }
}

void task1(int nrC, int nrP, struct cartiere c[], struct pachet p[]){
    int i, j;
    //Afisez id-ul corespunzator numelui unui cartier
    for(i = 0; i < nrC; i++){
        printf("%d %s\n", c[i].id, c[i].nume);
    }
    for(i = 0; i < nrP; i++){
        printf("%d\n", p[i].id);
        //Ca sa nu existe spatiu dupa cel de-al 17-lea element, le afisez pe primele 16 si individual pe cel de-al 17-lea
        for(j = 0; j <= 16; j++){
            printf("%d ", p[i].adr[j]);
        }
        printf("%d\n", p[i].adr[17]);
        printf("%d %.3f\n", p[i].prio, p[i].weight);
        printf("%s", p[i].mesaj);
    }
}

int pow2(int nr){
    int p = 1, i;
    for(i = 1; i <= nr; i++)
        p *= 2;
    return p;
}

void task2(int nrP, struct cartiere c[], struct pachet p[], int test){
    int i, j;
    for(i = 0; i < nrP; i++){
        if(test == 1){
            printf("%d\n", p[i].id);
        }
        p[i].idCartier = p[i].str = p[i].nr = 0;
        //Completez cartierul si strada pachetelor
        for(j = 0; j <= 4; j++){
            if(p[i].adr[j] != 0){
                p[i].idCartier += pow2(4 - j);
            }
            if(p[i].adr[j + 5] != 0){
                p[i].str += pow2(4 - j);
            }
        }
        //Completez separat numarul pachetelor
        for(j = 0; j <= 7; j++){
            if(p[i].adr[j + 10] != 0){
                p[i].nr += pow2(7 - j);
            }
        }
        if(test == 1){
            printf("%d %d %d\n", p[i].idCartier, p[i].str, p[i].nr);
        }
    }
}

void task3(struct postas post[], struct pachet p[], struct cartiere c[], int nrP, int nrC, int test){
    int i, j, tmp;
    ///Initializez id-ul postasilor si numarul de pachete
    for(i = 0; i < nrC; i++){
        post[i].id = c[i].id;
        post[i].nrPachete = 0;
    }
    ///Determin numarul de pachete al fiecarui postas si retin id-ul pachetele care urmeaza sa fie distribuite
    for(i = 0; i < nrC; i++){
        for(j = 0; j < nrP; j++){
            if(post[i].id == p[j].idCartier){
                post[i].nrPachete++;
                tmp = post[i].nrPachete - 1;
                post[i].dist[tmp] = p[j].id;
            }
        }
    }
    if(test == 1){
        ///Afisarea id-ului postasului si al numarului de pachete care trebuie livrate, urmate de id-ul fiecarui pachet
        for(i = 0; i < nrC; i++){
            printf("%d %d\n", post[i].id, post[i].nrPachete);
            if(post[i].nrPachete != 0){
                for(j = 0; j < post[i].nrPachete - 1; j++){
                    printf("%d ", post[i].dist[j]);
                }
                printf("%d\n", post[i].dist[j]);
            }
        }
    }
}

void task4(struct postas post[], struct pachet p[], int nrC, int test){
    int i, j, k, var1, var2, tmp;
    ///Sortarea descrescatoare in functie de prioritate si ulterior de greutate
    for(i = 0; i < nrC; i++){
        for(j = 0; j < post[i].nrPachete - 1; j++){
            for(k = j + 1; k < post[i].nrPachete; k++){
                var1 = post[i].dist[j];
                var2 = post[i].dist[k];
                if(p[var1].prio < p[var2].prio){
                    tmp = post[i].dist[j];
                    post[i].dist[j] = post[i].dist[k];
                    post[i].dist[k] = tmp;
                }
                else if(p[var1].prio == p[var2].prio){
                    if(p[var1].weight < p[var2].weight){
                        tmp = post[i].dist[j];
                        post[i].dist[j] = post[i].dist[k];
                        post[i].dist[k] = tmp;
                    }
                }
            }
        }
    }
    ///Afisarea dupa sortare, la fel ca la task-ul 3
    if(test == 1){
        for(i = 0; i < nrC; i++){
            printf("%d %d\n", post[i].id, post[i].nrPachete);
            if(post[i].nrPachete != 0){
                for(j = 0; j < post[i].nrPachete - 1; j++){
                    printf("%d ", post[i].dist[j]);
                }
                printf("%d\n", post[i].dist[j]);
            }
        }
    }
}

void reverse(char sir[101]){
    fflush(stdin);
    int i = 0, j;
    char sir_nou[101], *p, cuv[101][101];
    p = strtok(sir, ".,!??: ");
    ///Pun toate cuvintele din sirul initial intr-o matrice de cuvinte
    while(p != NULL){
        strcpy(cuv[i], p);
        p = strtok(NULL, ".,!?: ");
        i++;
    }
    i -= 2;
    ///Pun toate elementele din matrice (adica toate cuvintele din sirul initial) in ordine inversa intr-un alt sir de caractere
    strcpy(sir_nou, cuv[i]);
    for(j = i - 1; j >= 0; j--){
        strcat(sir_nou, cuv[j]);
    }
    j = strlen(sir_nou);
    sir_nou[j] = '\0';
    strcpy(sir, sir_nou);
}

///Functia determina cel mai mare exponent al lui 2 care nu depaseste un anumit numar
int pow2max(int nr){
    int p = 1, exp = 0;
    while(p <= nr){
        p *= 2;
        exp++;
    }
    return exp - 1;
}

int task6(int id, int cod){
    int cp, cif[101], nrcif = 0, cp_id, i, okay = 0;
    cp = cod;
    ///Determin toate cifrele codului
    while(cp > 0){
        nrcif++;
        cif[nrcif] = cp % 10;
        cp /= 10;
    }
    ///Verific daca cel putin o cifra a codului se regaseste in id
    for(i = 1; i <= nrcif && okay == 0; i++){
        cp_id = id;
        while(cp_id > 0){
            if(cif[i] == cp_id % 10){
                okay = 1;
            }
            cp_id /= 10;
        }
    }
    ///Daca nicio cifra a codului nu se regaseste in id
    if(okay == 0){
        return cod;
    }
    else{
        int fac[101], nr = -1, check, biti[101], maxim;
        ///Gasirea factorilor primi ai id-ului
        if(id == 0 || id == 1){
            nr++;
            fac[nr] = id;
        }
        else if(id % 2 == 0){
            nr++;
            fac[nr] = 2;
        }
        for(i = 3; i <= id/2 && i <= 31; i += 2){
            okay = 1;
            if(id % i == 0){
                for(check = 3; check * check <= i && okay == 1; check += 2){
                    if(i % check == 0)
                        okay = 0;
                }
                if(okay == 0){
                    okay = 1;
                }
                else{
                    nr++;
                    fac[nr] = i;
                }
            }
        }
        ///Daca nu am gasit niciun factor prim al numarului, atunci clar numarul este prim si singurul factor prim este el insusi
        if(nr == -1){
            nr++;
            fac[nr] = id;
        }
        ///Determinarea bitilor
        maxim = pow2max(cod);
        if(fac[nr] > maxim){
            maxim = fac[nr];
        }
        for(i = 0; i <= maxim; i++){
            biti[i] = 0;
        }
        while(cod > 0){
            check = pow2max(cod);
            biti[check] = 1;
            cod -= pow2(check);
        }
        ///Inversarea bitilor care se afla pe pozitiile factorilor primi ai id-ului
        for(i = 0; i <= nr; i++){
            if(biti[fac[i]] == 1){
                biti[fac[i]] = 0;
            }
            else{
                biti[fac[i]] = 1;
            }
        }
        ///Reconstruirea codului
        for(i = 0; i <= maxim; i++){
            if(biti[i] == 1){
                cod += pow2(i);
            }
        }
        return cod;
    }
}

///Afisarea scorului fiecarui postas
void task7(int id, int nr, int tot){
    if(nr == 0){
        printf("%d 0.000\n", id);
    }
    else{
        printf("%d %.3f\n", id, (float) tot / nr);
    }
}

void task5(struct postas post[], struct pachet p[], int nrC, int test){
    int i, j, cod, k, MOD, tot;
    for(i = 0; i < nrC; i++){
        tot = 0;
        if(test == 1 || test == 0){
            ///Afisez id-ul postasului si cate pachete trebuie sa livreze
            printf("%d %d\n", post[i].id, post[i].nrPachete);
        }
        if(post[i].nrPachete != 0){
            for(j = 0; j < post[i].nrPachete; j++){
                cod = 0;
                if(test == 1 || test == 0){
                    ///Afisez id-ul pachetului
                    printf("%d ", post[i].dist[j]);
                }
                ///Inversez mesajul
                reverse(p[post[i].dist[j]].mesaj);
                ///Calculez codul
                for(k = 1; k < strlen(p[post[i].dist[j]].mesaj); k++){
                    cod += k * (int) p[post[i].dist[j]].mesaj[k];
                }
                ///Calcularea codului final
                MOD = p[post[i].dist[j]].str * p[post[i].dist[j]].nr + 1;
                cod = cod % MOD;
                p[post[i].dist[j]].codif = cod;
                if(test == 1){
                    ///Afisarea codului
                    printf("%d\n", cod);
                }
                else if(test == 0){
                    ///Trecerea la task-ul 6
                    printf("%d\n", task6(post[i].id, p[post[i].dist[j]].codif));
                }
                else if(test == -1){
                    ///Calcularea tuturor pachetelor livrate corect
                    cod = task6(post[i].id, p[post[i].dist[j]].codif);
                    if(cod == p[post[i].dist[j]].codif){
                        tot++;
                    }
                }
            }
        }
        if(test == -1){
            ///Afisarea scorului fiecarui postas
            task7(post[i].id, post[i].nrPachete, tot);
        }
    }
}

int main(){
    int task, nrC, nrP;
    struct cartiere c[101];
    struct pachet p[101];
    struct postas post[101];
    scanf("%d", &task);
    citire(&nrC, &nrP, c, p);
    if(task == 1){
        task1(nrC, nrP, c, p);
    }
    else if(task == 2){
        task2(nrP, c, p, 1);
    }
    else if(task == 3){
        task2(nrP, c, p, 0);
        task3(post, p, c, nrP, nrC, 1);
    }
    else if(task == 4){
        task2(nrP, c, p, 0);
        task3(post, p, c, nrP, nrC, 0);
        task4(post, p, nrC, 1);
    }
    else if(task == 5){
        task2(nrP, c, p, 0);
        task3(post, p, c, nrP, nrC, 0);
        task4(post, p, nrC, 0);
        task5(post, p, nrC, 1);
    }
    else if(task == 6){
        task2(nrP, c, p, 0);
        task3(post, p, c, nrP, nrC, 0);
        task4(post, p, nrC, 0);
        task5(post, p, nrC, 0);
    }
    else if(task == 7){
        task2(nrP, c, p, 0);
        task3(post, p, c, nrP, nrC, 0);
        task4(post, p, nrC, 0);
        task5(post, p, nrC, -1);
    }
}