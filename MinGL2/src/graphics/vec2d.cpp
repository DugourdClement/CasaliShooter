/**
 *
 * @file    vec2d.cpp
 * @author  Alexandre Sollier
 * @date    Septembre 2020
 * @version 1.3
 * @brief   Représente un vecteur sur deux dimensions
 *
 **/

#include <cmath>

#include "mingl/graphics/vec2d.h"

nsGraphics::Vec2D::Vec2D(const int& x, const int& y)
    : m_x(x)
    , m_y(y)
{} // Vec2D()

nsGraphics::Vec2D::Vec2D(const Vec2D& pos)
    : m_x(pos.getX())
    , m_y(pos.getY())
{} // Vec2D()

nsGraphics::Vec2D nsGraphics::Vec2D::operator+() const
{
    return Vec2D(+m_x, +m_y);
} // operator+()

nsGraphics::Vec2D nsGraphics::Vec2D::operator-() const
{
    return Vec2D(-m_x, -m_y);
} // operator-()

nsGraphics::Vec2D nsGraphics::Vec2D::operator+(const Vec2D& pos) const
{
    return Vec2D(m_x + pos.getX(), m_y + pos.getY());
} // operator+()

nsGraphics::Vec2D nsGraphics::Vec2D::operator-(const Vec2D &pos) const
{
    return Vec2D(m_x - pos.getX(), m_y - pos.getY());
} // operator-()

nsGraphics::Vec2D nsGraphics::Vec2D::operator*(const Vec2D& pos) const
{
    return Vec2D(m_x * pos.getX(), m_y * pos.getY());
} // operator*()

nsGraphics::Vec2D nsGraphics::Vec2D::operator*(const float& n) const
{
    return Vec2D(m_x * n, m_y * n);
} // operator*()

nsGraphics::Vec2D nsGraphics::Vec2D::operator/(const Vec2D &pos) const
{
    return Vec2D(m_x / pos.getX(), m_y / pos.getY());
} // operator/()

nsGraphics::Vec2D nsGraphics::Vec2D::operator/(const float &n) const
{
    return Vec2D(m_x / n, m_y / n);
} // operator/()

nsGraphics::Vec2D nsGraphics::Vec2D::operator%(const Vec2D &pos) const
{
    return Vec2D(m_x % pos.getX(), m_y % pos.getY());
} // operator%()

bool nsGraphics::Vec2D::operator==(const Vec2D& pos) const
{
    return m_x == pos.getX() && m_y == pos.getY();
} // operator==()

bool nsGraphics::Vec2D::operator!=(const Vec2D &pos) const
{
    return m_x != pos.getX() || m_y != pos.getY();
} // operator!=()

bool nsGraphics::Vec2D::operator<(const Vec2D& pos) const
{
    return computeMagnitude() < pos.computeMagnitude();
} // operator<()

bool nsGraphics::Vec2D::operator>(const Vec2D& pos) const
{
    return computeMagnitude() > pos.computeMagnitude();
} // operator>()

bool nsGraphics::Vec2D::operator<=(const Vec2D& pos) const
{
    return computeMagnitude() <= pos.computeMagnitude();
} // operator<=()

bool nsGraphics::Vec2D::operator>=(const Vec2D& pos) const
{
    return computeMagnitude() >= pos.computeMagnitude();
} // operator>=()

nsGraphics::Vec2D& nsGraphics::Vec2D::operator=(const Vec2D& pos)
{
    m_x = pos.getX();
    m_y = pos.getY();

    return *this;
} // operator=()

nsGraphics::Vec2D& nsGraphics::Vec2D::operator+=(const Vec2D& pos)
{
    m_x += pos.getX();
    m_y += pos.getY();

    return *this;
} // operator+=()

nsGraphics::Vec2D &nsGraphics::Vec2D::operator-=(const nsGraphics::Vec2D &pos)
{
    m_x -= pos.getX();
    m_y -= pos.getY();

    return *this;
} // operator-=()

nsGraphics::Vec2D &nsGraphics::Vec2D::operator*=(const nsGraphics::Vec2D &pos)
{
    m_x *= pos.getX();
    m_y *= pos.getY();

    return *this;
} // operator*=()

nsGraphics::Vec2D &nsGraphics::Vec2D::operator/=(const nsGraphics::Vec2D &pos)
{
    m_x /= pos.getX();
    m_y /= pos.getY();

    return *this;
} // operator/=()

nsGraphics::Vec2D &nsGraphics::Vec2D::operator%=(const nsGraphics::Vec2D &pos)
{
    m_x %= pos.getX();
    m_y %= pos.getY();

    return *this;
} // operator%=()

nsGraphics::Vec2D nsGraphics::Vec2D::min(const Vec2D& p1, const Vec2D& p2)
{
    if (p1.getX() < p2.getX()) return p1;
    else if (p1.getX() == p2.getX() && p1.getY() < p2.getY()) return p1;
    return p2;
} // min()

bool nsGraphics::Vec2D::minf(const Vec2D& p1, const Vec2D& p2)
{
    return (p1 == min(p1, p2));
} // minf()

bool nsGraphics::Vec2D::isColliding(Vec2D firstCorner, Vec2D secondCorner) const
{
    // On inverse les coordonnées si nécessaire
    if (secondCorner.getX() < firstCorner.getX())
        std::swap(secondCorner.m_x, firstCorner.m_x);

    if (secondCorner.getY() < firstCorner.getY())
        std::swap(secondCorner.m_y, firstCorner.m_y);

    // On retourne si notre vecteur est entre ces deux coins
    return (operator>=(firstCorner) && operator<=(secondCorner));
} // isColliding()

double nsGraphics::Vec2D::computeMagnitude() const
{
    return sqrt(m_x * m_x + m_y * m_y);
} // getMagnitude()

int nsGraphics::Vec2D::getX() const
{
    return m_x;
} // getX()

void nsGraphics::Vec2D::setX(int x)
{
    m_x = x;
} // setX()

int nsGraphics::Vec2D::getY() const
{
    return m_y;
} // getY()

void nsGraphics::Vec2D::setY(int y)
{
    m_y = y;
} // setY()

std::ostream& nsGraphics::Vec2D::_Edit(std::ostream& os) const
{
    os << "X: " << m_x << ", Y: " << m_y;
    return os;
} // _Edit()
