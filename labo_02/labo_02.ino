const int btnPin = 2;
const int nbLeds = 4;
const int ledPins[] = {8, 9, 10, 11};
const int potentiometrePin = A1;
const unsigned long debounceDelay = 50;
const int echelle=20;
const int niveauPWM=1023;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(btnPin, INPUT_PULLUP);
  for (int i = 0; i < nbLeds; i++){
     pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  int valeur = lirePotentiometre();
  gererLeds(valeur);
  verifierBouton(valeur);
}

int lirePotentiometre() {
  return map(analogRead(potentiometrePin), 0, niveauPWM, 0, echelle);
}

void gererLeds(int valeur) {
  int index = map(valeur, 0, echelle, 0, nbLeds);
  for (int i = 0; i < nbLeds; i++){
     digitalWrite(ledPins[i], (i == index) ? HIGH : LOW);
  }
}

void verifierBouton(int valeur) {
  int buttonState = digitalRead(btnPin);
  if (buttonState == LOW && lastButtonState == HIGH && millis() - lastDebounceTime > debounceDelay) {
    afficherBarreProgression(valeur);
    lastDebounceTime = millis();
  }
  lastButtonState = buttonState;
}

void afficherBarreProgression(int valeur) {
  int pourcentage = map(valeur, 0, echelle, 0, 100);
  Serial.print(pourcentage);
  Serial.print("% [");
  for (int i = 0; i < echelle; i++){
     Serial.print(i < pourcentage / 5 ? "@" : ".");
  }
  Serial.println("]");
}
