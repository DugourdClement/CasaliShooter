/**
 *
 * @file    sprite.cpp
 * @author  Alexandre Sollier
 * @date    Janvier 2020
 * @version 1.0
 * @brief   Image pouvant être chargé depuis un fichier
 *
 **/

#include "mingl/gui/sprite.h"

#include <unistd.h>
#include <fcntl.h>
#include <iostream>

#include "mingl/macros.h"
#include "mingl/exception/cexception.h"

nsGui::Sprite::Sprite(const std::string& filename, const nsGraphics::Vec2D& position)
    : m_position(position)
{
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd < 0)
    {
        std::cerr << "[DisplaySprite] Sprite file \"" << filename << "\" could not be opened." << std::endl;
        throw nsException::CException(filename + " cannot be loaded", nsException::KFileError);
    }

    FileBegin fileBegin;
    read(fd, &fileBegin, sizeof(FileBegin));

    for (uint32_t i = 0; i < fileBegin.pixelCount; ++i)
    {
        GLubyte red, green, blue, alpha;
        read(fd, &red,    sizeof(red));
        read(fd, &green,  sizeof(green));
        read(fd, &blue,   sizeof(blue));
        read(fd, &alpha,  sizeof(alpha));

        m_pixelData.push_back(nsGraphics::RGBAcolor(red, green, blue, alpha));
    }

    close(fd);

    m_rowSize = fileBegin.rowSize;
} // Sprite()

nsGui::Sprite::Sprite(const std::vector<nsGraphics::RGBAcolor>& pixelData, const uint32_t& rowSize, const nsGraphics::Vec2D& position)
    : m_position(position)
    , m_rowSize(rowSize)
    , m_pixelData(pixelData)
{} // Sprite()

void nsGui::Sprite::draw(MinGL& window) const
{
    UNUSED(window);

    glBegin(GL_POINTS);

    for (unsigned i = 0; i < m_pixelData.size(); ++i)
    {
        const nsGraphics::RGBAcolor actualColor = m_pixelData[i];
        const unsigned x = i % m_rowSize;
        const unsigned y = i / m_rowSize;

        glColor4ub(actualColor.getRed(), actualColor.getGreen(), actualColor.getBlue(), actualColor.getAlpha());
        glVertex2i(x + m_position.getX(), y + m_position.getY());
    }

    glEnd();
} // draw()

void nsGui::Sprite::getValues(const int &id, std::vector<float> &values)
{
    switch (id) {
        case TRANSITION_POSITION:
            values[0] = m_position.getX();
            values[1] = m_position.getY();

            break;
    }
} // getValues()

void nsGui::Sprite::setValues(const int &id, const std::vector<float> &values)
{
    switch (id) {
        case TRANSITION_POSITION:
            m_position.setX(values[0]);
            m_position.setY(values[1]);

            break;
    }
} // setValues()

const uint32_t& nsGui::Sprite::getRowSize() const
{
    return m_rowSize;
} // getRowSize()

const std::vector<nsGraphics::RGBAcolor>& nsGui::Sprite::getPixelData() const
{
    return m_pixelData;
} // getPixelData()

const nsGraphics::Vec2D& nsGui::Sprite::getPosition() const
{
    return m_position;
} // getPosition()

void nsGui::Sprite::setPosition(const nsGraphics::Vec2D& position)
{
    m_position = position;
} // setPosition()

nsGraphics::Vec2D nsGui::Sprite::computeSize() const
{
    return nsGraphics::Vec2D(m_pixelData.size() / m_rowSize, m_rowSize);
} // computeSize()
