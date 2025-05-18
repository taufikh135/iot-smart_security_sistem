#include "MP3Player.h"

MP3Player::MP3Player(): player() {}

void MP3Player::begin(HardwareSerial& serial) {
    Serial.println("Initializing DFPlayer...");

    if (this->player.begin(serial)) {
        Serial.println("MP3 Player terhubung");
        return;
    }

    Serial.println("Unable to begin MP3 Player");
    while (true);
}

void MP3Player::setVolume(int volume) {
    this->player.volume(volume);
}

void MP3Player::playByIndex(int index, bool isLoop) {
    if (isLoop) {
        this->player.disableLoop();
    } else {
        this->player.enableLoop();
    }

    this->player.play(index);
}

void MP3Player::stop() {
    this->player.stop();
}

DFRobotDFPlayerMini& MP3Player::getPlayer() {
    return this->player;
}