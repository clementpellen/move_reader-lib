# move_reader-lib
Bibliothèque permettant de lire l'accélération / vitesse / position d'un Système Embarqué 

Lecture réalisée à partir d'une centrale inertielle MPU9250

Programmation Orientée Objet sur Système Embarqué : C / C++ / Arduino

Bibliothèques utilisées : 
- Wire.h
- Arduino.h
- iostream
- vector
- utility

Les fonctions pensées pour être utilisées simplement par un objet appelant sont celles de la catégorie USE en bas de la classe :
- use()
- display()
- present()

Les pins du PMU9250 se branchent de la façon suivante à un ESP32 :
- VCC sur le 3.3V
- GND à la masse
- SCL/SCLK au pin 22
- SDA/SDI au pin 21
