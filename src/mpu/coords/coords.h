#ifndef COORDS_H_INCLUDED
#define COORDS_H_INCLUDED

#include <iostream>
#include <vector>
#include <utility>
#include <Arduino.h>

/* CONSTANTE DEFINISSANT LES COORDONNEES A 3 DIMENSIONS */
const unsigned char DIM3 = 3;

/* CONSTANTES VERBEUSES D'ACCES A CHAQUE DIMENSION DU VECTEUR M_COORDS */
const unsigned char X = 0;
const unsigned char Y = 1;
const unsigned char Z = 2;

// TODO: FAIRE UNE CLASSE COORDS TEMPORELLES QUI HERITE DE COORDS

/* VALEUR DE LA COORDONNEE LORSQUE LE VECTEUR EST CREE */
const unsigned char INITIAL_COORD_VALUE = 0;

class Coords {

    private :
        
        std::vector<float> m_coords;

    
    public :
        
        Coords(unsigned char nb_axes);
        Coords(const std::vector<float>& to_allocate);
        ~Coords();

        /* ******* */
        /* GETTERS */
        /* ******* */

        float getCoordX() const {
            return m_coords[X];
        }
        float getCoordY() const {
            return m_coords[Y];
        }
        float getCoordZ() const {
            return m_coords[Z];
        }
        float getCoordOnAxe(unsigned char axe_number) const {
            return m_coords[axe_number];
        }

        std::vector<float> getCoords() const {
            return m_coords;
        }


        /* ******* */
        /* SETTERS */
        /* ******* */

        void setCoordX(float x) {
            m_coords[X] = x;
        }
        void setCoordY(float y){
            m_coords[Y] = y;
        }
        void setCoordZ(float z){
            m_coords[Z] = z;
        }
        void setCoordOnAxe(unsigned char axe_number, float coord) {
            m_coords[axe_number] = coord;
        }
        
        void setCoords(float x, float y);
        void setCoords(float x, float y, float z);
        void setCoords(std::vector<float> coords);

        // template <typename AXE_X, typename... OTHER_AXES>
        // void setCoordsExtraDim(const AXE_X& x, const OTHER_AXES&... other_axes) {
        //     setCoordOnAxe(X, x);
        //     const unsigned char vec_size = sizeof...(other_axes);
        // }

        bool isSetted() const;
        

        /* ******* */
        /* DISPLAY */
        /* ******* */

        void displayCoordX() const;
        void displayCoordY() const;
        void displayCoordZ() const;
        void displayCoordOnAxe(unsigned char axe_number) const;
        void displayCoords() const;
        void displayCoords(std::string title) const;

        /* ********* */
        /* OPERATION */
        /* ********* */

        bool isEqualTo(const Coords& reference) const;
        bool isUpperThan(const Coords& reference) const;
        bool isLowerThan(const Coords &reference) const;
        friend bool operator == (const Coords& to_compare, const Coords& reference);
        friend bool operator != (const Coords &to_compare, const Coords &reference);
        friend bool operator > (const Coords &to_compare, const Coords &reference);
        friend bool operator < (const Coords &to_compare, const Coords &reference);

        Coords addCoords(const Coords &to_add) const;
        Coords addCoords(float to_add) const;
        Coords substractCoords(const Coords &to_sub) const;
        Coords substractCoords(float to_sub) const;
        friend Coords operator + (const Coords &reference, const Coords &to_add);
        friend Coords operator + (const Coords &reference, float to_add);
        friend Coords operator + (float to_add, const Coords &reference);
        friend Coords operator - (const Coords &reference, const Coords &to_sub);
        friend Coords operator - (const Coords &reference, float to_sub);

};

#endif // COORDS_H_INCLUDED
