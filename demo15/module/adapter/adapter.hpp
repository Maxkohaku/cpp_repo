#pragma once
#ifndef _ADAPTER_HPP_
#define _ADAPTER_HPP_
#include <iostream>
#include <string>
#include <memory>
class Mp3Player
{
public:
    Mp3Player() = default;
    ~Mp3Player() = default;
    void playMp3(const std::string fileName)
    {
        std::cout << "playing file: " << fileName << std::endl;
    }
};
class AudioPlayer
{
public:
    AudioPlayer() = default;
    virtual ~AudioPlayer() = default;
    virtual void play(const std::string& audioTyep, const std::string& fileName) = 0;
};
class AudioPlayerAdapter : public AudioPlayer
{
public:
    AudioPlayerAdapter() : _mp3Player(std::make_unique<Mp3Player>()) {}
    ~AudioPlayerAdapter() = default;
    void play(const std::string& audioTyep, const std::string& fileName) override
    {
        if (audioTyep == "mp3")
        {
            _mp3Player->playMp3(fileName);
        }
        else if (audioTyep == "mp4")
        {
            std::cout << "playing file: " << fileName << std::endl;
        }
        else if (audioTyep == "vlc")
        {
            std::cout << "playing file: " << fileName << std::endl;
        }
        else
        {
            std::cout << "unsupported audio type: " << audioTyep << std::endl;
        }
    }
private:
    std::unique_ptr<Mp3Player> _mp3Player;
};
void adapter()
{
    auto player = std::make_unique<AudioPlayerAdapter>();
    player->play("mp3", "example.mp3");
    player->play("mp4", "example.mp4");
    player->play("vlc", "example.vlc");
    player->play("avi", "example.avi");
}
#endif // _ADAPTER_HPP_