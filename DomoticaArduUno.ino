//Proyecto Domótica Provisoria 

//Control de luces mediante llaves, pulsadores y sensores
//Autor: LJP 
//Fecha: 27/03/2019


//###########################################################################################################################################################

//Includes
#include <TimerOne.h>

//Salidas
#define oLamp_Escalera A0
#define oLamp_PuertaExterior A1
#define oLamp_Parrilla A2
#define oLamp_Taller A3
#define oLamp_Habitacion A4
#define oLamp_Cocina A5
#define oLamp_Bano 12

//Entradas
#define iLlave_Taller 2
#define iPuls_TallerDerNegro 3
#define iPuls_TallerIzqRojo 4
#define iPuls_Abajo 5
#define iSns_PuertaPpal 6
#define iLlave_Habitacion 7
#define iLlave_Cocina 8
#define iLlave_Bano 9
#define iPuls_TallerPaso 10

const long maxCont_oLamp_Escalera = 480;
const long maxCont_oLamp_PuertaExterior = 480;
const long maxCont_oLamp_Parrilla = 50000;
const long maxCont_oLamp_Taller = 50000;
const long maxCont_oLamp_Habitacion = 50000;
const long maxCont_oLamp_Cocina = 50000;
const long maxCont_oLamp_Bano = 50000;
const long maxCont_iFiltro = 10;

//Estado anterior Entradas
int Est_iLlave_Taller = 0;
int Est_iPuls_TallerDerNegro = 0;
int Est_iPuls_TallerIzqRojo = 0;
int Est_iPuls_Abajo = 0;
int Est_iSns_PuertaPpal = 0;
int Est_iLlave_Habitacion = 0;
int Est_iLlave_Cocina = 0;
int Est_iLlave_Bano = 0;
int Est_iPuls_TallerPaso = 0;

//Estado anterior Entradas
int EstAnt_iLlave_Taller = 0;
int EstAnt_iPuls_TallerDerNegro = 0;
int EstAnt_iPuls_TallerIzqRojo = 0;
int EstAnt_iPuls_Abajo = 0;
int EstAnt_iSns_PuertaPpal = 0;
int EstAnt_iLlave_Habitacion = 0;
int EstAnt_iLlave_Cocina = 0;
int EstAnt_iLlave_Bano = 0;
int EstAnt_iPuls_TallerPaso = 0;


//Estados Salidas
int Est_oLamp_Escalera = 0;
int Est_oLamp_PuertaExterior = 0;
int Est_oLamp_Parrilla = 0;
int Est_oLamp_Taller = 0;
int Est_oLamp_Habitacion = 0;
int Est_oLamp_Cocina = 0;
int Est_oLamp_Bano = 0; 

//Variables
int state = 0; // Variable lectrura dato serial
int subiendoEscalera = 0; //1: indica que precione pulsador de abajo y prendo luz esc y luz puerta, y se apaga cuando cierro puerta.

volatile unsigned long cont_iLlave_Taller = 0;
volatile unsigned long cont_iPuls_TallerDerNegro = 0; 
volatile unsigned long cont_iPuls_TallerIzqRojo = 0;
volatile unsigned long cont_iPuls_Abajo = 0;
volatile unsigned long cont_iSns_PuertaPpal = 0;
volatile unsigned long cont_iLlave_Habitacion = 0;
volatile unsigned long cont_iLlave_Cocina = 0;
volatile unsigned long cont_iLlave_Bano = 0;
volatile unsigned long cont_iPuls_TallerPaso = 0;

volatile unsigned long cont_oLamp_Escalera = 0;
volatile unsigned long cont_oLamp_PuertaExterior = 0; 
volatile unsigned long cont_oLamp_Parrilla = 0;
volatile unsigned long cont_oLamp_Taller = 0;
volatile unsigned long cont_oLamp_Habitacion = 0;
volatile unsigned long cont_oLamp_Cocina = 0;
volatile unsigned long cont_oLamp_Bano = 0;


