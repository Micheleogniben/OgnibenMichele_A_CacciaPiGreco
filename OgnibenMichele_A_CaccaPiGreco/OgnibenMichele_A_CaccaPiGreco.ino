#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
                                            //  creazione variabili di INPUT
#define  btn1     3
#define  btn2     4
#define  btn3     5
#define  btn4     6
#define  btn5     7
#define  btnStart 12
                                            //  creazione variabili numeriche
int  vite;
int  punti;
int  tempo;
int  record;                                //  creazione di un nuovo carattere per il piGreco
byte piGreco[8] = { B00000, B00000, B11111, B01010, B01010, B01010, B01001, B00000 };
byte bonus[8]   = { B00000, B01010, B11111, B11111, B11111, B01110, B00100, B00000 };
byte malus[8]   = { B00000, B01110, B11111, B10101, B11111, B01010, B01110, B00000 };

void setup() {
  lcd.init();                               //  inizializzazione schermo lcd con modulo i2c
  lcd.backlight();
  lcd.createChar(0, piGreco);               //  creazione dei caratteri per lo schermo lcd di piGreco, bonus e malus
  lcd.createChar(1, bonus);
  lcd.createChar(2, malus);
                                            //  assegnazione variabili
  record   = 0;
                                            //  pinMode di input dei vari bottoni
  pinMode(btn1,     INPUT);
  pinMode(btn2,     INPUT);
  pinMode(btn3,     INPUT);
  pinMode(btn4,     INPUT);
  pinMode(btn5,     INPUT);
  pinMode(btnStart, INPUT);
}
                                            //  metodo per scrivere su lcd dati in input il messaggio, le coordinate di dove scriverlo ed un delay finale
void mex(String f1, String f2, int n1, int n2, int tempo) {
  lcd.clear();
  lcd.print(f1);
  lcd.setCursor(n1, n2);
  lcd.print(f2);
  delay(tempo);
}
                                            //  metodo per stampare il piGreco, bonus o malus
void stampaChar(char c, int incV, int incP, int incT, int t){
  mex("Vite:" + String(vite), "Punti:" + String(punti), 10 - String(punti).length(), 0, 1500);
                                            //  Stampo il piGreco
  int var = (random(1, 6) * 3) - 2, pos = -1;
  lcd.setCursor(var, 1);
  lcd.write(c);
                                            //  Ciclo che continua fino a che non finisce il tempo o l'utente preme un bottone
  for (int i = 0; i < t; i++) {
    if      (digitalRead(btn1) == HIGH) { pos = 1;  break; }
    else if (digitalRead(btn2) == HIGH) { pos = 4;  break; }
    else if (digitalRead(btn3) == HIGH) { pos = 7;  break; }
    else if (digitalRead(btn4) == HIGH) { pos = 10; break; }
    else if (digitalRead(btn5) == HIGH) { pos = 13; break; }
    delay(1);
  }
                                            //  if dove vengono incrementati / decrementati tempo, vite e punti
  if (var == pos) {
    vite  += incV;
    punti += incP;
    if ((incT < 0 && tempo > 300) || incT > 0) {tempo += incT;}
  }else{
    vite  -= incP;
  }
}

void loop() {                               //  ripristino vite, punti e tempo
  vite  = 5;
  punti = 0;
  tempo = 1200;
  mex("Premi per", "iniziare", 0, 1, 0);
                                            //  il ciclo continua fino a che non viene premuto il btn inizio
  while (digitalRead(btnStart)  == LOW) {}
                                            //  avviso l'utente che il gioco sta iniziando con un messaggio su schermo lcd
  mex("Gioco iniziato", "preparati!", 0, 1, 2500);
                                            //  una volta iniziato il gioco, comincio stampando le vite disponibili (5) ed i punti (0)
  mex("Vite:5", "Punti:0", 10 - String(punti).length(), 0, 0);
                                            //  il ciclo si ripete fino a che l'utente non finisce le vite
  while (vite > 0) {
    if (random(1, 9) == 1) {                //  ------- BONUS -------     esce con probabilità del 14% circa (1 volta su 8)
      stampaChar(1,  1, 0,  50, 1300);
    } else if (random(1, 9) == 1) {         //  ------- MALUS -------     esce con probabilità del 14% circa (1 volta su 8)
      stampaChar(2, -1, 0, -40, 1300);
    } else {                                //  ------ PIGRECO ------     esce come alternativa a BONUS e MALUS che escono con meno probabilità
      stampaChar(0,  0, 1, -40, tempo);
    }
                                            //  se l'utente non ha ancora finito le vite aggiorno vite e punti, altrimenti notifico che ha perso
    mex("Vite:" + String(vite),"Punti:" + String(punti), 10 - String(punti).length(), 0, 0); 
    if (vite == 0) { mex("Hai perso!", "Riprova", 0, 1, 2500); }
  }
                                            //  aggiorno il record in caso sia stato appena fatto e lo stampo
  if (punti > record) {
    record = punti;
    mex("Nuovo record!", "Record: " + String(record) + " pt", 0, 1, 2500);
  }
  else{                                     //  in caso l'utente non abbia fatto un record,stampo il punteggio appena fatto ed il record precedente
    mex("Punteggio: " + String(punti) + " pt", "Record: " + String(record) + " pt", 0, 1, 2500);
  }
}
