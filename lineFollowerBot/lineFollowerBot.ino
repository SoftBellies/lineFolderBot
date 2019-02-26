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
#define MOTEUR_DROITE 8

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
  // Configure les broches des moteurs en sortie numérique. Ces broches seront
  // soit à 0 volt, soit à 5 volts. Les broches de l’Arduino ne sont pas faites
  // pour alimenter un moteur, elles serviront à piloter des transistors qui,
  // eux, alimenteront les moteurs.
  pinMode(MOTEUR_GAUCHE, OUTPUT);
  pinMode(MOTEUR_DROITE, OUTPUT);

  // Configure les broches des leds de suivi d’étalonnage en sortie numérique.
  // Les leds consomment très peu d’énergie, elles seront directement pilotées
  // par les broches de l’Arduino.
  pinMode(ETALONNAGE_LED_GAUCHE, OUTPUT);
  pinMode(ETALONNAGE_LED_DROITE, OUTPUT);

  // Configure la broche du bouton d’étalonnage en entrée numérique.
  pinMode(ETALONNAGE_BOUTON, INPUT);

  // Les broches analogiques des capteurs sont obligatoirement en mode lecture
  // analogique. Il n’y a donc pas de réglage à faire sur ces broches.
  Serial.begin(9600);
}

// =============================================================================
//
// GESTION DU BOUTON D’ÉTALONNAGE
//
// =============================================================================

// Attend jusqu’à ce que le bouton d’étalonnage soit enfoncé ou relaché.
// Le paramètre etat peut prendre 2 valeurs : BOUTON_PRESSE et BOUTON_RELEVE.
// Si la fonction est appelée avec BOUTON_PRESSE, elle ne laissera le programme
// continuer que si le bouton est enfoncé. Si elle est appelée avec
// BOUTON_RELEVE, elle ne laissera le programme continuer que si le bouton est
// relevé.
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

    // Attend 0,2 secondes (200 millisecondes).
    delay(200);

    // Éteint les leds d’étalonnage (les broches sont réglées à 0 volt).
    digitalWrite(ETALONNAGE_LED_GAUCHE, LOW);
    digitalWrite(ETALONNAGE_LED_DROITE, LOW);

    // Attend 0,2 secondes (200 millisecondes).
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
  // gauche et droite (L’unité importe peu). Elles permettent de garder en
  // mémoire l’état du capteur afin de pouvoir effectuer des calculs plus tard.
  int min_gauche;
  int min_droite;
  int max_gauche;
  int max_droite;

  // Arrête les 2 moteurs, le robot ne bouge plus.
  moteur_arret();

  // L’étalonnage est déclenché quand l’utilisateur appuie sur le bouton
  // d’étalonnage. On attend que le bouton soit relaché pour étalonner.
  continuer_si(BOUTON_RELEVE);
  Serial.println("BOUTON_RELEVE");

  // Lit l’état des deux capteurs.
  min_gauche = analogRead(CAPTEUR_GAUCHE);
  min_droite = analogRead(CAPTEUR_DROITE);

  // Éteint les deux leds d’étalonnage.
  eteindre();

  // Attend que l’utilisateur clique sur le bouton (clic = appui + relache).
  continuer_si(BOUTON_PRESSE);
  continuer_si(BOUTON_RELEVE);
  Serial.println("BOUTON_PRESSE_RELEVE");

  // Lit l’état des deux capteurs.
  max_gauche = analogRead(CAPTEUR_GAUCHE);
  max_droite = analogRead(CAPTEUR_DROITE);

  // Le seuil correspond à la valeur située entre les valeurs minimales et
  // maximales que le capteur retourne.
  seuil_gauche = (min_gauche + max_gauche) / 2;
  seuil_droite = (min_droite + max_droite) / 2;
  Serial.println("FIN_ETALONNAGE");

  clignoter();
}

// =============================================================================
//
// GESTION DES DEUX MOTEURS
//
// =============================================================================

// Arrête les deux moteurs. Le robot ne bouge plus.
void moteur_arret() {
  Serial.println("ARRET_MOTEUR");
  digitalWrite(MOTEUR_GAUCHE, LOW);
  digitalWrite(MOTEUR_DROITE, LOW);
}

// Fait tourner le robot à droite.
void moteur_droite() {
  // Pour tourner à droite, on bloque le côté droit et on fait avancer le côté
  // gauche.
  Serial.println("MOTEUR_DROITE");

  digitalWrite(MOTEUR_GAUCHE,HIGH);
  digitalWrite(MOTEUR_DROITE,LOW);
}

// Fait tourner le robot à gauche.
void moteur_gauche() {
  // Pour tourner à gauche, on bloque le côté gauche et on fait avancer le côté
  // droit.
  Serial.println("MOTEUR_GAUCHE");
  digitalWrite(MOTEUR_GAUCHE, LOW);
  digitalWrite(MOTEUR_DROITE, HIGH);
}

// Fait tourner les deux moteurs. Le robot avance.
void moteur_avance() {
  Serial.println("MOTEUR_AVANCE");
  digitalWrite(MOTEUR_GAUCHE, HIGH);
  digitalWrite(MOTEUR_DROITE, HIGH);
}

// =============================================================================
//
// BOUCLE PRINCIPALE
//
// =============================================================================

// La fonction loop est appelée en boucle par l’Arduino. Un Arduino est prévu
// pour ce genre de tâche : exclusive et répétitive.
// Le programme considère que le robot démarre la ligne entre les deux capteurs.
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
  // droite identifie la ligne. Cela veut dire que le robot dévie à gauche par
  // rapport à la ligne qu’il doit suivre. On corrige en tournant à droite
  // jusqu’à ce que la ligne soit à nouveau entre les deux capteurs.
  if((valeur_gauche < seuil_gauche) && (valeur_droite > seuil_droite)) {
    moteur_droite();

    // Attend que le capteur de droite identifie le sol.
    while(analogRead(CAPTEUR_DROITE) > seuil_droite) delay(1);

    return;
  }

  // Tourne à gauche si le capteur de gauche identifie la ligne et le capteur de
  // droite identifie le sol. Cela veut dire que le robot dévie à droite par
  // rapport à la ligne qu’il doit suivre. On corrige en tournant à gauche
  // jusqu’à ce que la ligne soit à nouveau entre les deux capteurs.
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