int Lamp_ExtYpuerta = 0; //VER
int ApagarXtiempo_oLamp_Escalera=0; //VER
int AuxLecturaEntrada=0;


//Funcion Inicializacion
void setup() {

    //Timer 
    Timer1.initialize(2500000);
    Timer1.attachInterrupt(controlTiempo); 
    interrupts();

    //Puerto serie
    Serial.begin(9600);
    
    //Configura salidas
    pinMode(oLamp_Escalera, OUTPUT);
    pinMode(oLamp_PuertaExterior, OUTPUT);
    pinMode(oLamp_Parrilla, OUTPUT);
    pinMode(oLamp_Taller, OUTPUT);
    pinMode(oLamp_Habitacion, OUTPUT);
    pinMode(oLamp_Cocina, OUTPUT); 
    pinMode(oLamp_Bano, OUTPUT);

    //Inicializa luces apagadas
    digitalWrite(oLamp_Escalera, LOW);   
    digitalWrite(oLamp_PuertaExterior, LOW);   
    digitalWrite(oLamp_Parrilla, LOW);   
    digitalWrite(oLamp_Taller, LOW);   
    digitalWrite(oLamp_Habitacion, LOW);  
    digitalWrite(oLamp_Cocina, LOW);
    digitalWrite(oLamp_Bano, LOW);

    //Configura entradas
    pinMode(iLlave_Taller, INPUT_PULLUP); 
    pinMode(iPuls_TallerDerNegro, INPUT_PULLUP);
    pinMode(iPuls_TallerIzqRojo, INPUT_PULLUP);
    pinMode(iPuls_Abajo, INPUT_PULLUP);
    pinMode(iSns_PuertaPpal, INPUT_PULLUP);
    pinMode(iLlave_Habitacion, INPUT_PULLUP);
    pinMode(iLlave_Cocina, INPUT_PULLUP);
    pinMode(iLlave_Bano, INPUT_PULLUP);
    pinMode(iPuls_TallerPaso, INPUT_PULLUP);

    //Actualiza valores de entradas
    Est_iLlave_Taller=digitalRead(iLlave_Taller);
    Est_iPuls_TallerDerNegro=digitalRead(iPuls_TallerDerNegro);
    Est_iPuls_TallerIzqRojo=digitalRead(iPuls_TallerIzqRojo);
    Est_iPuls_Abajo=digitalRead(iPuls_Abajo);
    Est_iSns_PuertaPpal=digitalRead(iSns_PuertaPpal);
    Est_iLlave_Habitacion=digitalRead(iLlave_Habitacion);
    Est_iLlave_Cocina=digitalRead(iLlave_Cocina);
    Est_iLlave_Bano=digitalRead(iLlave_Bano);
    Est_iPuls_TallerPaso=digitalRead(iPuls_TallerPaso);

    EstAnt_iLlave_Taller=Est_iLlave_Taller;
    EstAnt_iPuls_TallerDerNegro=Est_iPuls_TallerDerNegro;
    EstAnt_iPuls_TallerIzqRojo=Est_iPuls_TallerIzqRojo;
    EstAnt_iPuls_Abajo=Est_iPuls_Abajo;
    EstAnt_iSns_PuertaPpal=Est_iPuls_Abajo;
    EstAnt_iLlave_Habitacion=Est_iLlave_Habitacion;
    EstAnt_iLlave_Cocina=Est_iLlave_Cocina;
    EstAnt_iLlave_Bano=Est_iLlave_Bano;
    EstAnt_iPuls_TallerPaso=Est_iPuls_TallerPaso;
    
}

