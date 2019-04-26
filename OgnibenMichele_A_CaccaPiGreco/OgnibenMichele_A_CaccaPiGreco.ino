#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
                                      //  variabili di INPUT
int btn1;
int btn2;
int btn3;
int btn4;
int btn5;
int btnStart;
                                      //  variabili numeriche
int vite;
int punti;
int tempo;
int record;


void setup(){
  lcd.init();
  lcd.backlight();
                                      //  bottoni
  btn1      = 7;
  btn2      = 6;
  btn3      = 5;
  btn4      = 4;
  btn5      = 3;
  btnStart  = 12;
  record    = 0;
                                      //  pinMode di input
  pinMode(btn1,      INPUT);
  pinMode(btn2,      INPUT);
  pinMode(btn3,      INPUT);
  pinMode(btn4,      INPUT);
  pinMode(btn5,      INPUT);
  pinMode(btnStart,  INPUT);
}


void stampa(String vite, String punti){
  lcd.print(vite);
  lcd.setCursor(10 - String(punti).length(), 0);
  lcd.print(punti);
}


void avvisa(String f1, String f2, int vite, int punti){
  lcd.clear();
  lcd.print(f1);
  lcd.setCursor(0, 1);
  lcd.print(f2);
  delay(2500);
  lcd.clear();
  stampa(vite, punti);
}


int posizione(String s){
  lcd.clear();
  stampa(vite, punti);
  delay(1500);
                                  //  Stampo il piGreco     
  int var = (random(1, 6)* 3) - 2;
  lcd.setCursor(var, 1);
  lcd.print(s);
  return var;
}

int premi(){
  int i = 0, premuto = 0;
                                  //  Ciclo che continua fino a che non finisce il tempo o l'utente preme un bottone
  while  (i < tempo){
    if      (digitalRead(btn1) == HIGH){premuto = 1;  break;}
    else if (digitalRead(btn2) == HIGH){premuto = 4;  break;}
    else if (digitalRead(btn3) == HIGH){premuto = 7;  break;}
    else if (digitalRead(btn4) == HIGH){premuto = 10; break;}
    else if (digitalRead(btn5) == HIGH){premuto = 13; break;}
    delay(1);
    i++;
  }
  return premuto;
}


void loop() {
  vite  = 5;
  punti = 0;
  tempo = 1200;
  lcd.print("Premi per");
  lcd.setCursor(0, 1);
  lcd.print("iniziare");
                                      //  btn inizio
  while(digitalRead(btnStart)  == LOW){}
  
  avvisa("Gioco iniziato", "preparati!", vite, punti);
  
  while(vite > 0){                    //  bonus che esce con probabilità del 14% circa (1 volta su 8)
    if (random(1, 9) == 1){
      int var = posizione("b"), premuto = premi();
      
      if (var == premuto){
        vite++; tempo += 50;
      }
      else{
        vite--;
      }
    }else if (random(1, 9) == 1){     //  malus che esce con probabilità del 14% circa (1 volta su 8)
      int var = posizione("m"), premuto = premi();
      
      if (var == premuto){
        vite--; punti--; 
        if (tempo > 250){tempo -= 40;}
      }
    }else{                            //  simbolo del pi greco
      int var = posizione("p"), premuto = premi();
      
      if (var == premuto){
        punti++;
        if (tempo > 250){tempo -= 40;}
      }
      else{
        vite--;
      }
    }                                 //  se l'utente non ha ancora finito le vite aggiorno vite e punti, altrimenti notifico che ha perso
    if (vite > 0){
    stampa(vite, punti);
    }else{
      avvisa("Hai perso!", "Riprova", 5, 0);
    }
  }                                 //  aggiorno il record in caso sia stato appena fatto
  lcd.clear();
  if (punti > record){
    record = punti;
    lcd.print("Nuovo record!");
    lcd.setCursor(0, 1);
  }
  lcd.print("Record: " + String(record));
  delay(2500);
  lcd.clear();
}
