#include <TimerOne.h>
#include <ServoTimer2.h>

ServoTimer2 servo; //Crear el objeto servo

const int pot_sp = 140; 
const int Pin_En2 = 4; 
const int interruptPin2 = 2;
const int Pin_En = 6; 

long unsigned int counter=0; 
double VelocidadEnRPM =0.0; 
float tiempo=0.0; 
float T=0.02; 
float sp =0;

float referencia= 0.0; 
float Kp=0.03; //0.03; 
float Ti=0.05; //0.05; 
float Td=0.2; //0.0; //Termino derivativo 

float K0=Kp+(Kp*T/Ti)+(Kp*Td/T);
float K1=-Kp-2*Kp*Td/T; 
float K2= Kp*Td/T; 
//Inicializar el error y el control 

float e=0, e1=0, e2=0; 


float u=0, u1=0, u3=0;
void setup() {
  pinMode(Pin_En2,OUTPUT);
  pinMode(Pin_En,OUTPUT);
  pinMode(interruptPin2, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), counting, RISING);
  //Timer 1: Se activa cada 20,000 microsegundos =0.02segundos
  servo.attach(8);
  Timer1.initialize(20000);
  Timer1.attachInterrupt(ISR_RevolucionesPorMinuto);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  sp = pot_sp;
  Serial.print("sp: ");
  Serial.print(referencia); 
  Serial.print(" PWM Salida: "); 
  Serial.print(u);
  Serial.print(" PWM Salida: "); 
  Serial.print(u3);
  Serial.print(" ");  
  Serial.print(e);
  Serial.print(" RPM: "); 
  Serial.println(VelocidadEnRPM/2); 
  int i = 1000; 
  for( i = 1000; i < 2250; i++) { servo.write(i); delay(1); } //delay(1000); //Volver hacia atras for(int i = 2250; i > 750; i--)
  {
    servo.write(i);
  }
}
 
void counting (){
  //contador 
  counter++; 
}

void ISR_RevolucionesPorMinuto(){
  //Calculo de las RPM
    VelocidadEnRPM = 25*counter/(334*T);
  tiempo = tiempo + 0.02;
  referencia = sp;
  e = referencia - VelocidadEnRPM;//El calculo del error es la referencia menos la salida
  u = u1 + K0*e + K1*e1 + K2*e2;//La ley de control no puede ser negativa, en este caso es PWM //modelo de control 
  //Saturacion de la ley de control
  if(u<140){
    u=140;
    }
   else if (u<10){
     u=30;
     }
   u3 = u;
   analogWrite(Pin_En,u);
   analogWrite(Pin_En2, u3);
   u1=u;
   e2=e1;
   e1=e;
   counter = 0;
  }
