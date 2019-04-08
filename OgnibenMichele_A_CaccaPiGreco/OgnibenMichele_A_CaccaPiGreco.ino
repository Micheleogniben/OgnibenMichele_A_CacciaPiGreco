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
  btnStart  = 12;
  btnRecord = 11;
  record    = 0;
                                      //  pinMode di input
  pinMode(btn1,      INPUT);
  pinMode(btn2,      INPUT);
  pinMode(btn3,      INPUT);
  pinMode(btn4,      INPUT);
  pinMode(btn5,      INPUT);
  pinMode(btnStart,  INPUT);
  pinMode(btnRecord, INPUT);
  
  lcd.print("Premi per");
  lcd.setCursor(0, 1);
  lcd.print("iniziare");
}


void stampa(String f1, String f2){
  lcd.print("Vite:" + f1);
  lcd.setCursor(16 - 6 - String(punti).length(), 0);
  lcd.print("Punti:" + f2);
}


void stampaPiGreco(){
  delay(1500);
                                      //  Stampo il piGreco
  int i = 0, premuto = 0, piGreco = (random(1, 6)* 3) - 2;
  
  lcd.setCursor(piGreco, 1);
  lcd.print("π");
  
  while  (i < tempo && premuto == 0){
    if      (digitalRead(btn1) == HIGH){premuto = 1;}
    else if (digitalRead(btn2) == HIGH){premuto = 4;}
    else if (digitalRead(btn3) == HIGH){premuto = 7;}
    else if (digitalRead(btn4) == HIGH){premuto = 10;}
    else if (digitalRead(btn5) == HIGH){premuto = 13;}
    delay(1);
    i++;
  }

  if (premuto == piGreco){punti++;}
  else{vite--; tempo += 50;}

  tempo -= 50;
  
  lcd.clear(); 
  if (vite >= 0){stampa(String(vite), String(punti));}
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
      delay(400);
      while (digitalRead(btnRecord) == LOW){}
      delay(200);
      lcd.clear();
      stampa(String(vite), String(punti));
    }
  }
  lcd.clear();
  lcd.print("Gioco iniziato");
  lcd.setCursor(0, 1);
  lcd.print("Preparati!");
  delay(2500);
  lcd.clear();
  stampa(String(vite), String(punti));
                                      //  con un random scelgo se far apparire bonus o mauls, in questo caso il 15% circa delle partite
  while(vite >= 0){
    if (random(1, 8) == 1){
      //stampaPiGreco();                //  con un random scelgo se far apparire bonus o mauls, in questo caso il 15% circa delle partite

      
      delay(1500);
                                      //  Stampo il piGreco
      int i = 0, premuto = 0, piGreco = (random(1, 6)* 3) - 2, bonus = (random(1, 6)* 3) - 2;

      while (bonus == piGreco){bonus = (random(1, 6)* 3) - 2;}
      
      lcd.setCursor(piGreco, 1);
      lcd.print("π");
      
      lcd.setCursor(bonus, 1);
      lcd.print("b");
  
      while  (i < tempo && premuto == 0){
        if      (digitalRead(btn1) == HIGH){premuto = 1;}
        else if (digitalRead(btn2) == HIGH){premuto = 4;}
        else if (digitalRead(btn3) == HIGH){premuto = 7;}
        else if (digitalRead(btn4) == HIGH){premuto = 10;}
        else if (digitalRead(btn5) == HIGH){premuto = 13;}
        delay(1);
        i++;
      }

      if (premuto == bonus){vite++;}
      else if (premuto == piGreco){punti++;}
      else {vite--; tempo += 50;}

      tempo -= 50;
  
      lcd.clear(); 
      if (vite >= 0){stampa(String(vite), String(punti));}
      
    }else if (random(1, 8) == 1){
      //stampaPiGreco();                //  con un random scelgo se far apparire bonus o mauls, in questo caso il 15% circa delle partite

      
      delay(1500);
                                      //  Stampo il piGreco
      int i = 0, premuto = 0, piGreco = (random(1, 6)* 3) - 2, malus = (random(1, 6)* 3) - 2;

      while (malus == piGreco){malus = (random(1, 6)* 3) - 2;}
      
      lcd.setCursor(piGreco, 1);
      lcd.print("π");
      
      lcd.setCursor(malus, 1);
      lcd.print("m");
  
      while  (i < tempo && premuto == 0){
        if      (digitalRead(btn1) == HIGH){premuto = 1;}
        else if (digitalRead(btn2) == HIGH){premuto = 4;}
        else if (digitalRead(btn3) == HIGH){premuto = 7;}
        else if (digitalRead(btn4) == HIGH){premuto = 10;}
        else if (digitalRead(btn5) == HIGH){premuto = 13;}
        delay(1);
        i++;
      }

      if (premuto == malus){punti--;}
      else if (premuto == piGreco){punti++;}
      else {vite--; tempo += 50;}

      tempo -= 50;
  
      lcd.clear(); 
      if (vite >= 0){stampa(String(vite), String(punti));}

    }else{
      stampaPiGreco();
    }
  }

  if (punti > record){record = punti;}

  lcd.print("Hai perso!");
  lcd.setCursor(0, 1);
  lcd.print("Riprova");
  delay(2500);
  lcd.clear();
  stampa("5", "0");
}
