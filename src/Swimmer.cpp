#include "Swimmer.h"

#include <chrono>

uint64_t Swimmer::timestamp() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

Swimmer::Swimmer(std::string& inName, float inSpeed) {
    name = inName;
    speed = inSpeed;
    position = 0;
    startTimestamp = 0;
    lastMoveTimestamp = 0;
};

void Swimmer::move() {
    if (startTimestamp == 0) {
        startTimestamp = timestamp();
        lastMoveTimestamp = startTimestamp;
        return;
    }

    uint64_t thisTimestamp = timestamp();
    position += static_cast<float>(thisTimestamp - lastMoveTimestamp) / 1000.f * speed;
    lastMoveTimestamp = thisTimestamp;
}

std::string Swimmer::getName() const {
    return name;
}

std::string Swimmer::currentTimestampRepr() const {
    float seconds = static_cast<float>(lastMoveTimestamp - startTimestamp) / 1000;
    int minutes = static_cast<int>(seconds / 60);

    char buff[32];
    std::snprintf(buff, 32, "%dm %.2fs", minutes, seconds - (float)(minutes * 60));

    std::string result;
    result.assign(buff);
    return result;
}
