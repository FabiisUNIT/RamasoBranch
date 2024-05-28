#include <Servo.h>  //Control Servos
 //Pines para la Rampa Móvil, conexión con Arduino Mega y Servo(2) Librería Servo.h
    #define pinServo_Rampa 5

//Objetos Servomotores
Servo ServoRampa;

const int Selector_Monedas_Pin = 2;//pin al cual estara conectada la señal del monedero

int Lectura_Pin_Moneda;

int Contador_Monedas = 0;

const int Led_Boton = A1;//pin al cual estara conectado un led, para indicar cuando una moneda es aceptada.

//Pines para el boton con led
    #define Boton A0 // // Arduino Mega 12
    #define Boton2 A2 // // Arduino Mega 12

//Variable para el estado del boton de inicio
int estadoBoton, estadoBoton_ant;

//Variable para el estado del boton de inicio
int estadoBoton2, estadoBoton_ant2;

//Etapas de funcionamiento
int etapa = 0;

void setup() {
  // Inicializamos el puerto serial.
  Serial.begin(9600);
  
  //Interrupcion para el Selector de Monedas
  pinMode(Selector_Monedas_Pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(Selector_Monedas_Pin), Selector_Monedas_Interrupt, RISING);

  //Asignamos el pin para el led como salida
  pinMode(Led_Boton, OUTPUT);
  pinMode(Boton2, INPUT);
  pinMode(Boton, INPUT);

  //pinMode(pinServo_Lineal, OUTPUT);
  pinMode(pinServo_Rampa, OUTPUT);

    //Al inicio del codigo los motores inician inactivos
  //ServoLineal.attach(pinServo_Lineal);
  ServoRampa.attach(pinServo_Rampa);
    //Al inicio del codigo los servomotores empiezane en cero
  ServoRampa.write(0);
}

void loop() {
    Leer_Boton();
//De acuerdo con la Tabla de Estados se tiene la siguiente lógica
  if (etapa == 0) {
    if (Contador_Monedas >= 1)
    {
      enciendeBoton();
      if (estadoBoton == 1) {
        Girar_ServoRampa();
        apagaBoton();
        etapa = 1;
        estadoBoton = 0;
      }
    }
  }

 if (etapa == 1) {
 if (estadoBoton2 == 1) {
        etapa = 0;
        estadoBoton2 = 0;
        Regresar_ServoRampa();
        Contador_Monedas--;
      }
  }
}

void Selector_Monedas_Interrupt() {

 Lectura_Pin_Moneda = digitalRead(Selector_Monedas_Pin);

  if (Lectura_Pin_Moneda == 1){
    Contador_Monedas++;
  }
}

void Girar_ServoRampa()
{
  ServoRampa.write(70);
}

void Regresar_ServoRampa()
{
  ServoRampa.write(0);
}

void Leer_Boton () {
  estadoBoton = digitalRead(Boton);
  estadoBoton_ant = estadoBoton;
  estadoBoton2 = digitalRead(Boton2);
  estadoBoton_ant2 = estadoBoton2;
}

void enciendeBoton()
{
  digitalWrite(Led_Boton, HIGH);
}

void apagaBoton()
{
  digitalWrite(Led_Boton, LOW);
}
