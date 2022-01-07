#ifndef POSITION_READER_H_INCLUDED
#define POSITION_READER_H_INCLUDED

#include "acceleration_reader.h"


class Position_reader : public Acceleration_reader {

    private:

        /* VARIABLES CONTENANT LA VALEUR DE LA VITESSE SUR CHAQUE AXE */
        Coords m_speed{NB_DIMENSIONS};

        /* VECTEUR DE STOCKAGE DES PRECEDENTES VITESSES */
        std::vector<Coords*> m_previous_speeds_save;

        /* VARIABLES CONTENANT LA VALEUR DE LA POSITION SUR CHAQUE AXE */
        Coords m_position{NB_DIMENSIONS};

        /* VECTEUR DE STOCKAGE DES PRECEDENTES POSITIONS */
        std::vector<Coords*> m_previous_positions_save;

        /* CONSTANTE DEFINISSANT LE NOMBRE DE COORDS ENREGISTREES */
        const unsigned short NB_COORDS_SAVED_MAX = 250;

        

    public:
        
        Position_reader();
        ~Position_reader();

        /* ***** */
        /* SPEED */
        /* ***** */

        void setInitialVelocityToNull();

        /* ******** */
        /* POSITION */
        /* ******** */

        // void setInitialPosition(const SPIFFS& save_coords_file);
        void setInitialPosition();

};

#endif // POSITION_READER_H_INCLUDED