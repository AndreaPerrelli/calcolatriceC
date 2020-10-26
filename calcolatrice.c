
/**
 *
 * @author Andrea Antonio Perrelli
 */

#include <stdio.h>
#include <conio.h>

const char * calcolatrice(unsigned int contatoreMax, char tipoOperazione);
float sommaArray(int arrayDaSommare[], int contatoreMax);
float sottraiArray(int arrayDaSottrarre[], int contatoreMax);
float dividiArray(int arrayDaDividere[], int contatoreMax);
float moltiplicaArray(int arrayDaMoltiplicare[], int contatoreMax);
char FunzioneTipoOperazione();
void *selezioneOperazione(unsigned int *numeroOperatori, char *tipoOperazione);

// Tipi di operazione disponibili per la calcolatrice.
static const char addizioneConst[] = "+";
static const char sottrazioneConst[] = "-";
static const char divisioneConst[] = "/";
static const char moltiplicazioneConst[] = "*";


int main () {

    //Due variabili per salvare gli operatori usati dalla calcolatrice.
    unsigned int operatoreUno = 0;
    unsigned int operatoreDue = 0;


    /*Variabile di tipo int usata per decidere se la calcolatrice deve 
    ancora continuare a fare calcoli o se si può terminare il programma.
    1 = Calcolatrice attiva.
    0 = Fine programma.
    */
    unsigned int statoCalcolatrice = 1;


    /*Variabile che salva risultato della calcolatrice, 
    puntatore che punta all'array di char restituito dalla funzione calcolatrice.*/
    const char *risultato;

    /*Variabile che salva tipo di operazione da effettuare e numero di operatori da usare.
    Puntatore che punta all'array di int restituito dalla funzione selezionaoperazione.*/
    char tipoOperazione;
    unsigned int numeroOperatori;

    while(statoCalcolatrice == 1) {
    printf("Menù tipi di calcolo disponibili: \n");
    printf("*********************************** \n");
    printf("Addizione: + \n" );
    printf("Sottrazione: - \n");
    printf("Divisione: / \n");
    printf("Moltiplicazione: * \n");
    printf("*********************************** \n");

    //Assegno valore restituito dalla funzione selezionaOperazione al puntatore arraySelezioneOperazioneRisultato.
    selezioneOperazione(&numeroOperatori, &tipoOperazione);
    
    //Estraggo i valori da arraySelezioneOperazioneRisultato, così da poterli mandare alla funzione calcolatrice.
    risultato = calcolatrice(numeroOperatori, tipoOperazione);
    
    //Stampo risultato dell'operazione.
    printf("%s\n", risultato);
    
    printf("Inserisci 1 se vuoi effettuare un altro calcolo, 0 se invece vuoi spegnere la calcolatrice. \n");
    scanf("%d", &statoCalcolatrice);
    }
    printf("Grazie per aver usato questa calcolatrice! Adesso puoi premere INVIO per chiudere il programma. Buona giornata!");

    /*Funzione richiamata che si occupa di tenere il programma
    finchè non viene premuto un tasto.*/
    getch();

   
    
    return 0;
}


/*Funzione che si occupa della selezione dell'operazione
  effettuata dalla calcolatrice, e del numero di operandi
  che la calcolatrice andrà a calcolare.*/
void *selezioneOperazione(unsigned int *numeroOperatori, char *tipoOperazione) {
    char tipoOperazioneTmp;
    int numeroOperatoriTmp;
    /*costrutto goto per ripetere esecuzione della funzione FunzioneTipoOperazione
     finchè l'utente non inserisce un tipo operazione corretto.*/
    LABEL:tipoOperazioneTmp = FunzioneTipoOperazione(tipoOperazioneTmp);
    if(tipoOperazioneTmp != addizioneConst[0] && tipoOperazioneTmp != sottrazioneConst[0] && tipoOperazioneTmp != divisioneConst[0] && tipoOperazioneTmp != moltiplicazioneConst[0]) {
        goto LABEL; 
    } else {
        printf("Con quanti numeri vuoi operare? \n");
        scanf("%d", &numeroOperatoriTmp);
        *tipoOperazione = tipoOperazioneTmp;
        *numeroOperatori = numeroOperatoriTmp;
    }  
    

}

/*Funzione che si occupa di recuperare il tipo operazione
  che la calcolatrice andrà ad usare, recuperandolo
  tramite input dell'utente.*/  
char FunzioneTipoOperazione() {
    char tipoOperazioneVar = "";
    printf("Quale tipo di operazione desideri effettuare?: \n");
    scanf("%c", &tipoOperazioneVar);
    return tipoOperazioneVar;
}

/*Funzione che si occupa dei calcoli di addizione, sottrazione
  divisione, e moltiplicazione, dei due operatori che vengono 
  inseriti in input dall'utente. La funzione ritorna un'array
  di char che corrisponde al risultato della calcolatrice più
  una frase che lo accompagna. 
  ES : "Il risultato della somma degli operatori è : " */
