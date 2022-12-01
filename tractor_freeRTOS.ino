////////////////////////lcd 
#include <Wire.h>      // libreria de comunicacion por I2C
#include <LCD.h>      // libreria para funciones de LCD
#include <LiquidCrystal_I2C.h>    // libreria para LCD por I2C

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7



#include <Arduino_FreeRTOS.h>
// variables sensor 

#include <dht.h>

#define dht_pin A0     // Analog Pin A0 of Arduino is connected to DHT11 out pin
 
dht DHT;


int contador;

// define two tasks for Blink & AnalogRead
void TaskPrint1( void *param );
void TaskPrint2( void *param );
void TaskPrint3( void *param );

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;
TaskHandle_t Task_Handle3;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  xTaskCreate(Task_Print1, "Task1",100,NULL,1,&Task_Handle1);
  xTaskCreate(Task_Print2, "Task2",100,NULL,1,&Task_Handle2);
  xTaskCreate(Task_Print3, "Task3",100,NULL,1,&Task_Handle3);
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  DHT.read11(dht_pin);

  ////////////////lcd
  lcd.setBacklightPin(3,POSITIVE);  // puerto P3 de PCF8574 como positivo
  lcd.setBacklight(HIGH);   // habilita iluminacion posterior de LCD
  lcd.begin(16, 2);     // 16 columnas por 2 lineas para LCD 1602A
  lcd.clear();      // limpia pantalla
    
}

void loop()
{
  // Empty. Things are done in Tasks.
}

void Task_Print1(void *param){
  (void) param;
  while(1){
    
    
    Serial.print("Humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%    ");
    
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void Task_Print2(void *param){
  (void) param;
  while(1){
    Serial.print("Temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println(" C");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    contador++;
  }
}


void Task_Print3(void *param){
  (void) param;
  while(1){
    lcd.setCursor(0, 0);  
    lcd.print("T: "); // ubica cursor en columna 0 y linea 0
    lcd.print(DHT.temperature);
    vTaskDelay(100/portTICK_PERIOD_MS);
    lcd.print("H: "); // ubica cursor en columna 0 y linea 0
    lcd.print(DHT.humidity);
    // escribe el texto
    lcd.setCursor(0, 1);    // ubica cursor en columna 0 y linea 1
    
    lcd.print(" Semillas: "); 
    lcd.print(millis() / 2000);   // funcion millis() / 1000 para segundos transcurridos// escribe seg.
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
