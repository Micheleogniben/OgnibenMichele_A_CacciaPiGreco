#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
                                      //  variabili di INPUT
int btn1;
int btn2;
int btn3;
int btn4;
int btn5;
int btnStart;
int btnRecord;
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
  btnRecord = 11;
  btnStart  = 12;
  record    = 0;
                                      //  pinMode di input
  pinMode(btn1,      INPUT);
  pinMode(btn2,      INPUT);
  pinMode(btn3,      INPUT);
  pinMode(btn4,      INPUT);
  pinMode(btn5,      INPUT);
  pinMode(btnRecord, INPUT);
  pinMode(btnStart,  INPUT);
  
  lcd.print("Premi per");
  lcd.setCursor(0, 1);
  lcd.print("iniziare");
}


void stampa(String f1, String f2){
  lcd.print("Vite:" + f1);
  lcd.setCursor(16 - 6 - String(punti).length(), 0);
  lcd.print("Punti:" + f2);
}


void avvisa(String f1, String f2, String vite, String punti){
  lcd.clear();
  lcd.print(f1);
  lcd.setCursor(0, 1);
  lcd.print(f2);
  delay(2500);
  lcd.clear();
  stampa(vite, punti);
}


void stampaPiGreco(int posizione, bool bonus, String s){
      delay(1500);
                                      //  Stampo il piGreco
      int i = 0, premuto = 0, piGreco = (random(1, 6)* 3) - 2;

      while(piGreco == posizione){piGreco = (random(1, 6)* 3) - 2;}
      
      lcd.setCursor(piGreco, 1);
      lcd.print("π");
      
      lcd.setCursor(posizione, 1);
      lcd.print(s);
  
      while  (i < tempo && premuto == 0){
        if      (digitalRead(btn1) == HIGH){premuto = 1;}
        else if (digitalRead(btn2) == HIGH){premuto = 4;}
        else if (digitalRead(btn3) == HIGH){premuto = 7;}
        else if (digitalRead(btn4) == HIGH){premuto = 10;}
        else if (digitalRead(btn5) == HIGH){premuto = 13;}
        delay(1);
        i++;
      }

      if (premuto == posizione){
        if (bonus == false){
        punti--; 
        tempo -= 50; 
        vite--;
        }else{
          vite++;
          tempo += 100;
        }
      }else if (premuto == piGreco){
        punti++; 
        if (tempo > 150)
          tempo -= 50;
      }else 
        vite--;
  
      if (vite >= 0)
        {lcd.clear(); stampa(String(vite), String(punti));}
}


void loop() {
  vite  = 5;
  punti = 0;
  tempo = 1500;
                                      //  btn inizio
  while(digitalRead(btnStart)  == LOW){
    if (digitalRead(btnRecord) == HIGH){
      lcd.clear();
      lcd.print("Record: " + String(record) + "pt");
      delay(300);
      while (digitalRead(btnRecord) == LOW){}
      lcd.clear();
      stampa(String(vite), String(punti));
      delay(300);
    }
  }
  avvisa("Gioco iniziato", "preparati!", String(vite), String(punti));
  while(vite >= 0){
    if (random(1, 8) == 1){
      stampaPiGreco((random(1, 6) * 3) - 2, true, "b");
    }else if (random(1, 8) == 1){
      stampaPiGreco((random(1, 6) * 3) - 2, false, "m");
    }else{
      stampaPiGreco(-1, false, "");
    }
  }
  if (punti > record){record = punti;}
  avvisa("Hai perso!", "Riprova", "5", "0");
}
