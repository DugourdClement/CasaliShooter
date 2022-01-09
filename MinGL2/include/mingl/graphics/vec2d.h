/**
 *
 * @file    vec2d.h
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.3
 * @brief   Représente un vecteur sur deux dimensions
 *
 **/

#ifndef VEC2D_H
#define VEC2D_H

#include <ostream>

#include "../tools/ieditable.h"

namespace nsGraphics
{

/**
 * @class Vec2D
 * @brief Classe représentant un vecteur deux-dimensionnel
 */
class Vec2D : public nsUtil::IEditable
{

public:
    /**
     * @brief Constructeur pour la classe Vec2D
     * @param[in] x : Position X (abscisse) du vecteur
     * @param[in] y : Position Y (ordonnée) du vecteur
     * @fn Vec2D(const int& x = 0, const int& y = 0);
     */
    Vec2D(const int& x = 0, const int& y = 0);

    /**
     * @brief Constructeur de recopie pour la classe Vec2D
     * @param[in] pos : Vec2D a copier
     * @fn Vec2D(const Vec2D& pos);
     */
    Vec2D(const Vec2D& pos);

    /**
     * @brief Opérateur unaire plus
     * @fn Vec2D operator+() const;
     */
    Vec2D operator+() const;

    /**
     * @brief Opérateur unaire moins
     * @fn Vec2D operator-() const;
     */
    Vec2D operator-() const;

    /**
     * @brief Opérateur d'addition
     * @param[in] pos : Vecteur a additionner
     * @fn Vec2D operator+(const Vec2D& pos) const;
     */
    Vec2D operator+(const Vec2D& pos) const;

    /**
     * @brief Opérateur de soustraction
     * @param[in] pos : Vecteur a soustraire
     * @fn Vec2D operator-(const Vec2D& pos) const;
     */
    Vec2D operator-(const Vec2D& pos) const;

    /**
     * @brief Opérateur de multiplication
     * @param[in] pos : Vecteur a multiplier
     * @fn Vec2D operator*(const Vec2D& pos) const;
     */
    Vec2D operator*(const Vec2D& pos) const;

    /**
     * @brief Opérateur de multiplication
     * @param[in] n : Nombre avec lequel multiplier le vecteur actuel
     * @fn Vec2D operator*(const float& n) const;
     */
    Vec2D operator*(const float& n) const;

    /**
     * @brief Opérateur de division
     * @param[in] pos : Vecteur a diviser
     * @fn Vec2D operator/(const Vec2D& pos) const;
     */
    Vec2D operator/(const Vec2D& pos) const;

    /**
     * @brief Opérateur de division
     * @param[in] n : Nombre avec lequel diviser le vecteur actuel
     * @fn Vec2D operator/(const float& n) const;
     */
    Vec2D operator/(const float& n) const;

    /**
     * @brief Opérateur modulo
     * @param[in] pos : Vecteur avec lequel faire un modulo
     * @fn Vec2D operator%(const Vec2D& pos) const;
     */
    Vec2D operator%(const Vec2D& pos) const;

    /**
     * @brief Opérateur d'égalité
     * @param[in] pos : Vecteur avec lequel vérifier l'égalité
     * @fn bool operator==(const Vec2D& pos) const;
     */
    bool operator==(const Vec2D& pos) const;

    /**
     * @brief Opérateur d'inégalité
     * @param[in] pos : Vecteur avec lequel vérifier l'inégalité
     * @fn bool operator!=(const Vec2D& pos) const;
     */
    bool operator!=(const Vec2D& pos) const;

    /**
     * @brief Opérateur de stricte infériorité
     * (Vérifie la stricte infériorité de la magnitude des deux vecteurs)
     * @param[in] pos : Vecteur avec lequel vérifier la stricte infériorité
     * @fn bool operator<(const Vec2D& pos) const;
     */
    bool operator<(const Vec2D& pos) const;

    /**
     * @brief Opérateur de stricte supériorité
     * (Vérifie la stricte supériorité de la magnitude des deux vecteurs)
     * @param[in] pos : Vecteur avec lequel vérifier la stricte supériorité
     * @fn bool operator>(const Vec2D& pos) const;
     */
    bool operator>(const Vec2D& pos) const;

    /**
     * @brief Opérateur d'infériorité
     * (Vérifie l'infériorité de la magnitude des deux vecteurs)
     * @param[in] pos : Vecteur avec lequel vérifier l'infériorité
     * @fn bool operator<=(const Vec2D& pos) const;
     */
    bool operator<=(const Vec2D& pos) const;

