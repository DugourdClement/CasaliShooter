/**
 *
 * @file    rgbacolor.cpp
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.1
 * @brief   Représente une couleur RGBA
 *
 **/

#include "mingl/graphics/rgbacolor.h"

nsGraphics::RGBAcolor::RGBAcolor(const GLubyte& red, const GLubyte& green, const GLubyte& blue, const GLubyte& alpha)
    : m_red(red)
    , m_green(green)
    , m_blue(blue)
    , m_alpha(alpha)
{} // RGBAcolor()

bool nsGraphics::RGBAcolor::operator==(const RGBAcolor& col) const
{
    return col.m_red == m_red && col.m_green == m_green && col.m_blue == m_blue && col.m_alpha == m_alpha;
} // operator==()

bool nsGraphics::RGBAcolor::operator!=(const RGBAcolor& col) const
{
    return col.m_red != m_red || col.m_green != m_green || col.m_blue != m_blue || col.m_alpha != m_alpha;
} // operator!=()

nsGraphics::RGBAcolor nsGraphics::RGBAcolor::operator+(const RGBAcolor& rhs) const
{
    return RGBAcolor(m_red + rhs.m_red, m_green + rhs.m_green, m_blue + rhs.m_blue, m_alpha + rhs.m_alpha);
} // operator+()

nsGraphics::RGBAcolor nsGraphics::RGBAcolor::operator*(const float& rhs) const
{
    return RGBAcolor(m_red * rhs, m_green * rhs, m_blue * rhs, m_alpha * rhs);
} // operator*()

std::ostream &nsGraphics::RGBAcolor::_Edit(std::ostream& os) const
{
    os << "R: " << int(m_red) << ", G: " << int(m_green) << ", B: " << int(m_blue) << ", A: " << int(m_alpha);
    return os;
} // _Edit()

GLubyte nsGraphics::RGBAcolor::getAlpha() const
{
    return m_alpha;
} // getAlpha()

void nsGraphics::RGBAcolor::setAlpha(const GLubyte& alpha)
{
    m_alpha = alpha;
} // setAlpha()

GLubyte nsGraphics::RGBAcolor::getBlue() const
{
    return m_blue;
} // getBlue()

void nsGraphics::RGBAcolor::setBlue(const GLubyte& blue)
{
    m_blue = blue;
} // setBlue()

GLubyte nsGraphics::RGBAcolor::getGreen() const
{
    return m_green;
} // getGreen()

void nsGraphics::RGBAcolor::setGreen(const GLubyte& green)
{
    m_green = green;
} // setGreen()

GLubyte nsGraphics::RGBAcolor::getRed() const
{
    return m_red;
} // getRed()

void nsGraphics::RGBAcolor::setRed(const GLubyte& red)
{
    m_red = red;
} // setRed()
