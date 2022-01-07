#include "acceleration_reader.h"

Acceleration_reader::Acceleration_reader() {
    in_move = false;
    
    if (!Wire.begin())
    {
        while (1)
        {
            Serial.println("MPU9250 indétectable");
            delay(10);
        }
    }

    /////// Réglage de la sensibilité du gyroscope du MPU ///////
    Wire.beginTransmission(0x68); // début de la communication avec le MPU
    Wire.write(0x1B);             // On accède au registre permettant de configurer la sensibilité du gyroscope
    Wire.write(0x10);             // On lui donne une sensibilité de +-1000 degrés/sec
    Wire.endTransmission(true);   // fin de la transmission

    /////// Réglage de la sensibilité de l'accéléromètre ///////
    Wire.beginTransmission(0x68); // début de la communication avec le MPU
    Wire.write(0x1C);             // On accède au registre permettant de configurer la sensibilité de l'accéléromètre
    Wire.write(0x10);             // on lui donne une sensiblité de +- 8g
    Wire.endTransmission(true);   // fin de la transmission

}

Acceleration_reader::~Acceleration_reader() {}



/* ******************** */
/* SETTERS : READ VALUE */
/* ******************** */

void Acceleration_reader::beginCommunication() const {
    Wire.beginTransmission(0x68); // on entame la communication avec le MPU
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 6, 1);
}

float Acceleration_reader::readAccelerationX() {
    /////////////////   on divise par 4096 (datasheet) pour obtenir une accélération en m.s^-2 /////////////////////////
    return (Wire.read() << 8 | Wire.read()) / 4096.0; //
}

float Acceleration_reader::readAccelerationY()
{
    /////////////////   on divise par 4096 (datasheet) pour obtenir une accélération en m.s^-2 /////////////////////////
    return (Wire.read() << 8 | Wire.read()) / 4096.0; //
}

float Acceleration_reader::readAccelerationZ()
{
    /////////////////   on divise par 4096 (datasheet) pour obtenir une accélération en m.s^-2 /////////////////////////
    return (Wire.read() << 8 | Wire.read()) / 4096.0; //
}

void Acceleration_reader::determineAcceleration() {
    beginCommunication();
    m_acceleration.setCoordX( readAccelerationX() );
    m_acceleration.setCoordY( readAccelerationY() );
    m_acceleration.setCoordZ( readAccelerationZ() );
    saveAcceleration();
}



/* ******* */
/* DISPLAY */
/* ******* */

void Acceleration_reader::displayAcceleration() const {
    Serial.println("Accélération :");
    m_acceleration.displayCoords();
} 

void Acceleration_reader::presentAcceleration() {
    determineAcceleration();
    displayAcceleration();
}


/* **************** */
/* SAVE INTO VECTOR */
/* **************** */

void Acceleration_reader::saveAcceleration() {
    /////////////////   on décale les coordonnées enregistrées et on en ajoute une au vecteur de sauvegarde /////////////////////////
    shiftCoordsSaved(m_previous_accelerations_save);              
    Coords* acceleration_save = new Coords{m_acceleration.getCoords()}; 
    m_previous_accelerations_save.push_back(acceleration_save);         //on ajoute le nouveau pointeur sur Coords
}

void Acceleration_reader::shiftCoordsSaved(std::vector<Coords*>& vec) {
    if (getPreviousAccelerationsVectorSize() >= NB_COORDS_SAVED_MAX) {  //on vérifie si le vecteur est rempli en coordonnées enregistrées
        delete(vec[0]);                                                 //on supprime le pointeur de Coords
        vec.erase(vec.begin());                                         //on supprime la première case du vecteur accélération et on décale toutes les suivantes
    }
}



/* ************ */
/* DISPLAY SAVE */
/* ************ */

void Acceleration_reader::displayPreviousAccelerationsVectorSize() const
{
    Serial.print("Taille du vecteur de Sauvegarde de l'Acceleration : ");
    Serial.println(m_previous_accelerations_save.size());
    Serial.println("");
}

void Acceleration_reader::displayPreviousAccelerationById(unsigned char i) const
{
    Serial.print("Affichage de l'Acceleration ");
    Serial.print(i);
    Serial.println(" :");
    m_previous_accelerations_save[i]->displayCoords();
}

void Acceleration_reader::displayLastAcceleration() const
{
    Serial.println("Affichage de la dernière Accélération :");
    m_previous_accelerations_save.back()->displayCoords();
}

void Acceleration_reader::presentLastAcceleration()
{
    saveAcceleration();
    displayLastAcceleration();
}

void Acceleration_reader::displayAllPreviousAccelerations() const {
    for(unsigned char i=0; i<m_previous_accelerations_save.size(); ++i)
        displayPreviousAccelerationById(i);
}



/* ********** */
/* MOVE STATE */
/* ********** */

bool Acceleration_reader::checkUpdateMoveStateAllowed() const
{
    //on vérifie qu'on n'appelle pas la case -1 du vecteur
    /* (CHECK car vec[-1] <=> vec[4897]) */
    return ((m_previous_accelerations_save.size() - 2 >= 0 && m_previous_accelerations_save.size() - 2 < m_previous_accelerations_save.size()) ? true : false);
}

void Acceleration_reader::updateMoveState() {
    /////////////////   on compare la nouvelle accélération à la dernière valeur enregistrée /////////////////////////
    //(en réalité on compare à l'avant dernière car la sauvegarde dans le vecteur se fait en temps réel)
    if (checkUpdateMoveStateAllowed()) {
        Coords reference = *(m_previous_accelerations_save[m_previous_accelerations_save.size() - 2]);
        Coords margin_high = reference + ACCELERATION_DEVIATION;
        Coords margin_low = reference - ACCELERATION_DEVIATION;
        //Si l'accélération a été (suffisamment) modifiée par rapport à la précédente sauvegarde -> le système est en mouvement
        if(m_acceleration < margin_high && m_acceleration > margin_low)
            in_move = false;
        else 
            in_move = true;
    }
}

void Acceleration_reader::determineMoveState() {
    determineAcceleration();
    updateMoveState();
}

void Acceleration_reader::displayMoveState() const {
    if(in_move == true) {
        Serial.println("Move State : ON");
        Serial.println("** Le système est en mouvement **");
    }
    else {
        Serial.println("Move State : OFF");
        Serial.println("** Le système est immobile **");
    }
    Serial.println("");
}

void Acceleration_reader::presentMoveState() {
    determineMoveState();
    displayMoveState();
}



/* *** */
/* USE */
/* *** */

void Acceleration_reader::use() {
    determineMoveState();
}

void Acceleration_reader::display() const {
    displayAcceleration();
    displayMoveState();
}

void Acceleration_reader::present() {
    determineMoveState();
    displayAcceleration();
    displayMoveState();
}