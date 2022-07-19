#pragma once

#include <vector>
#include <mutex>

#include "Swimmer.h"

class SwimmingContest{
    std::vector<Swimmer> participants;
    std::vector<Swimmer> placements;
    std::mutex placementsAccess;
    float contestLength;

    void processParticipant(Swimmer* participant);
    void displayContestState();
    bool contestOver();

public:
    void startContest();
    void inputParticipants();
};