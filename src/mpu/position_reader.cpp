#include "position_reader.h"

Position_reader::Position_reader() {
    Acceleration_reader();
    setInitialVelocityToNull(); // vitesse initiale égale à 0
    setInitialPosition();       // initialisation de la position du mpu
}

Position_reader::~Position_reader() {}



/* ***** */
/* SPEED */
/* ***** */


void Position_reader::setInitialVelocityToNull()
{
    m_speed.setCoords(0, 0, 0);
}

/* ******** */
/* POSITION */
/* ******** */

void Position_reader::setInitialPosition()
{
    m_position.setCoords(0, 0, 0);
}