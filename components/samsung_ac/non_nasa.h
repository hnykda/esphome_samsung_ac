#pragma once

#include <vector>
#include <iostream>
#include "protocol.h"

namespace esphome
{
    namespace samsung_ac
    {
        enum class NonNasaFanspeed : uint8_t
        {
            Auto = 0,
            Low = 2,
            Medium = 4,
            High = 5,
            Fresh = 6
        };

        enum class NonNasaMode : uint8_t
        {
            Heat = 0x01,
            Cool = 0x02,
            Dry = 0x04,
            Fan = 0x08,
            Auto_Heat = 0x21,
            Auto = 0x22
        };

        enum class NonNasaWindDirection : uint8_t
        {
            Vertical = 26,
            Horizontal = 27,
            FourWay = 28,
            Stop = 31
        };

        struct NonNasaCommand20
        {
            uint8_t target_temp = 0;
            uint8_t room_temp = 0;
            uint8_t pipe_in = 0;
            uint8_t pipe_out = 0;

            NonNasaFanspeed fanspeed = NonNasaFanspeed::Auto;
            NonNasaMode mode = NonNasaMode::Heat;
            NonNasaWindDirection wind_direction = NonNasaWindDirection::Stop;

            bool power = false;

            std::string to_string();
        };

        struct NonNasaPacket
        {
            std::string src;
            std::string dst;

            NonNasaCommand20 command;

            std::vector<uint8_t> encode();

            bool decode(std::vector<uint8_t> &data);
            std::string to_string();
        };

        void process_non_nasa_message(std::vector<uint8_t> data, MessageTarget *target);
    } // namespace samsung_ac
} // namespace esphome
