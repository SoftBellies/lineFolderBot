
int ledDebugDroite = 5;
int ledDebugGauche = 4;

int moteurGauche = 2;
int moteurDroite = 3;


int capteurGauche = A0;
int capteurDroite = A1;

int pinButton = 12;

int seuil = 200;
int seuilGauche = 200;
int seuilDroite = 200;

void setup()
{

  pinMode(ledDebugDroite, OUTPUT);
  pinMode(ledDebugGauche, OUTPUT);
  pinMode(moteurGauche, OUTPUT);
  pinMode(moteurDroite, OUTPUT);
  pinMode(pinButton, INPUT);
  
}
void setSeuil()
{
  stop();
  //on attend que le bouton soit relaché
  int a=1;
  while( a==1){
    a = digitalRead(pinButton);
    delay(1);
  }

  int minGauche;
  int minDroite;
  minGauche = analogRead(capteurGauche);
  minDroite = analogRead(capteurDroite);

  digitalWrite(ledDebugDroite,LOW);
  digitalWrite(ledDebugGauche,LOW);

  while (a ==0){
    delay(1);
    a = digitalRead(pinButton);
  }
  //Nouvel appui sur le bouton
  while(a==1){
    delay(1);
    a = digitalRead(pinButton);
  }

  int maxGauche;
  int maxDroite;
  maxGauche = analogRead(capteurGauche);
  maxDroite = analogRead(capteurDroite);

  seuilGauche = (minGauche + maxGauche) / 2;
  seuilDroite = (minDroite + maxDroite) / 2;

  for(int b = 0; b < 5; b++){
      digitalWrite(ledDebugDroite,HIGH);
      digitalWrite(ledDebugGauche,HIGH);
      delay(200);
      digitalWrite(ledDebugDroite,LOW);
      digitalWrite(ledDebugGauche,LOW);
      delay(200);
  }

}
void stop(){
  digitalWrite(moteurGauche,LOW);
  digitalWrite(moteurDroite,LOW);
}
void tourneDroite(){
  digitalWrite(moteurGauche,HIGH);
  digitalWrite(moteurDroite,LOW);
}
void tourneGauche(){
  digitalWrite(moteurGauche,LOW);
  digitalWrite(moteurDroite,HIGH);
}
void avance(){
    digitalWrite(moteurGauche,HIGH);
    digitalWrite(moteurDroite,HIGH);
}
void loop()
{
  int a;
  a = digitalRead(pinButton);
  if(a == 1){
    //le buton a été appuyé
    setSeuil();
  }

  int valGauche;
  int valDroite;
  valGauche = analogRead(capteurGauche);    
  valDroite = analogRead(capteurDroite);

  if(valGauche < seuil)
    digitalWrite(ledDebugGauche,HIGH);
  else
    digitalWrite(ledDebugGauche,LOW);
  

  if(valDroite < seuil)
    digitalWrite(ledDebugDroite,HIGH);
  else
    digitalWrite(ledDebugDroite,LOW);
  

  if((valGauche < seuilGauche) && (valDroite < seuilDroite))
    avance();
  
  if((valGauche < seuilGauche) && (valDroite > seuilDroite)){
    tourneDroite();
    while(valDroite > seuilDroite){
      valDroite = analogRead(capteurDroite);  
      delay(1);
    }
  }
  if((valGauche > seuilGauche) && (valDroite < seuilDroite)){
    tourneGauche();
    while(valGauche > seuilGauche){
      valGauche = analogRead(capteurGauche);  
      delay(1);
    }
  }
  if((valGauche > seuilGauche) && (valDroite > seuilDroite))
    stop();  
}