//#################################################Control por tiempo##########################################
 void controlTiempo(void)
{
  //Control lampara escalera
  if(Est_oLamp_Escalera){
    if(cont_oLamp_Escalera>maxCont_oLamp_Escalera){
      Est_oLamp_Escalera=0;
      subiendoEscalera=0;
      cont_oLamp_Escalera = 0;
    }else{
      cont_oLamp_Escalera++;
    }
  }else{
    cont_oLamp_Escalera = 0;
}
  //Control lampara puerta
  if(Est_oLamp_PuertaExterior){
    if(cont_oLamp_PuertaExterior>maxCont_oLamp_PuertaExterior){
      Est_oLamp_PuertaExterior=0;
      cont_oLamp_PuertaExterior = 0;
    }else{
      cont_oLamp_PuertaExterior++;
    }
  }else{
    cont_oLamp_PuertaExterior = 0;
}


}



void loop() {

 

//############################### Filtro Entradas ##########################
AuxLecturaEntrada=digitalRead(iLlave_Taller);
if ((Est_iLlave_Taller && AuxLecturaEntrada == 0) || (Est_iLlave_Taller == 0 && AuxLecturaEntrada)){
  if (cont_iLlave_Taller>maxCont_iFiltro){
    Est_iLlave_Taller=AuxLecturaEntrada;
    cont_iLlave_Taller=0;
  }else{
    cont_iLlave_Taller++;
  }
}else{
  cont_iLlave_Taller=0;
}

AuxLecturaEntrada=digitalRead(iPuls_TallerDerNegro);
if ((Est_iPuls_TallerDerNegro && AuxLecturaEntrada == 0) || (Est_iPuls_TallerDerNegro == 0 && AuxLecturaEntrada)){
  if (cont_iPuls_TallerDerNegro>maxCont_iFiltro){
    Est_iPuls_TallerDerNegro=AuxLecturaEntrada;
    cont_iPuls_TallerDerNegro=0;
  }else{
    cont_iPuls_TallerDerNegro++;
  }
}else{
  cont_iPuls_TallerDerNegro=0;
}

AuxLecturaEntrada=digitalRead(iPuls_TallerIzqRojo);
if ((Est_iPuls_TallerIzqRojo && AuxLecturaEntrada == 0) || (Est_iPuls_TallerIzqRojo == 0 && AuxLecturaEntrada)){
  if (cont_iPuls_TallerIzqRojo>maxCont_iFiltro){
    Est_iPuls_TallerIzqRojo=AuxLecturaEntrada;
    cont_iPuls_TallerIzqRojo=0;
  }else{
    cont_iPuls_TallerIzqRojo++;
  }
}else{
  cont_iPuls_TallerIzqRojo=0;
}

AuxLecturaEntrada=digitalRead(iPuls_Abajo);
if ((Est_iPuls_Abajo && AuxLecturaEntrada == 0) || (Est_iPuls_Abajo == 0 && AuxLecturaEntrada)){
  if (cont_iPuls_Abajo>maxCont_iFiltro){
    Est_iPuls_Abajo=AuxLecturaEntrada;
    cont_iPuls_Abajo=0;
  }else{
    cont_iPuls_Abajo++;
  }
}else{
  cont_iPuls_Abajo=0;
}

AuxLecturaEntrada=digitalRead(iSns_PuertaPpal);
if ((Est_iSns_PuertaPpal && AuxLecturaEntrada == 0) || (Est_iSns_PuertaPpal == 0 && AuxLecturaEntrada)){
  if (cont_iSns_PuertaPpal>maxCont_iFiltro){
    Est_iSns_PuertaPpal=AuxLecturaEntrada;
    cont_iSns_PuertaPpal=0;
  }else{
    cont_iSns_PuertaPpal++;
  }
}else{
  cont_iSns_PuertaPpal=0;
}

AuxLecturaEntrada=digitalRead(iLlave_Habitacion);
if ((Est_iLlave_Habitacion && AuxLecturaEntrada == 0) || (Est_iLlave_Habitacion == 0 && AuxLecturaEntrada)){
  if (cont_iLlave_Habitacion>maxCont_iFiltro){
    Est_iLlave_Habitacion=AuxLecturaEntrada;
    cont_iLlave_Habitacion=0;
  }else{
    cont_iLlave_Habitacion++;
  }
}else{
  cont_iLlave_Habitacion=0;
}

AuxLecturaEntrada=digitalRead(iLlave_Cocina);
if ((Est_iLlave_Cocina && AuxLecturaEntrada == 0) || (Est_iLlave_Cocina == 0 && AuxLecturaEntrada)){
  if (cont_iLlave_Cocina>maxCont_iFiltro){
    Est_iLlave_Cocina=AuxLecturaEntrada;
    cont_iLlave_Cocina=0;
  }else{
    cont_iLlave_Cocina++;
  }
}else{
  cont_iLlave_Cocina=0;
}

AuxLecturaEntrada=digitalRead(iLlave_Bano);
if ((Est_iLlave_Bano && AuxLecturaEntrada == 0) || (Est_iLlave_Bano == 0 && AuxLecturaEntrada)){
  if (cont_iLlave_Bano>maxCont_iFiltro){
    Est_iLlave_Bano=AuxLecturaEntrada;
    cont_iLlave_Bano=0;
  }else{
    cont_iLlave_Bano++;
  }
}else{
  cont_iLlave_Bano=0;
}

AuxLecturaEntrada=digitalRead(iPuls_TallerPaso);
if ((Est_iPuls_TallerPaso && AuxLecturaEntrada == 0) || (Est_iPuls_TallerPaso == 0 && AuxLecturaEntrada)){
  if (cont_iPuls_TallerPaso>maxCont_iFiltro){
    Est_iPuls_TallerPaso=AuxLecturaEntrada;
    cont_iPuls_TallerPaso=0;
  }else{
    cont_iPuls_TallerPaso++;
  }
}else{
  cont_iPuls_TallerPaso=0;
}




 //################### Control por HC05 #######################################################
        state=0;
        if(Serial.available() > 0){
             state = Serial.read();
        } 
 
        switch (state){
          case 'e': //escalera 
            Est_oLamp_Escalera=!Est_oLamp_Escalera;  
            break;
          case 'a': //afueraLuz puerta 
            Est_oLamp_PuertaExterior=!Est_oLamp_PuertaExterior;
            break;            
          case 'p': //parrilla
            Est_oLamp_Parrilla=!Est_oLamp_Parrilla;        
            break;            
          case 't': //Taller
            Est_oLamp_Taller=!Est_oLamp_Taller;  
            break;
          case 'h': //Habitacion
            Est_oLamp_Habitacion=!Est_oLamp_Habitacion;
            break;
          case 'c': //Cocina 
            Est_oLamp_Cocina=!Est_oLamp_Cocina;
            break;
          case 'b': //Bano
            Est_oLamp_Bano=!Est_oLamp_Bano;
            break;
          default:
            break;
        }
       
//######################## Control por lógica ####################################################

// Funcion prender/apagar lampara de escalera con pulsadores de abajo y de arriba ingreso pulsadr derecha
if(EstAnt_iPuls_Abajo == 0 && Est_iPuls_Abajo){ //Flanco ascendente pulsador abajo -condicion subir escalera
          if(Est_oLamp_Escalera){
            Est_oLamp_Escalera=0;
            Est_oLamp_PuertaExterior=0;
            subiendoEscalera=0;
          }
          else{
            Est_oLamp_Escalera=1;
            Est_oLamp_PuertaExterior=1;
            subiendoEscalera=1;
          }
}
if(EstAnt_iPuls_TallerDerNegro == 0 && Est_iPuls_TallerDerNegro){ //Flanco ascendente pulsador negro taller -condicion bajar escalera
          if(Est_oLamp_Escalera){
            Est_oLamp_Escalera=0;
            Est_oLamp_PuertaExterior=0;
            subiendoEscalera=0; //no creo que haga falta
          }
          else{
            Est_oLamp_Escalera=1;
            Est_oLamp_PuertaExterior=1;
            subiendoEscalera=0; //no creo que haga falta
          }
}

//Situacion en la que subo la escalera de noche  al abrir la puerta prende luz taller y al cerrarla apaga luz escalera
if(Est_oLamp_Escalera && subiendoEscalera){
  if (EstAnt_iSns_PuertaPpal == 0 && Est_iSns_PuertaPpal){
    Est_oLamp_Taller=1;
  }
  if (EstAnt_iSns_PuertaPpal && Est_iSns_PuertaPpal == 0){
    Est_oLamp_Escalera=0;
    Est_oLamp_PuertaExterior=0;
    subiendoEscalera=0;
  }
}



// Funcion de llave taller cambia estado de lampara taller
if((EstAnt_iLlave_Taller == 0 && Est_iLlave_Taller)||(EstAnt_iLlave_Taller && Est_iLlave_Taller == 0  )|| (EstAnt_iPuls_TallerPaso == 0 && Est_iPuls_TallerPaso  )){ //Cualquier flanco
            Est_oLamp_Taller=!Est_oLamp_Taller;
}

// Funcion de llave habitacionr cambia estado de lampara habitacion
if((EstAnt_iLlave_Habitacion == 0 && Est_iLlave_Habitacion)||(EstAnt_iLlave_Habitacion && Est_iLlave_Habitacion == 0  )){ //Cualquier flanco
            Est_oLamp_Habitacion=!Est_oLamp_Habitacion;
}

// Funcion de llave cocina cambia estado de lampara cocina
if((EstAnt_iLlave_Cocina == 0 && Est_iLlave_Cocina)||(EstAnt_iLlave_Cocina && Est_iLlave_Cocina == 0  )){ //Cualquier flanco
            Est_oLamp_Cocina=!Est_oLamp_Cocina;
}

// Funcion de llave bano cambia estado de lampara bano
if((EstAnt_iLlave_Bano == 0 && Est_iLlave_Bano)||(EstAnt_iLlave_Bano && Est_iLlave_Bano == 0  )){ //Cualquier flanco
            Est_oLamp_Bano=!Est_oLamp_Bano;
}

// Funcion pprender/apagar lampara parrilla con pulsadores ingreso pulsadr izq
if((EstAnt_iPuls_TallerIzqRojo == 0 && Est_iPuls_TallerIzqRojo)){ //Flanco ascendente
            Est_oLamp_Parrilla=!Est_oLamp_Parrilla;
}


EstAnt_iLlave_Taller=Est_iLlave_Taller;
EstAnt_iPuls_TallerDerNegro=Est_iPuls_TallerDerNegro;
EstAnt_iPuls_TallerIzqRojo=Est_iPuls_TallerIzqRojo;
EstAnt_iPuls_Abajo=Est_iPuls_Abajo;
EstAnt_iSns_PuertaPpal=Est_iSns_PuertaPpal;
EstAnt_iLlave_Habitacion=Est_iLlave_Habitacion;
EstAnt_iLlave_Cocina=Est_iLlave_Cocina;
EstAnt_iLlave_Bano=Est_iLlave_Bano;
EstAnt_iPuls_TallerPaso=Est_iPuls_TallerPaso;


//############################### Seteo salidas ##########################
digitalWrite(oLamp_Escalera,Est_oLamp_Escalera);
digitalWrite(oLamp_PuertaExterior,Est_oLamp_PuertaExterior);
digitalWrite(oLamp_Parrilla,Est_oLamp_Parrilla);
digitalWrite(oLamp_Taller,Est_oLamp_Taller);
digitalWrite(oLamp_Habitacion,Est_oLamp_Habitacion);
digitalWrite(oLamp_Cocina,Est_oLamp_Cocina);
digitalWrite(oLamp_Bano,Est_oLamp_Bano);



delay(5);
}


