// lineFollowerBot.ino
// Programme basique permettant à un robot de suivre une ligne dessinée au sol.
//
// Un projet du hackerspace Ventres Mous.

// =============================================================================
//
// IDENTIFICATION DES BROCHES DE L’ARDUINO UTILISÉES PAR LE PROJET
//
// =============================================================================

// Chaque broche de l’Arduino est identifiée par un numéro. Afin de faciliter
// la lecture du code, on leur donne des noms parlants.

// Broches sur lesquelles les moteurs sont connectés.
// Ce sont des broches de sortie numériques.
#define MOTEUR_GAUCHE 2
#define MOTEUR_DROITE 3

// Broches sur lesquelles les capteurs sont connectés.
// Ce sont des broches de lecture analogique.
#define CAPTEUR_GAUCHE A0
#define CAPTEUR_DROITE A1

// Broches sur lesquelles les leds de suivi d’étalonnage sont connectées.
// Ce sont des broches de sortie numériques.
#define ETALONNAGE_LED_GAUCHE 4
#define ETALONNAGE_LED_DROITE 5

// Broche sur laquelle le bouton d’étalonnage est connecté.
// C’est une broche de lecture numérique.
#define ETALONNAGE_BOUTON 12

// Les 2 états possible du bouton d’étalonnage : pressé et relevé.
#define BOUTON_PRESSE 1
#define BOUTON_RELEVE 0

// Variables utilisées pour définir les seuils de détection des capteurs. Les
// seuils sont réglés à 200 par défaut.
int seuil_gauche = 200;
int seuil_droite = 200;

// =============================================================================
//
// INITIALISATION DES BROCHES DE L’ARDUINO
//
// =============================================================================

// Cette fonction est exécutée une seule fois lors de l’allumage de l’Arduino.
// Son rôle consiste à configurer l’Arduino pour un usage précis, dans le cas
// présent pour un robot suiveur de ligne.
void setup() {
  // Configure les broches des moteurs en sortie numérique.
  pinMode(MOTEUR_GAUCHE, OUTPUT);
  pinMode(MOTEUR_DROITE, OUTPUT);

  // Configure les broches des leds de suivi d’étalonnage en sortie numérique.
  pinMode(ETALONNAGE_LED_GAUCHE, OUTPUT);
  pinMode(ETALONNAGE_LED_DROITE, OUTPUT);

  // Configure la broche du bouton d’étalonnage en entrée numérique.
  pinMode(ETALONNAGE_BOUTON, INPUT);

  // Les broches analogiques des capteurs sont obligatoirement en mode lecture
  // analogique. Il n’y a donc pas de réglage à faire sur ces broches.
}

// =============================================================================
//
// GESTION DU BOUTON D’ÉTALONNAGE
//
// =============================================================================

// Attend jusqu’à ce que le bouton d’étalonnage soit enfoncé ou relaché.
// Le paramètre etat peut prendre 2 valeurs : BOUTON_PRESSE et BOUTON_RELEVE.
void continuer_si(int etat) {
  while(digitalRead(ETALONNAGE_BOUTON) != etat) delay(1);
}

// =============================================================================
//
// GESTION DES LEDS D’ÉTALONNAGE
//
// =============================================================================

// Fait clignoter les leds d’étalonnage pour indiquer à l’utilisateur que
// l’étalonnage est terminé.
void clignoter() {
  // Fait clignoter 5 fois les leds. Clignoter consiste à allumer puis éteindre.
  for(int b = 0; b < 5; b++) {
    // Allume les leds d’étalonnage (les broches sont réglées à 5 volts).
    digitalWrite(ETALONNAGE_LED_GAUCHE, HIGH);
    digitalWrite(ETALONNAGE_LED_DROITE, HIGH);

    // Attend 0,2 secondes.
    delay(200);

    // Éteint les leds d’étalonnage (les broches sont réglées à 0 volt).
    digitalWrite(ETALONNAGE_LED_GAUCHE, LOW);
    digitalWrite(ETALONNAGE_LED_DROITE, LOW);

    // Attend 0,2 secondes.
    delay(200);
  }
}

// Éteint les deux leds d’étalonnage.
void eteindre() {
  // Éteint les 2 leds de débogage en mettant leurs broches à 0 volt.
  digitalWrite(ETALONNAGE_LED_GAUCHE, LOW);
  digitalWrite(ETALONNAGE_LED_DROITE, LOW);
}

// =============================================================================
//
// ÉTALONNAGE DES CAPTEURS DU ROBOT
//
// =============================================================================

