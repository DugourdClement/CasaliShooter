/**
 *
 * @file    audioengine.h
 * @author  Clément Mathieu--Drif
 * @date    Septembre 2020
 * @version 1.0
 * @brief   Gestionnaire audio de minGL
 *
 **/

#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <memory>
#include <list>
#include <SFML/Audio.hpp> // based on SFML

/**
 * @namespace nsAudio
 * @brief Espace de nom pour les utilitaires audio. Il est conseillé d'utiliser des fichiers .wav
 */
namespace nsAudio
{
/**
 * @class AudioEngine
 * @brief Une classe de gestion des effets audio et de la musique
 */
class AudioEngine
{

public:
    /**
     * @brief Définit le fichier audio de la musique
     * @param[in] fileName : nom du fichier
     * @param[in] loop : indique si la musique est lue en boucle ou non (oui par défaut)
     * @fn void setMusic(const std::string& fileName, bool loop = true);
     */
    void setMusic(const std::string& fileName, bool loop = true);

    /**
     * @brief Met en pause ou relance la musique
     * @fn void toggleMusicPlaying();
     */
    void toggleMusicPlaying();

    /**
     * @brief Règle l'état de lecture de la musique
     * @param[in] playing : Nouvel état de lecture
     * @fn void setMusicPlaying(bool playing);
     */
    void setMusicPlaying(bool playing);

    /**
     * @brief Récupère l'état de lecture de la musique
     * @fn bool isMusicPlaying() const;
     */
    bool isMusicPlaying() const;

    /**
     * @brief Charge un fichier audio dans un buffer
     * @fn void loadSound(const std::string & fileName);
     */
    void loadSound(const std::string& fileName);

    /**
     * @brief Retire un buffer de la liste
     * @fn void removeBuffer(const std::string & fileName);
     */
    void removeBuffer(const std::string & fileName);

    /**
     * @brief Vide la liste des buffers
     * @fn void emptyBufferList();
     */
    void emptyBufferList();

    /**
     * @brief Relance la musique depuis le début
     * @fn void startMusicFromBeginning();
     */
    void startMusicFromBeginning();

    /**
     * @brief Joue un son depuis un buffer
     * @param[in] fileName : nom du fichier
     * @fn void playSoundFromBuffer(const std::string& fileName);
     */
    void playSoundFromBuffer(const std::string& fileName);

    /**
     * @brief Joue un son depuis un fichier
     * @param[in] fileName : nom du fichier
     * @fn void playSoundFromFile(const std::string& fileName);
     */
    void playSoundFromFile(const std::string& fileName);

private:
    /**
     * @brief m_buffers : Liste des buffers utilisés par les éléments de m_sounds
     */
    std::list<std::pair<std::string, sf::SoundBuffer>> m_buffers;

    /**
     * @brief m_sounds : Liste des effets audio en cours de lecture depuis des buffers
     */
    std::list<sf::Sound> m_sounds;

    /**
     * @brief m_soundsFromFiles : Liste des effets audio en cours de lecture depuis des fichiers
     */
    std::list<sf::Music> m_soundsFromFiles;

    /**
     * @brief m_music : Musique principale
     */
    sf::Music m_music;

    /**
     * @brief Retire les sons terminés des listes m_sounds et m_soundsFromFiles
     * @fn void removeOldSounds();
     */
    void removeOldSounds();

}; // class AudioEngine

} // namespace nsAudio

#endif // AUDIOENGINE_H
