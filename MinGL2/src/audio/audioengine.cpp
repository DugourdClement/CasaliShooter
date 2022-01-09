/**
 *
 * @file    audioengine.cpp
 * @author  Clément Mathieu--Drif
 * @date    Septembre 2020
 * @version 1.1
 * @brief   Gestionnaire audio de minGL
 *
 **/

#include "mingl/audio/audioengine.h"
#include "mingl/exception/cexception.h"

using namespace std;

void nsAudio::AudioEngine::setMusic(const std::string& fileName, bool loop /* = true */)
{
    if (!m_music.openFromFile(fileName))
        throw nsException::CException(fileName + " cannot be loaded", nsException::KFileError);

    m_music.setLoop(loop);
} // setMusic()

void nsAudio::AudioEngine::toggleMusicPlaying()
{
    setMusicPlaying(m_music.getStatus() != sf::Music::Status::Playing);
} // toggleMusic()

void nsAudio::AudioEngine::setMusicPlaying(bool playing)
{
    if (playing)
        m_music.play();
    else
        m_music.pause();
} // setMusicPlaying()

bool nsAudio::AudioEngine::isMusicPlaying() const
{
    return m_music.getStatus() == sf::Music::Status::Playing;
} // isMusicPlaying()

void nsAudio::AudioEngine::loadSound(const std::string & fileName)
{
    for(list<pair<string, sf::SoundBuffer>>::iterator it(m_buffers.begin()); it != m_buffers.end(); ++it)
        if(it->first == fileName)
            return;
    sf::SoundBuffer sb;
    if(!sb.loadFromFile(fileName))
        throw nsException::CException(fileName + " cannot be loaded", nsException::KFileError);
    m_buffers.push_front(make_pair(fileName, sb));
} // loadSound()

void nsAudio::AudioEngine::removeBuffer(const std::string & fileName)
{
    for(list<pair<string, sf::SoundBuffer>>::iterator it(m_buffers.begin()); it != m_buffers.end(); ++it)
    {
        if(it->first == fileName)
        {
            m_buffers.erase(it);
            return;
        }
    }
    throw nsException::CException(fileName + " does not exist", nsException::KErrArg);
} // removeBuffer()

void nsAudio::AudioEngine::emptyBufferList()
{
    m_buffers.clear();
} // emptyBufferList()

void nsAudio::AudioEngine::startMusicFromBeginning()
{
    m_music.stop();
    m_music.play();
} // startMusicFromBeginning()

void nsAudio::AudioEngine::playSoundFromBuffer(const std::string& fileName)
{
    bool ok(false);
    for(list<pair<string, sf::SoundBuffer>>::iterator it(m_buffers.begin()); it != m_buffers.end(); ++it)
    {
        if(it->first == fileName)
        {
            m_sounds.emplace_front(it->second);
            m_sounds.front().play();
            ok = true;
        }
    }
    if(!ok)
        throw nsException::CException(fileName + " buffer not found", nsException::KErrArg);

    removeOldSounds();
} // playSoundFromBuffer()

void nsAudio::AudioEngine::playSoundFromFile(const std::string& fileName)
{
    m_soundsFromFiles.emplace_back();
    if (!m_soundsFromFiles.back().openFromFile(fileName))
        throw nsException::CException("file cannot be loaded", nsException::KFileError);

    m_soundsFromFiles.back().play();

    removeOldSounds();
} // playSoundEffects()

void nsAudio::AudioEngine::removeOldSounds()
{
    for(list<sf::Sound>::iterator it(m_sounds.begin()); it != m_sounds.end(); ++it)
        if(it->getStatus() != sf::Sound::Status::Playing)
            it = m_sounds.erase(it);

    for(list<sf::Music>::iterator it(m_soundsFromFiles.begin()); it != m_soundsFromFiles.end(); ++it)
        if(it->getStatus() != sf::Sound::Status::Playing)
            it = m_soundsFromFiles.erase(it);
} // removeOldSounds()
