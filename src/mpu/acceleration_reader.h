/*  
    ***

    Cette classe est destinée à simplifier l'utilisation du MPU9250
    Elle permet de mesurer l'accélération d'un système embarqué et de savoir si ce dernier est en mouvement
    
    Les fonctions pensées pour être utilisées simplement par un objet appelant sont celles de la catégorie USE en bas de la classe :
        - use()
        - display()
        - present()
    
    Une classe position_reader hérite de cette classe et permet de récupérer les mêmes types de données sur la vitesse et la position du système 

    *** 
*/


#ifndef ACCELERATION_READER_H_INCLUDED
#define ACCELERATION_READER_H_INCLUDED

#include <iostream>
#include <Wire.h>

#include "coords/coords.h"

/* CONSTANTE DEFINISSANT LE NOMBRE DE DIMENSIONS UTILISEES POUR LES COORDS */
const unsigned char NB_DIMENSIONS = 3;

/* CONSTANTE DEFINISSANT LA LIMITE A PARTIR DE LAQUELLE ON CONSIDERE LE SYSTEME EN MOUVEMENT */
const float ACCELERATION_DEVIATION = 0.5;


class Acceleration_reader
{
    
    private:

        /* CONSTANTE DEFINISSANT LE NOMBRE DE COORDS ENREGISTREES */
        const unsigned short NB_COORDS_SAVED_MAX = 3;


    protected:

        /* VARIABLES CONTENANT LA VALEUR DE L'ACCELERATION SUR CHAQUE AXE */
        Coords m_acceleration{NB_DIMENSIONS};

        /* VECTEUR DE STOCKAGE DES PRECEDENTES ACCELERATIONS */
        std::vector<Coords*> m_previous_accelerations_save;

        /* BOOLEEN DECRIVANT SI LE MPU EST EN MOUVEMENT */
        bool in_move;

        

        /* ******************** */
        /* SETTERS : READ VALUE */
        /* ******************** */

        /* Lit la valeur d'accélération du MPU et la retourne */
        float readAccelerationX();
        float readAccelerationY();
        float readAccelerationZ();


        /* **************** */
        /* SAVE INTO VECTOR */
        /* **************** */

        void saveAcceleration();                                /* Sauvegarde la Coord d'accélération dans le vecteur */
        void shiftCoordsSaved(std::vector<Coords *> &vec);      /* Décale les cases du vecteur pour accueillir une nouvelle Coord */


        /* ********** */
        /* MOVE STATE */
        /* ********** */

        bool checkUpdateMoveStateAllowed() const;   /* Vérifie que l'on appelle pas la case -1 du vecteur */
        void updateMoveState();                     /* Modifie l'état s'il y a mouvement ou non détecté */



    public:

        Acceleration_reader();
        ~Acceleration_reader();


        /* ******************** */
        /* SETTERS : READ VALUE */
        /* ******************** */

        void beginCommunication() const;    /* Crée la liaison entre le MPU et le microcontrol. */
        void determineAcceleration();       /* Modifie la Coord d'accélération */


        /* ******* */
        /* GETTERS */
        /* ******* */

        /* Retourne la taille du vecteur de sauvegarde des Coords d'accélération */
        unsigned short getPreviousAccelerationsVectorSize() const
        {
            return m_previous_accelerations_save.size();
        }
        /* Retourne une Coord d'accélération sauvegardé en fonction de l'id */
        Coords getPreviousAccelerationById(unsigned char i) const
        {
            return *(m_previous_accelerations_save[i]);
        }
        /* Retourne la dernière Coord d'accélération enregistrée */
        Coords getLastAcceleration(unsigned char i) const
        {
            return *(m_previous_accelerations_save.back());
        }
        /* Retourne l'état du système : en mouvement / immobile */
        bool getMoveState() const
        {
            return in_move;
        }

        
        /* ******* */
        /* DISPLAY */
        /* ******* */

        void displayAcceleration() const;   /* Affiche la Coord d'accélération */
        void presentAcceleration();         /* Calcule et affiche la Coord d'accélération */


        /* ************ */
        /* DISPLAY SAVE */
        /* ************ */

        void displayPreviousAccelerationsVectorSize() const;            /* Affiche la taille du vecteur de sauvegarde des Coords d'accélération */
        void displayPreviousAccelerationById(unsigned char i) const;    /* Affiche une Coord d'accélération sauvegardé en fonction de l'id */
        void displayLastAcceleration() const;                           /* Affiche la dernière Coord d'accélération enregistrée */
        void presentLastAcceleration();                                 /* Calcule et affiche la dernière Coord d'accélération enregistrée */
        void displayAllPreviousAccelerations() const;                   /* Affiche l'ensemble du vecteur de sauvegarde des Coords d'accélération */


        /* ********** */
        /* MOVE STATE */
        /* ********** */

        void determineMoveState();          /* Détermine l'état du système : en mouvement / immobile */
        void displayMoveState() const;      /* Affiche l'état du système : en mouvement / immobile */
        void presentMoveState();            /* Calcule et affiche l'état du système : en mouvement / immobile */

        
        /* *** */
        /* USE */
        /* *** */

/* FONCTIONS D'UTILISATION DE LA CLASSE ACCELERATION_READER */
        void use();                         /* Calcule l'accélération et l'état du système (en mouvement / immobile) en arrière-plan */
        void display() const;               /* Affiche l'accélération et l'état du système (en mouvement / immobile)  */
        void present();                     /* Calcule et affiche l'accélération et l'état du système (en mouvement / immobile)  */

};

#endif // ACCELERATION_READER_H_INCLUDED