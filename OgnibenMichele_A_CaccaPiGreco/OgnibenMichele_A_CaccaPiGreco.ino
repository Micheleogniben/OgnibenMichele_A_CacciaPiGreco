#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
                                    //  creazione variabili di INPUT
int  btn1;
int  btn2;
int  btn3;
int  btn4;
int  btn5;
int  btnStart;
                                    //  creazione variabili numeriche
int  vite;
int  punti;
int  tempo;
int  record;                        //  creazione di un nuovo carattere per il piGreco
byte piGreco[8] = { B00000, B00000, B11111, B01010, B01010, B01010, B01001, B00000 };
byte cuore[8]   = { B00000, B01010, B11111, B11111, B11111, B01110, B00100, B00000 };

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, piGreco);
  lcd.createChar(1, cuore);
                                    //  assegnazione variabili
  record   = 0;
  btn1     = 3;
  btn2     = 4;
  btn3     = 5;
  btn4     = 6;
  btn5     = 7;
  btnStart = 12;
                                    //  pinMode di input
  pinMode(btn1,     INPUT);
  pinMode(btn2,     INPUT);
  pinMode(btn3,     INPUT);
  pinMode(btn4,     INPUT);
  pinMode(btn5,     INPUT);
  pinMode(btnStart, INPUT);
}

void stampa(int vite, int punti) {
  lcd.clear();
  lcd.print("Vite:" + String(vite));
  lcd.setCursor(10 - String(punti).length(), 0);
  lcd.print("Punti:" + String(punti));
}

void avvisa(String f1, String f2) {
  lcd.clear();
  lcd.print(f1);
  lcd.setCursor(0, 1);
  lcd.print(f2);
  delay(2500);
  stampa(5, 0);
}

void stampaChar(char s, int incV, int incP, int incT, int incV1){
  stampa(vite, punti);
  delay(1500);
                                            //  Stampo il piGreco
  int var = (random(1, 6) * 3) - 2, pos = -1;
  lcd.setCursor(var, 1);
  lcd.write(s);
                                            //  Ciclo che continua fino a che non finisce il tempo o l'utente preme un bottone
  for (int i = 0; i < tempo; i++) {
    if      (digitalRead(btn1) == HIGH) { pos = 1;  break; }
    else if (digitalRead(btn2) == HIGH) { pos = 4;  break; }
    else if (digitalRead(btn3) == HIGH) { pos = 7;  break; }
    else if (digitalRead(btn4) == HIGH) { pos = 10; break; }
    else if (digitalRead(btn5) == HIGH) { pos = 13; break; }
    delay(1);
  }
  
  if (var == pos) {
    vite  += incV;
    punti += incP;
    if ((incT < 0 && tempo > 300) || incT > 0) {tempo += incT;}
  }else{
    vite  += incV1;
  }
}

void loop() {
  vite  = 5;
  punti = 0;
  tempo = 1200;
  lcd.clear();
  lcd.print("Premi per");
  lcd.setCursor(0, 1);
  lcd.print("iniziare");
                                            //  il ciclo continua fino a che non viene premuto il btn inizio
  while (digitalRead(btnStart)  == LOW) {}
                                            //  avviso l'utente che il gioco sta iniziando con un messaggio sull'lcd
  avvisa("Gioco iniziato", "preparati!");
                                            //  il ciclo si ripete fino a che l'utente non finisce le vite
  while (vite > 0) {
    
    if (random(1, 9) == 1) {                //  BONUS che esce con probabilità del 14% circa (1 volta su 8)
      stampaChar(1,  1, 1,  50,  0);
    } else if (random(1, 9) == 1) {         //  MALUS che esce con probabilità del 14% circa (1 volta su 8)
      stampaChar('M', -1, 0, -40,  0);
    } else {                                //  PIGRECO che esce come alternativa a BONUS e MALUS che escono con meno probabilità
      stampaChar(0,    0, 1, -40, -1);
    }
                                            //  se l'utente non ha ancora finito le vite aggiorno vite e punti, altrimenti notifico che ha perso
    if (vite > 0) { stampa(vite, punti); } 
    else { avvisa("Hai perso!", "Riprova"); }
  }
  lcd.clear();                              //  aggiorno il record in caso sia stato appena fatto
  if (punti > record) {
    record = punti;
    lcd.print("Nuovo record!");
    lcd.setCursor(0, 1);
  }
                                            //  stampo il record ogni fine turno per mostrarlo all'utente
  lcd.print("Record: " + String(record));
  delay(2500);
}
