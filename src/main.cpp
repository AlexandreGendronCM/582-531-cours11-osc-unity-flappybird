#include <Arduino.h>
#include <FastLED.h>
#include <M5_PbHub.h>
#include <MicroOscSlip.h>




MicroOscSlip<128> monOsc(&Serial);
unsigned long monChronoDepart ; // À DÉPLACER au début du code avec les autres variables globales


#define BROCHE_ATOM_BTN 39
#define BROCHE_ATOM_LUMIERE 27
#define CANAL_0 0


CRGB pixel;
CRGB keyPixel2;
M5_PbHub myPbHub;


// FONCTION QUI SERA APPELÉE LORSQU'UN N'IMPORTTE QUEL MESSAGE OSC EST REÇU
// receivedOscMessage est le message reçu
void myOscMessageParser(MicroOscMessage & receivedOscMessage) {
  // Ici, un if et receivedOscMessage.checkOscAddress() est utilisé pour traiter les différents messages
  if (receivedOscMessage.checkOscAddress("/pixel")) {  // MODIFIER /pixel pour l'adresse qui sera reçue
       int R = receivedOscMessage.nextAsInt(); // Récupérer le premier argument du message en tant que int
       int G = receivedOscMessage.nextAsInt(); // SI NÉCESSAIRE, récupérer un autre int
       int B = receivedOscMessage.nextAsInt(); // SI NÉCESSAIRE, récupérer un autre int

       // UTILISER ici les arguments récupérés

       myPbHub.setPixelColor(CANAL_0, 0,R,G,B);


   // SI NÉCESSAIRE, ajouter d'autres if pour recevoir des messages avec d'autres adresses
   } else if (receivedOscMessage.checkOscAddress("/autre")) {  // MODIFIER /autre une autre adresse qui sera reçue
       // ...
   }
}


void setup()
{

  Wire.begin();
  myPbHub.begin();
  myPbHub.setPixelCount( CANAL_0 ,  1 );

  



  
  FastLED.addLeds<WS2812, BROCHE_ATOM_LUMIERE, GRB>(&pixel, 1); // pour faire l'animation au lancement //

 
  pixel = CRGB(255, 0, 0); 
  FastLED.show();
  delay(1000);
  pixel = CRGB(150, 150, 0); 
  FastLED.show();
  delay(1000);
  pixel = CRGB(0, 255, 0); 
  FastLED.show();
  delay(1000);
  pixel = CRGB(0, 0, 0);
  FastLED.show(); 






Serial.begin(115200);


delay(1000);

}

void loop()
{
  
// CODE RAPIDE
  monOsc.onOscMessageReceived(myOscMessageParser);



  // CODE RALENTIT
  if ( millis() - monChronoDepart >= 20 ) { 
    monChronoDepart = millis(); 

int maLectureBtn = myPbHub.digitalRead(CANAL_0);
  monOsc.sendInt("/btn", maLectureBtn);


 

  }

  
}