//Proyecto Domótica Provisoria 

//Control de luces mediante llaves, pulsadores y sensores
//Autor: LJP 
//Fecha: 27/03/2019


//###########################################################################################################################################################

//Salidas
#define oLamp_Escalera A0
#define oLamp_PuertaExterior A1
#define oLamp_Parrilla A2
#define oLamp_Taller A3
#define oLamp_Habitacion A4
#define oLamp_Cocina A5
#define oLamp_Bano 13

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



int state = 0; // Variable lectrura dato serial
 
void setup() {
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
    EstAnt_iLlave_Taller=digitalRead(iLlave_Taller);
    EstAnt_iPuls_TallerDerNegro=digitalRead(iPuls_TallerDerNegro);
    EstAnt_iPuls_TallerIzqRojo=digitalRead(iPuls_TallerIzqRojo);
    EstAnt_iPuls_Abajo=digitalRead(iPuls_Abajo);
    EstAnt_iSns_PuertaPpal=digitalRead(iSns_PuertaPpal);
    EstAnt_iLlave_Habitacion=digitalRead(iLlave_Habitacion);
    EstAnt_iLlave_Cocina=digitalRead(iLlave_Cocina);
    EstAnt_iLlave_Bano=digitalRead(iLlave_Bano);
    EstAnt_iPuls_TallerPaso=digitalRead(iPuls_TallerPaso);
    
}
 
