/**
 *
 * @file    shape.cpp
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Représente une forme
 *
 **/

#include "mingl/shape/shape.h"

nsShape::Shape::Shape(const nsGraphics::RGBAcolor &inColor, const nsGraphics::RGBAcolor &borderColor)
    : m_fillColor(inColor)
    , m_borderColor(borderColor)
{} // Shape()

const nsGraphics::RGBAcolor &nsShape::Shape::getFillColor() const
{
    return m_fillColor;
} // getFillColor()

void nsShape::Shape::setFillColor(const nsGraphics::RGBAcolor &fillColor)
{
    m_fillColor = fillColor;
} // setFillColor()

const nsGraphics::RGBAcolor &nsShape::Shape::getBorderColor() const
{
    return m_borderColor;
} // getBorderColor()

void nsShape::Shape::setBorderColor(const nsGraphics::RGBAcolor &borderColor)
{
    m_borderColor = borderColor;
} // setBorderColor()
