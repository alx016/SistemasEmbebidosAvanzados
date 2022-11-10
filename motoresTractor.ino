const int ENC_A = 6;
const int ENC_A2 = 5;
char op = '0';
char vel [] = {' ' , ' ', ' '};
const int IN1 = 2; //motor 2 
const int IN2 = 3;
const int ENA = 4;

int v = 300;






void setup() {
  Serial.begin (9600);
  pinMode (ENC_A, INPUT);
  pinMode (ENC_A2, INPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT);
  MENU();


}

void loop() {
  encoder();
  delay(3000);

}

void serialEvent () {

  delay(20);
  op = Serial.read();
  while (Serial.available() > 0){Serial.read();}
  switch (op) {
    case '1':
      //prende el motor 2 
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite (ENA, v);
      Serial.println();
      Serial.print(F("ESTADO: "));
      Serial.println(F("----------GIRO HORARIO-------"));
    break;
    //caso de apagado ambos moteres 
    case '2': 
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite (ENA, 0);
      Serial.println();
      Serial.print(F("ESTADO: "));
      Serial.println(F("----------APAGADO-------"));
      encoder();
    break;
    //prende el motor 1 
    case '3': 
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite (ENA, v);
      Serial.println();
      Serial.print(F("ESTADO: "));
      Serial.println(F("----------GIRO ANTIHORARIO-------"));
    break;

    //prenden los dos motores
    case '4' : 
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      analogWrite (ENA, v);
      Serial.println();
      Serial.print(F("ESTADO: "));
      Serial.println(F("----------GIRO ANTIHORARIO-------"));
    break;
      
    


    

    case '5': 
      v=0; 
      Serial.println(); 
      Serial.println(F("Cambio de velocidad")); 
      Serial.println(F("Inrese la velocida en rad/s: ")); 
      while (Serial.available()==0){;}
      Serial.readBytesUntil('\n',vel,3); 
      delay(100); 
      while (Serial.available()==0){Serial.read();}
      v=atoi(vel);
      Serial.print(F("Se cambio la velocidad a: ")); 
      Serial.println (v); 
    break; 

    
      

    }

  MENU(); 

}



void encoder(){
  int a = digitalRead(ENC_A); 
  int b = digitalRead(ENC_A2); 
  Serial.print(a*5); 
  Serial.print (""); 
  Serial.print(b*5); 
  
  
  
  }
void MENU(){
  
  Serial.println(); 
  Serial.println(F("          MENU"));
  Serial.println(F("Presione una opcion 1-4"));
  Serial.println(F("1.Giro izquierda "));
  Serial.println(F("2.Apagado "));  
  Serial.println(F("3.Giro derecha")); 
  Serial.println(F("4.Giro ambos"));
  Serial.println(F("5.Cambiar velocidad"));
}
