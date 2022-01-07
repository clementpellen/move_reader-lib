#include "coords.h"


Coords::Coords(unsigned char nb_axes = DIM3) {

    for(size_t i=0; i<nb_axes; ++i)
        m_coords.push_back(INITIAL_COORD_VALUE);

}

Coords::Coords(const std::vector<float>& to_allocate) {
    
    for(size_t i=0; i<to_allocate.size(); ++i)
        m_coords.push_back(to_allocate[i]);

}

Coords::~Coords(){}


/* ******* */
/* SETTERS */
/* ******* */

void Coords::setCoords(float x, float y) {
    setCoordX(x);
    setCoordY(y);
}

void Coords::setCoords(float x, float y, float z) {
    setCoordX(x);
    setCoordY(y);
    setCoordZ(z);
}

void Coords::setCoords(std::vector<float> coords) {
    setCoordX(coords[X]);
    setCoordY(coords[Y]);
    if(coords.size() == 3)
        setCoordZ(coords[Z]);
}

bool Coords::isSetted() const {
    return (m_coords[X] != 0 || m_coords[Y] != 0 || m_coords[Z] != 0 ? true : false);
}


/* ******* */
/* DISPLAY */
/* ******* */

void Coords::displayCoordX() const {
    Serial.print("Axe X : ");
    Serial.println(m_coords[X]);
}

void Coords::displayCoordY() const {
    Serial.print("Axe Y : ");
    Serial.println(m_coords[Y]);
}

void Coords::displayCoordZ() const {
    Serial.print("Axe Z : ");
    Serial.println(m_coords[Z]);
}

void Coords::displayCoordOnAxe(unsigned char axe_number) const {
    switch (axe_number)
    {
    case X:
        displayCoordX();
        break;
    case Y:
        displayCoordY();
        break;
    case Z:
        displayCoordZ();
        break;
    case 3:
        Serial.print("Axe Alpha : ");
        Serial.println(m_coords[axe_number]);
        break;
    case 4:
        Serial.print("Axe Beta : ");
        Serial.println(m_coords[axe_number]);
        break;

    default:
        Serial.print("Axe ");
        Serial.print(axe_number + 100 - 4);
        Serial.print(" : ");
        Serial.println(m_coords[axe_number]);
        break;
    }
}

void Coords::displayCoords() const {
    for(unsigned char i=0; i<m_coords.size(); ++i) 
        displayCoordOnAxe(i);
    Serial.println("");
}

void Coords::displayCoords(std::string title) const {
    Serial.println(title.c_str());
    for (unsigned char i = 0; i < m_coords.size(); ++i)
        displayCoordOnAxe(i);
    Serial.println("");
}


/* ********* */
/* OPERATION */
/* ********* */

bool Coords::isEqualTo(const Coords& reference) const {
    return (m_coords == reference.getCoords() ? true : false);
}

bool Coords::isUpperThan(const Coords &reference) const {
    bool is_upper = true;
    for (unsigned char i = 0; i < m_coords.size(); ++i) {
        if(m_coords[i] > reference.getCoordOnAxe(i)) {}
        else 
            is_upper = false;
    }
    return is_upper;
}

bool Coords::isLowerThan(const Coords &reference) const {
    bool is_lower = true;
    for (unsigned char i = 0; i < m_coords.size(); ++i)
    {
        if (m_coords[i] < reference.getCoordOnAxe(i)) {}
        else
            is_lower = false;
    }
    return is_lower;
}

bool operator == (const Coords& to_compare, const Coords& reference) {
    return to_compare.isEqualTo(reference);
}

bool operator != (const Coords &to_compare, const Coords &reference) {
    return !(to_compare.isEqualTo(reference));
}

bool operator > (const Coords &to_compare, const Coords &reference) {
    return to_compare.isUpperThan(reference);
}

bool operator < (const Coords &to_compare, const Coords &reference) {
    return to_compare.isLowerThan(reference);
}

Coords Coords::addCoords(const Coords& to_add) const {
    Coords new_coords;
    for(size_t i=0; i<m_coords.size(); ++i)
        new_coords.setCoordOnAxe(i, m_coords[i]+to_add.getCoordOnAxe(i));
    return new_coords;
}

Coords Coords::addCoords(float to_add) const {
    Coords new_coords;
    for (size_t i = 0; i < m_coords.size(); ++i)
        new_coords.setCoordOnAxe(i, m_coords[i] + to_add);
    return new_coords;
}

Coords Coords::substractCoords(const Coords &to_sub) const {
    Coords new_coords;
    for (size_t i = 0; i < m_coords.size(); ++i)
        new_coords.setCoordOnAxe(i, m_coords[i] - to_sub.getCoordOnAxe(i));
    return new_coords;
}

Coords Coords::substractCoords(float to_sub) const {
    Coords new_coords;
    for (size_t i = 0; i < m_coords.size(); ++i)
        new_coords.setCoordOnAxe(i, m_coords[i] - to_sub);
    return new_coords;
}

Coords operator + (const Coords &reference, const Coords &to_add)
{
    return reference.addCoords(to_add);
}

Coords operator+(const Coords &reference, float to_add) {
    return reference.addCoords(to_add);
}

Coords operator + (float to_add, const Coords &reference) {
    return reference.addCoords(to_add);
}

Coords operator - (const Coords &reference, const Coords &to_sub) {
    return reference.substractCoords(to_sub);
}

Coords operator-(const Coords &reference, float to_sub) {
    return reference.substractCoords(to_sub);
}