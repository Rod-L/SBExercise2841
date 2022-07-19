#pragma once

#include <string>

class Swimmer{
    std::string name;
    float speed;
    uint64_t startTimestamp;
    uint64_t lastMoveTimestamp;

    static uint64_t timestamp();

public:
    float position;

    Swimmer(std::string& inName, float inSpeed);
    void move();
    std::string getName() const;
    std::string currentTimestampRepr() const;
};