// Étalonne les capteurs pour établir la différence entre la ligne et le sol.
void etalonnage() {
  // Variables qui vont recevoir les valeurs minimales et maximales des capteurs
  // gauche et droite. L’unité importe peu.
  int min_gauche;
  int min_droite;
  int max_gauche;
  int max_droite;

  // Arrête les 2 moteurs, le robot ne bouge plus.
  moteur_arret();

  // L’étalonnage est déclenché quand l’utilisateur appuie sur le bouton
  // d’étalonnage. On attend que le bouton soit relaché pour étalonner.
  continuer_si(BOUTON_RELEVE);

  // Lit l’état des deux capteurs.
  min_gauche = analogRead(CAPTEUR_GAUCHE);
  min_droite = analogRead(CAPTEUR_DROITE);

  // Éteint les deux leds d’étalonnage.
  eteindre();

  // Attend que l’utilisateur clique sur le bouton (clic = appui + relache).
  continuer_si(BOUTON_PRESSE);
  continuer_si(BOUTON_RELEVE);

  // Lit l’état des deux capteurs.
  max_gauche = analogRead(CAPTEUR_GAUCHE);
  max_droite = analogRead(CAPTEUR_DROITE);

  // Le seuil correspond à la valeur située entre les valeurs minimales et
  // maximales que le capteur retourne.
  seuil_gauche = (min_gauche + max_gauche) / 2;
  seuil_droite = (min_droite + max_droite) / 2;

  clignoter();
}

// =============================================================================
//
// GESTION DES DEUX MOTEURS
//
// =============================================================================

// Arrête les deux moteurs. Le robot ne bouge plus.
void moteur_arret() {
  digitalWrite(MOTEUR_GAUCHE, LOW);
  digitalWrite(MOTEUR_DROITE, LOW);
}

// Fait tourner le robot à droite.
void moteur_droite() {
  // Pour tourner à droite, on bloque le côté droit et on fait avancer le côté
  // gauche.
  digitalWrite(MOTEUR_GAUCHE,HIGH);
  digitalWrite(MOTEUR_DROITE,LOW);
}

// Fait tourner le robot à gauche.
void moteur_gauche() {
  // Pour tourner à gauche, on bloque le côté gauche et on fait avancer le côté
  // droit.
  digitalWrite(MOTEUR_GAUCHE, LOW);
  digitalWrite(MOTEUR_DROITE, HIGH);
}

// Fait tourner les deux moteurs. Le robot avance.
void moteur_avance() {
  digitalWrite(MOTEUR_GAUCHE, HIGH);
  digitalWrite(MOTEUR_DROITE, HIGH);
}

// =============================================================================
//
// BOUCLE PRINCIPALE
//
// =============================================================================

// La fonction loop est appelée en boucle par l’Arduino.
void loop() {
  // Variables qui vont recevoir les valeurs des capteurs.
  int valeur_gauche;
  int valeur_droite;

  // Si le bouton d’étalonnage est pressé, on lance l’étalonnage.
  if(digitalRead(ETALONNAGE_BOUTON) == 1) etalonnage();

  // Lit l’état des deux capteurs.
  valeur_gauche = analogRead(CAPTEUR_GAUCHE);
  valeur_droite = analogRead(CAPTEUR_DROITE);

  // Fait avancer le robot si les deux capteurs identifient le sol.
  if((valeur_gauche < seuil_gauche) && (valeur_droite < seuil_droite)) {
    moteur_avance();
    return;
  }

  // Tourne à droite si le capteur de gauche identifie le sol et le capteur de
  // droite identifie la ligne.
  if((valeur_gauche < seuil_gauche) && (valeur_droite > seuil_droite)) {
    moteur_droite();

    // Attend que le capteur de droite identifie le sol.
    while(analogRead(CAPTEUR_DROITE) > seuil_droite) delay(1);

    return;
  }

  // Tourne à gauche si le capteur de gauche identifie la ligne et le capteur de
  // droite identifie le sol.
  if((valeur_gauche > seuil_gauche) && (valeur_droite < seuil_droite)) {
    moteur_gauche();

    // Attend que le capteur de gauche identifie le sol.
    while(analogRead(CAPTEUR_GAUCHE) > seuil_gauche) delay(1);

    return;
  }

  // Arrête le robot si les deux capteurs identifient chacun le sol. Cela veut
  // dire que le robot a perdu la ligne, il est plus prudent de l’arrêter.
  if((valeur_gauche > seuil_gauche) && (valeur_droite > seuil_droite)) {
    moteur_arret();
    return;
  }
}
