#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// ------------------------------------------------------------------------------------------------------------ // 

// inilizzazioni 

const int RIG = 5;
const int COL = 5;
const char NAVE = 'N';
const char ACQUA = '-';
const char HIT = 'X';
const char MISS = 'O';

// ------------------------------------------------------------------------------------------------------------ //

// funzioni visualizzazzione tabelle

// funzione stampa la tabella bot

void StampaTabellaBot(char tabella[RIG][COL]){

  cout << endl;
  cout << "--BOT--" << endl;
  
  cout << "  ";
  for(int i = 0; i < COL; i++){

    cout << i << " ";
    
  }

  cout << endl;
  
  for(int i = 0; i < RIG; i++){

    cout << i << " ";
    
    for(int j = 0; j < COL; j++){

      if(tabella[i][j] != NAVE){
     
      cout << tabella[i][j] << " ";
      
      } else {

        cout << ACQUA << " ";
      }
    }

    cout << endl;
    
  }
}

// funzione stampa la tabella utente

void StampaTabellaUtente(char tabella[RIG][COL]){
  
  cout << endl;  
  cout << "--TU--" << endl;
  
  cout << "  ";
  for(int i = 0; i < COL; i++){

    cout << i << " ";
    
  }

  cout << endl;
  
  for(int i = 0; i < RIG; i++){

    cout << i << " ";
    
    for(int j = 0; j < COL; j++){

    cout << tabella[i][j] << " ";

    }

    cout << endl;
    
  }
}

// ------------------------------------------------------------------------------------------------------------ //

// funzioni riempimento tabella

// funzione riempimento tavola acqua

void RiempimentoTabella(char tabella[RIG][COL]){

  for(int i = 0; i< RIG; i++){
    for (int j = 0; j < COL; j++){

      tabella[i][j] = ACQUA;
      
    }
  }
}

// funzione inserimento navi random bot

void InserimentoNaviBot(char tabella[RIG][COL], int N_navi){

  srand(time(0)); // per generare sempre valori casuali con la funzione rand()
  
  int num_navi = 0;
  
  if(N_navi < RIG * COL){

    while(N_navi > num_navi){

      int x = rand() % RIG;
      int y = rand() % COL;

      if(tabella[x][y] != NAVE){

        tabella[x][y] = NAVE;

        num_navi++;

      }
    }
  }
}

// funzione inserimento navi utente

void InserimentoNaviUtente(char tabella[RIG][COL], int N_navi){

  int num_navi = 0;
  
  if(N_navi < RIG * COL){

    while(N_navi > num_navi){

      int x;
      int y;
      
      cout << "inserire le coordinate della " << num_navi + 1 << "° nave: ";
      cin >> x >> y;

      if(tabella[x][y] == NAVE){

      cout << "giè inserita" << endl;

      } else if(tabella[x][y] == ACQUA){

      cout << "posizionata!" << endl;

      tabella[x][y] = NAVE;

      num_navi++;
      
      } else {

      cout << "questa casella o è già stata colpita o non è valida" << endl;

      }
    }
  }
}

// ------------------------------------------------------------------------------------------------------------ // 

// funzioni attacco e difesa

// funzione attacco giocatore

bool AttaccoGiocatore(char tabella[RIG][COL], int x, int y){

  if(tabella[x][y] == NAVE){

    cout << "colpito!" << endl;

    tabella[x][y] = HIT;

    return true;
    
  } else if(tabella[x][y] == ACQUA){

    cout << "mancato!" << endl;

    tabella[x][y] = MISS;

    return false;
    
  } else {

    cout << "questa casella o è già stata colpita o non è valida" << endl;

    return false;
    
  }
}

// funzione attacco bot

bool AttaccoBot(char tabella[RIG][COL]){
    
  srand(time(0));
  
  int x = rand() % RIG;
  int y = rand() % COL;

  if(tabella[x][y] == NAVE){

    cout << "sei stato colpito!" << endl;

    tabella[x][y] = HIT;

    return true;
    
  } else if(tabella[x][y] == ACQUA){

    cout << "ti ha mancato!" << endl;

    tabella[x][y] = MISS;

    return false;
    
  }
}

// ------------------------------------------------------------------------------------------------------------ // 

// funzioni per verificarer se hai vinto o perso 

// funzione per controllare se le navi del bot sono state abattute 

bool NaviAbattuteBot(char tabella[RIG][COL], int &a){

  for(int i = 0; i < RIG; i++){
    for(int j = 0; j < COL; j++){

      if(tabella[i][j] == NAVE){

        return false;
        
      } 
    }
  }

  a = 1;
  return true;
  
}

// funzione per controllare se le navi dell'utente sono state abattute 

bool NaviAbattuteUtente(char tabella[RIG][COL], int &a){

  for(int i = 0; i < RIG; i++){
    for(int j = 0; j < COL; j++){

      if(tabella[i][j] == NAVE){

        return false;
        
      } 
    }
  }

  a = 0;
  return true;
  
}

// ------------------------------------------------------------------------------------------------------------ // 

// funzione centrale

int main(){
    
    char TabellaUtente[RIG][COL];
    char TabellaBot[RIG][COL];
    
    int x, y, a = 2;
    
    int numero_navi;
    
    cout << "inserisci il numero di navi: ";
    cin >> numero_navi;
    
    RiempimentoTabella(TabellaUtente);
    RiempimentoTabella(TabellaBot);
    
    cout << "Benvenuti nel gioco della battaglia navale!" << endl;
    
    InserimentoNaviBot(TabellaBot, numero_navi);
    InserimentoNaviUtente(TabellaUtente, numero_navi);
    
    while(!NaviAbattuteBot(TabellaBot, a) || !NaviAbattuteUtente(TabellaUtente, a)){
        
        StampaTabellaBot(TabellaBot);
        StampaTabellaUtente(TabellaUtente);
        
        cout << endl;
        cout << "--E' IL TUO TURNO--" << endl;
        
        cout << "inserire le coordinate dove attaccare(righe colonne): ";
        cin >> x >> y;
        
        AttaccoGiocatore(TabellaBot, x, y);
        
        cout << endl;
        cout << "--E' IL TURNO DEL BOT--" << endl;
        
        AttaccoBot(TabellaUtente);
        
        cout << endl;
        
    }
    
    if(a == 1){
        
        cout << "HAI VINTOOO!" << endl;
        
    } else {
        
        cout << "HAI PERSO..." << endl;
        
    }
}
