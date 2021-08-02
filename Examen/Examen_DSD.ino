//Estas son las señales de las notas en hercios
const int arrSeniales[] = {440, 261, 293, 329};
//Estos son los puertos utilizados como entrada de las notas
const int arrPuertosEntradaSenial[] = {2, 3};
//Este arreglo representa los puntos del 1 al 6 del diagrama (Se le agrega uno mas que es la posicion 0 - no se utiliza)
bool arrCompuertasFlipFlop[] = {false, false, false, false, false, false, false};
//Este es el puerto de entrada del switch de 2 tiros
const int puertoSwitch = 4;
//Estos son los puertos por donde saldra la señal
const int arrPuertosSalida[] = {9, 10};
//Esto almacenara el ultimo estado del switch de 2 tiros para comparar si es necesario cambiar la configuracion inicial de las compuertas
bool ultimoEstadoDelSwitch = false;
//Este es el arreglo de las compuertas de salida del sistema
bool arrCompuertasBocinas[] = {false, false, false, false, false, false, false};
//Esta variable representa la senial cuadrada
bool debeSonar = true;
bool obtenerEstadoPuerto(int puerto){
  if(digitalRead(puerto) == HIGH){
    return true;
  }else{
    return false;
  }
}
void establecerConfiguracionCompuertas(){
    int i = 0;
    for(i = 1; i<=6; i++){
      arrCompuertasFlipFlop[i] = false;
    }
    //Primero valido que el switch de dos tiros este prendido para saber si incia con SET == 1 o RESET == 1
    if(obtenerEstadoPuerto(puertoSwitch)){
      arrCompuertasFlipFlop[1] = true;
      arrCompuertasFlipFlop[5] = false;
    }else{
      arrCompuertasFlipFlop[1] = false;
      arrCompuertasFlipFlop[5] = true;
    }
}
int obtenerNota(){
  int valorArreglo = 0;
  valorArreglo += (obtenerEstadoPuerto(arrPuertosEntradaSenial[0])?1:0);
  valorArreglo += (obtenerEstadoPuerto(arrPuertosEntradaSenial[1])?2:0);
  return arrSeniales[valorArreglo];
}
void setup() {
  Serial.begin(9600);
  int i = 0;
  for(i = 0; i < 2; i ++){
    pinMode(arrPuertosEntradaSenial[i], INPUT);
  }
  for(i = 0; i < 2; i ++){
    pinMode(arrPuertosSalida[i], OUTPUT);
  }
  pinMode(puertoSwitch, INPUT);
  //Abro los puertos y especifico como va a estar el estado inicial de las compuertas
  arrCompuertasFlipFlop[0] = true;
  establecerConfiguracionCompuertas();
}
void sonarBocina(){
  unsigned long tiempoEspera = 0;
  int nota = 0;
  nota = obtenerNota();
  if(arrCompuertasBocinas[3]){
    tone(arrPuertosSalida[0],nota);
    noTone(arrPuertosSalida[1]);
  }else if(arrCompuertasBocinas[6]){
    tone(arrPuertosSalida[1],nota);
    noTone(arrPuertosSalida[0]);
  }
}
void loop() {
  if(obtenerEstadoPuerto(puertoSwitch) != ultimoEstadoDelSwitch){
    ultimoEstadoDelSwitch = !ultimoEstadoDelSwitch;
    establecerConfiguracionCompuertas();
  }
  //Al terminar la ecuacion ya tenemos Q y /Q (posiciones 3 y 6)
  arrCompuertasFlipFlop[3] = arrCompuertasFlipFlop[4] = (!arrCompuertasFlipFlop[2] || !arrCompuertasFlipFlop[1]);
  arrCompuertasFlipFlop[6] = arrCompuertasFlipFlop[2] = (!arrCompuertasFlipFlop[4] || !arrCompuertasFlipFlop[5]);
  arrCompuertasBocinas[2] = arrCompuertasFlipFlop[3];
  arrCompuertasBocinas[5] = arrCompuertasFlipFlop[6];
  arrCompuertasBocinas[1] = arrCompuertasBocinas[4] = debeSonar;
  arrCompuertasBocinas[3] = (arrCompuertasBocinas[1] && arrCompuertasBocinas[2]);
  arrCompuertasBocinas[6] = (arrCompuertasBocinas[4] && arrCompuertasBocinas[5]);
  debeSonar = !debeSonar;
  int nota = obtenerNota();
  char lado;
  if(arrCompuertasFlipFlop[3])
    lado = 'L';
  else 
    lado = 'R';
  Serial.println(String(nota)+" - "+String(lado));
  sonarBocina();
}
