#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 


int boton_inicio = 2; // Pin del boton amarillo (inicia la lectura de datos)
int boton_final = 3; // Pin del boton rojo (finaliza la lectura de datos)
int led_verde = 6; // led verde(indica registro de datos)
int led_rojo = 7; // led verde(indica que no hay registro de datos)

unsigned long tiempo_lectura = 1000; // intervalo de lectura general (sin ejecutar funcion de registro de datos)
unsigned long intervalo_lectura = 50; // intervalo de lectura para el registro de datos
unsigned long tiempo_actual;  
unsigned long tiempo_bmp;
int estado_boton_inicio;
int estado_boton_final;

int estado_anterior_boton_inicio;
int estado_anterior_boton_final;

float presion_inicial;
float presion;
char p_char[10];


Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600); // Inicializa el monitor serial

  Serial.println("CLEARDATA"); //limpia los datos previos 
  Serial.println("LABEL, Hora, tiempo, presion"); // string necesario para el registro de datos en excel
  Serial.println("RESETTIMER"); 

  pinMode(boton_inicio, INPUT_PULLUP); //Habilita el pin asignado al boton de inicio de registro de datos en el modo de entrada y activa la resistencia Pullup
  pinMode(boton_final, INPUT_PULLUP); //Habilita el pin asignado al boton para finalizar el registro de datos en el modo de entrada y activa la resistencia Pullup
  digitalWrite(boton_inicio,HIGH); // Aplica un estado lógico alto en el boton de inicio de registro de datos 
  digitalWrite(boton_final,HIGH);// Aplica un estado lógico alto en el boton de finalización de registro de datos 
  
  pinMode(led_verde, OUTPUT); // Habilita el pin del led verde (registro de datos) como un pin de salida
  pinMode(led_rojo, OUTPUT); // Habilita el pin del led rojo (no hay registro de datos) como un pin de salida
  

  estado_anterior_boton_inicio = digitalRead(boton_inicio);
  estado_anterior_boton_final = digitalRead(boton_final);
  tiempo_actual = millis();

  inicio_lcd();
  comprobar_bmp();
  leds_no_lectura();
  presion_inicial = bmp.readPressure();

}

void loop() {

  if(millis() - tiempo_bmp >= tiempo_lectura){
    lectura_continua();  
    }
  
  int estado_actual_boton_inicio = digitalRead(boton_inicio);
  int estado_actual_boton_final = digitalRead(boton_final);
  
  if (estado_actual_boton_inicio == LOW && estado_anterior_boton_inicio == HIGH ) {
    while(estado_actual_boton_final == HIGH){
      registro_presion();
      estado_actual_boton_final = digitalRead(boton_final);
      
      }
  Serial.println("Hemos pulsado el boton");
  registro_presion();
  }/* else if (estado_actual_boton_inicio == LOW && estado_actual_boton_final == LOW ){
    
  }*/
 
  //estado_anterior_boton_inicio = estado_actual_boton_inicio;
  //estado_anterior_boton_final = estado_actual_boton_final;

}
//////////////////////////////////////////

 void inicio_lcd(){
  lcd.init();
  lcd.backlight();          // Activar luz de fondo 
  lcd.clear();              // Borrar LCD

  lcd.setCursor(6,0);
  lcd.print("UNAM");
  delay(1500);

  lcd.clear();
  lcd.setCursor(1,0);       // coordenadas LCD (x,y)
  lcd.print("Facultad");   // Mensaje de inicio 
  lcd.setCursor(5,1);
  lcd.print("de Quimica");
  delay(1500);
  lcd.clear();
}


void comprobar_bmp(){
  
  if (!bmp.begin()) {
    
    Serial.println("No se ha detectado un sensor valido (BMP180). Por favor checa las conecciones!");
    lcd.clear();
    lcd.setCursor(2,0);       // coordenadas LCD (x,y)
    lcd.print("BMP180 Fallo");
    lcd.setCursor(1,1);       // coordenadas LCD (x,y)
    lcd.print("Revisar cables");
    delay(3000);
    while (1) {}
    }  else {
      Serial.println("Se ha detectado correctamente el sensor BMP185");
      lcd.clear();
      lcd.setCursor(6,0);       // coordenadas LCD (x,y)
      lcd.print("BMP180");
      lcd.setCursor(2,1);       // coordenadas LCD (x,y)
      lcd.print("CORRECTO");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0,0);       // coordenadas LCD (x,y)
      lcd.print("Iniciando lectura");
      lcd.setCursor(2,1);       // coordenadas LCD (x,y)
      lcd.print("de presion");
      delay(2000);
      lcd.clear();
    }
}

void leer_presion(){
  presion = bmp.readPressure();
  presion = presion_inicial - presion;
  presion = presion / 1000;
  presion = (0.9508 * presion) + 6.0424;
}

void registro_presion(){
  leds_lectura();
  tiempo_actual = 0;
   
  Serial.println("Voy a leer la presion");

  if(millis() - tiempo_actual >= intervalo_lectura){
      presion = bmp.readPressure();
      presion = presion_inicial - presion;
      presion = presion / 1000;
      presion = (0.9508 * presion) + 6.0424;
      dtostrf(presion, 5, 2, p_char);

      Serial.print("DATA,TIME,TIMER,"); 
      Serial.println(p_char);
    }

   

  lcd.setCursor(4,0);
  lcd.print("Presion:");
  lcd.setCursor(2,1);
  lcd.print(String(presion, 2) + ("   kPa"));
  
  leds_no_lectura();
}

void lectura_continua(){
    leer_presion();
    Serial.println("lectura de bmp180: " + String(presion) + " kPa");

    lcd.setCursor(4,0);
    lcd.print("Presion:");
    lcd.setCursor(2,1);
    lcd.print(String(presion, 2) + ("   kPa"));
    tiempo_bmp = millis(); 
  }


void leds_lectura(){
  digitalWrite(led_rojo, LOW);
  digitalWrite(led_verde, HIGH);
  }

 void leds_no_lectura(){
  digitalWrite(led_rojo, HIGH);
  digitalWrite(led_verde, LOW);
  }