void loop() {


 //################### Control por HC05 #######################################################
        if(Serial.available() > 0){
             state = Serial.read();
        } 
 
        switch (state){
          case 'e': //escalera 
          if(Est_oLamp_Escalera){
            digitalWrite(oLamp_Escalera, LOW);
            Est_oLamp_Escalera=0;
          }
          else{
            digitalWrite(oLamp_Escalera, HIGH);
            Est_oLamp_Escalera=1;
          }
          state=0;
            break;
          case 'a': //afueraLuz puerta 
          if(Est_oLamp_PuertaExterior){
            digitalWrite(oLamp_PuertaExterior, LOW);
            Est_oLamp_PuertaExterior=0;
          }
          else{
            digitalWrite(oLamp_PuertaExterior, HIGH);
            Est_oLamp_PuertaExterior=1;
          }
          state=0;
            break;            
          case 'p': //parrilla
          if(Est_oLamp_Parrilla){
            digitalWrite(oLamp_Parrilla, LOW);
            Est_oLamp_Parrilla=0;
          }
          else{
            digitalWrite(oLamp_Parrilla, HIGH);
            Est_oLamp_Parrilla=1;
          }
          state=0;
            break;            
          case 't': //Taller
          if(Est_oLamp_Taller){
            digitalWrite(oLamp_Taller, LOW);
            Est_oLamp_Taller=0;
          }
          else{
            digitalWrite(oLamp_Taller, HIGH);
            Est_oLamp_Taller=1;
          }
          state=0;
            break;
          case 'h': //Habitacion
          if(Est_oLamp_Habitacion){
            digitalWrite(oLamp_Habitacion, LOW);
            Est_oLamp_Habitacion=0;
          }
          else{
            digitalWrite(oLamp_Habitacion, HIGH);
            Est_oLamp_Habitacion=1;
          }
          state=0;
            break;
          case 'c': //Cocina 
          if(Est_oLamp_Cocina){
            digitalWrite(oLamp_Cocina, LOW);
            Est_oLamp_Cocina=0;
          }
          else{
            digitalWrite(oLamp_Cocina, HIGH);
            Est_oLamp_Cocina=1;
          }
          state=0;
            break;
          case 'b': //Bano
          if(Est_oLamp_Bano){
            digitalWrite(oLamp_Bano, LOW);
            Est_oLamp_Bano=0;
          }
          else{
            digitalWrite(oLamp_Bano, HIGH);
            Est_oLamp_Bano=1;
          }
          state=0;
            break;
          default:
            break;
        }
       
//######################## Control por lógica ####################################################

// Funcion pprender/apagar lampara de escalera con pulsadores de abajo y de arriba ingreso pulsadr derecha
if((EstAnt_iPuls_Abajo == 0 && digitalRead(iPuls_Abajo)) || (EstAnt_iPuls_TallerDerNegro == 0 && digitalRead(iPuls_TallerDerNegro))){ //Flanco ascendente
          if(Est_oLamp_Escalera){
            digitalWrite(oLamp_Escalera, LOW);
            Est_oLamp_Escalera=0;
            digitalWrite(oLamp_PuertaExterior, LOW);
            Est_oLamp_PuertaExterior=0;
          }
          else{
            digitalWrite(oLamp_Escalera, HIGH);
            Est_oLamp_Escalera=1;
            digitalWrite(oLamp_PuertaExterior, HIGH);
            Est_oLamp_PuertaExterior=1;
          }
}

//Situacion en la que subo la escalera de noche  al abrir la puerta prende luz taller y al cerrarla apaga luz escalera
if(Est_oLamp_Escalera){
  if (EstAnt_iSns_PuertaPpal == 0 && digitalRead(iSns_PuertaPpal)){
    digitalWrite(oLamp_Taller, HIGH);
    Est_oLamp_Taller=1;
  }
  if (EstAnt_iSns_PuertaPpal && digitalRead(iSns_PuertaPpal) == 0){
    digitalWrite(oLamp_Escalera, LOW);
    Est_oLamp_Escalera=0;
    digitalWrite(oLamp_PuertaExterior, LOW);
    Est_oLamp_PuertaExterior=0;
  }
}



// Funcion de llave taller cambia estado de lampara taller
if((EstAnt_iLlave_Taller == 0 && digitalRead(iLlave_Taller))||(EstAnt_iLlave_Taller && digitalRead(iLlave_Taller) == 0  )|| (EstAnt_iPuls_TallerPaso == 0 && digitalRead(iPuls_TallerPaso)  )){ //Cualquier flanco
          if(Est_oLamp_Taller){
            digitalWrite(oLamp_Taller, LOW);
            Est_oLamp_Taller=0;
          }
          else{
            digitalWrite(oLamp_Taller, HIGH);
            Est_oLamp_Taller=1;
          }
}

// Funcion de llave habitacionr cambia estado de lampara habitacion
if((EstAnt_iLlave_Habitacion == 0 && digitalRead(iLlave_Habitacion))||(EstAnt_iLlave_Habitacion && digitalRead(iLlave_Habitacion) == 0  )){ //Cualquier flanco
          if(Est_oLamp_Habitacion){
            digitalWrite(oLamp_Habitacion, LOW);
            Est_oLamp_Habitacion=0;
          }
          else{
            digitalWrite(oLamp_Habitacion, HIGH);
            Est_oLamp_Habitacion=1;
          }
}

// Funcion de llave cocina cambia estado de lampara cocina
if((EstAnt_iLlave_Cocina == 0 && digitalRead(iLlave_Cocina))||(EstAnt_iLlave_Cocina && digitalRead(iLlave_Cocina) == 0  )){ //Cualquier flanco
          if(Est_oLamp_Cocina){
            digitalWrite(oLamp_Cocina, LOW);
            Est_oLamp_Cocina=0;
          }
          else{
            digitalWrite(oLamp_Cocina, HIGH);
            Est_oLamp_Cocina=1;
          }
}

// Funcion de llave bano cambia estado de lampara bano
if((EstAnt_iLlave_Bano == 0 && digitalRead(iLlave_Bano))||(EstAnt_iLlave_Bano && digitalRead(iLlave_Bano) == 0  )){ //Cualquier flanco
          if(Est_oLamp_Bano){
            digitalWrite(oLamp_Bano, LOW);
            Est_oLamp_Bano=0;
          }
          else{
            digitalWrite(oLamp_Bano, HIGH);
            Est_oLamp_Bano=1;
          }
}

// Funcion pprender/apagar lampara parrilla con pulsadores ingreso pulsadr izq
if((EstAnt_iPuls_TallerIzqRojo == 0 && digitalRead(iPuls_TallerIzqRojo))){ //Flanco ascendente
          if(Est_oLamp_Parrilla){
            digitalWrite(oLamp_Parrilla, LOW);
            Est_oLamp_Parrilla=0;
          }
          else{
            digitalWrite(oLamp_Parrilla, HIGH);
            Est_oLamp_Parrilla=1;
          }
}





//############################### Actualizo valores de estado anterior de entradas ##########################
EstAnt_iPuls_Abajo=digitalRead(iPuls_Abajo);
EstAnt_iPuls_TallerDerNegro=digitalRead(iPuls_TallerDerNegro);
EstAnt_iPuls_TallerIzqRojo=digitalRead(iPuls_TallerIzqRojo);
EstAnt_iLlave_Taller=digitalRead(iLlave_Taller);
EstAnt_iSns_PuertaPpal=digitalRead(iSns_PuertaPpal);
EstAnt_iLlave_Habitacion=digitalRead(iLlave_Habitacion);
EstAnt_iLlave_Cocina=digitalRead(iLlave_Cocina);
EstAnt_iLlave_Bano=digitalRead(iLlave_Bano);
EstAnt_iPuls_TallerPaso=digitalRead(iPuls_TallerPaso);

delay(50);
}


