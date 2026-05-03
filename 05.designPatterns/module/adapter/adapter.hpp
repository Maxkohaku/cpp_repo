#pragma once
#ifndef _ADAPTER_HPP_
#define _ADAPTER_HPP_
#include <iostream>
#include <string>
#include <memory>
using namespace std;
class Mp3Player {
public:
    Mp3Player() = default;
    ~Mp3Player() = default;
    void play(const string& file) {
        cout << "play mp3 file : " << file << endl; 
    }
};
enum class AudioType {
    mp3,
    mp4,
    vlc,
    avi
};
class AudioPlayerOld {
public:
    AudioPlayerOld() = default;
    ~AudioPlayerOld() = default;
    void playMp4(const string& file) {
        cout << "play mp4 file : " << file << endl; 
    }
    void playVlc(const string& file) {
        cout << "play vlc file : " << file << endl; 
    }
};
class AudioPlayerAbstract {
public:
    AudioPlayerAbstract() = default;
    virtual ~AudioPlayerAbstract() = default;
    virtual void play(const AudioType& type, const string& file) = 0;
};
class AudioPlayerAdapter : public AudioPlayerAbstract {
public:
    AudioPlayerAdapter() : _mp3Player(make_unique<Mp3Player>()), _audioPlayerOld(make_unique<AudioPlayerOld>()) {}
    ~AudioPlayerAdapter() = default;
    void play(const AudioType& type, const string& file) override {
        switch (type)
        {
        case AudioType::mp3:
            _mp3Player->play(file);
            break;
        case AudioType::mp4:
            _audioPlayerOld->playMp4(file);
            break;
        case AudioType::vlc:
            _audioPlayerOld->playVlc(file);
            break;
        default:
            cout << "unsupported audio type" << endl;
            break;
        }
    } 
private:
    unique_ptr<Mp3Player> _mp3Player;
    unique_ptr<AudioPlayerOld> _audioPlayerOld;
};
void adapter() {
    auto player = make_unique<AudioPlayerAdapter>();
    player->play(AudioType::mp3, "example.mp3");
    player->play(AudioType::mp4, "example.mp4");
    player->play(AudioType::vlc, "example.vlc");
    player->play(AudioType::avi, "example.avi");
}
#endif /*_ADAPTER_HPP_*/