const char * calcolatrice(unsigned int contatoreMax, char tipoOperazione) {
    unsigned int contatore = 0;
    float somma = 0;
    float sottrazione = 0;
    float divisione = 0;
    int resto = 0;
    float moltiplicazione = 0;
    int arrayCalcoloRisultato[100];
    static char str[1024];

    for (contatore = 0; contatore < contatoreMax; contatore++) {
        printf("Scegli il valore dell'operatore %d \n", contatore);
        scanf("%d", &arrayCalcoloRisultato[contatore]);
    }

    if (tipoOperazione == addizioneConst[0]) {
        somma = sommaArray(arrayCalcoloRisultato, contatoreMax);
        snprintf(str, sizeof(str),"Il risultato della somma degli operatori è : %f", somma);
        return str;
    }
    if (tipoOperazione == sottrazioneConst[0]) {
        sottrazione = sottraiArray(arrayCalcoloRisultato, contatoreMax);
        snprintf(str, sizeof(str), "Il risultato della sottrazione degli operatori è : %f", sottrazione);
        return str;
    }

    if (tipoOperazione == divisioneConst[0]) {
        divisione = dividiArray(arrayCalcoloRisultato, contatoreMax);
        snprintf(str, sizeof(str), "Il risultato della divisione degli operatori è : %f", divisione);
        return str;
    }
    if (tipoOperazione == moltiplicazioneConst[0]) {
        moltiplicazione = moltiplicaArray(arrayCalcoloRisultato, contatoreMax);
        snprintf(str, sizeof(str), "Il risultato della moltiplicazione degli operatori è : %f", moltiplicazione);
        return str;
    }

       /* printf("Scelta sbagliata, riprovare.");
        return "Operazione non riconosciuta";
        break; */  
}



/* Funzione che si occupa del calcolo della somma dei numeri
   che vengono inseriti in input dall'utente.*/
float sommaArray(int arrayDaSommare[], int contatoreMax) {
    int contatore = 0;
    float somma = 0;
    for (contatore = 0; contatore < contatoreMax; contatore++) {
        somma += arrayDaSommare[contatore];
    }
    return somma;

/* Funzione che si occupa del calcolo della differenza dei numeri
   che vengono inseriti in input dall'utente.*/
}
float sottraiArray(int arrayDaSottrarre[], int contatoreMax) {
    int contatore = 0;
    float sottrazione = 0;
    float sottrazioneTmp = 0;
    int secondoCiclo = 0;
    for (contatore = 0; contatore < contatoreMax - 1; contatore++) {
        switch (secondoCiclo)
        {
        case 0:
            sottrazioneTmp = arrayDaSottrarre[contatore] - arrayDaSottrarre[contatore+1];
            sottrazione = sottrazioneTmp;
            secondoCiclo = 1;            
            break;

        case 1:
            sottrazioneTmp = sottrazione;
            sottrazioneTmp = sottrazione - arrayDaSottrarre[contatore+1];
            sottrazione = sottrazioneTmp;
            break;
        default:
            sottrazione = 0;
        break;
        }
    }
        
    return sottrazione;
}

/* Funzione che si occupa del calcolo del quoziente dei numeri
   che vengono inseriti in input dall'utente.*/
float dividiArray(int arrayDaDividere[], int contatoreMax) {
    int contatore = 0;
    float divisione = 0;
    float divisioneTmp = 0;
    int secondoCiclo = 0;
    for (contatore = 0; contatore < contatoreMax - 1; contatore++) {
        switch (secondoCiclo)
        {
        case 0 /* constant-expression */:
            divisioneTmp = arrayDaDividere[contatore] / arrayDaDividere[contatore + 1];
            divisione = divisioneTmp;
            secondoCiclo = 1;
            /* code */
            break;
         case 1:
            divisioneTmp = divisione;
            divisioneTmp = divisione / arrayDaDividere[contatore+1];
            divisione = divisioneTmp;
            break;
        default:
            divisione = 0;
            break;
        }
        
    }
    return divisione;
}

/* Funzione che si occupa del calcolo del prodotto dei numeri
   che vengono inseriti in input dall'utente.*/
float moltiplicaArray(int arrayDaMoltiplicare[], int contatoreMax) {
    int contatore = 0;
    float moltiplicazione = 0;
    float moltiplicazioneTmp = 0;
    int secondoCiclo = 0;
    for (contatore = 0; contatore < contatoreMax - 1; contatore++) {
        switch (secondoCiclo)
        {
        case 0 /* constant-expression */:
            moltiplicazioneTmp = (arrayDaMoltiplicare[contatore] * arrayDaMoltiplicare[contatore+1]);
            moltiplicazione = moltiplicazioneTmp;
            secondoCiclo = 1;
            break;
        case 1:
            moltiplicazioneTmp = moltiplicazione;
            moltiplicazioneTmp = moltiplicazione * arrayDaMoltiplicare[contatore+1];
            moltiplicazione = moltiplicazioneTmp;
            break;
        default:
            moltiplicazione = 0;
            break;
        }
    }
    return moltiplicazione;
}

