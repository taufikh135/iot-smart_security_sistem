#pragma once

#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>

class MP3Player {
    private:
        DFRobotDFPlayerMini player;

    public:
        MP3Player();

        /**
         * Menginisialisasi MP3 player
         * @param serial objek serial
         * @return void
         */
        void begin(HardwareSerial& serial);

        /**
         * Mengatur volume
         * @param volume nilai volume dari 0 sampai 30
         */
        void setVolume(int volume);

        /**
         * Memainkan musik berdasarkan index
         * @param index index musik
         */
        void playByIndex(int index, bool isLoop = false);

        /**
         * Menstop Musik
         * @return void
        */
        void stop();
        DFRobotDFPlayerMini& getPlayer();
};