    /**
     * @brief Opérateur de supériorité
     * (Vérifie la supériorité de la magnitude des deux vecteurs)
     * @param[in] pos : Vecteur avec lequel vérifier la supériorité
     * @fn bool operator>=(const Vec2D& pos) const;
     */
    bool operator>=(const Vec2D& pos) const;

    /**
     * @brief Opérateur d'assignement
     * @param[in] pos : Vecteur source
     * @fn Vec2D& operator=(const Vec2D& pos);
     */
    Vec2D& operator=(const Vec2D& pos);

    /**
     * @brief Opérateur d'addition avec assignement
     * @param[in] pos : Vecteur avec lequel additionner le vecteur actuel
     * @fn Vec2D& operator+=(const Vec2D& pos);
     */
    Vec2D& operator+=(const Vec2D& pos);

    /**
     * @brief Opérateur de soustraction avec assignement
     * @param[in] pos : Vecteur avec lequel soustraire le vecteur actuel
     * @fn Vec2D& operator-=(const Vec2D& pos);
     */
    Vec2D& operator-=(const Vec2D& pos);

    /**
     * @brief Opérateur de multiplication avec assignement
     * @param[in] pos : Vecteur avec lequel multiplier le vecteur actuel
     * @fn Vec2D& operator*=(const Vec2D& pos);
     */
    Vec2D& operator*=(const Vec2D& pos);

    /**
     * @brief Opérateur de division avec assignement
     * @param[in] pos : Vecteur avec lequel diviser le vecteur actuel
     * @fn Vec2D& operator/=(const Vec2D& pos);
     */
    Vec2D& operator/=(const Vec2D& pos);

    /**
     * @brief Opérateur modulo avec assignement
     * @param[in] pos : Vecteur avec lequel faire un modulo sur le vecteur actuel
     * @fn Vec2D& operator%=(const Vec2D& pos);
     */
    Vec2D& operator%=(const Vec2D& pos);

    /**
     * @brief Retourne le vecteur le plus petit entre les deux passés en argument
     * @param[in] p1 : Premier vecteur
     * @param[in] p2 : Second vecteur
     * @fn static Vec2D min(const Vec2D& p1, const Vec2D& p2);
     */
    static Vec2D min(const Vec2D& p1, const Vec2D& p2);

    /**
     * @brief Retourne vrai si le premier vecteur est le plus petit des deux
     * @param[in] p1 : Premier vecteur
     * @param[in] p2 : Second vecteur
     * @fn static bool minf(const Vec2D& p1, const Vec2D& p2);
     */
    static bool minf(const Vec2D& p1, const Vec2D& p2);

    /**
     * @brief Retourne vrai si le vecteur actuel est compris entre deux vecteurs formant un rectangle
     * @param[in] firstCorner : Premier vecteur
     * @param[in] secondCorner : Second vecteur
     * @fn bool isColliding(Vec2D firstCorner, Vec2D secondCorner) const;
     */
    bool isColliding(Vec2D firstCorner, Vec2D secondCorner) const;

    /**
     * @brief Calcule la magnitude de ce vecteur
     * @return Magnitude du vecteur
     * @fn double computeMagnitude() const;
     */
    double computeMagnitude() const;

    /**
     * @brief Récupère la position X (abscisse)
     * @return Une référence constante vers m_x
     * @fn int getX() const;
     */
    int getX() const;

    /**
     * @brief Définit la nouvelle position X (abscisse)
     * @param[in] x : Nouvelle position X
     * @fn void setX(int x);
     */
    void setX(int x);

    /**
     * @brief Récupère la position Y (ordonnée)
     * @return Une référence constante vers m_y
     * @fn int getY() const;
     */
    int getY() const;

    /**
     * @brief Définit la nouvelle position Y (ordonnée)
     * @param[in] y : Nouvelle position Y
     * @fn void setY(int y);
     */
    void setY(int y);

protected:
    virtual std::ostream& _Edit(std::ostream& os = std::cout) const override;

private:
    /**
     * @brief m_x : Position X (abscisse)
     */
    int m_x;

    /**
     * @brief m_y : Position Y (ordonnée)
     */
    int m_y;

}; // class Vec2D

} // namespace nsGraphics

#endif // VEC2D_H
