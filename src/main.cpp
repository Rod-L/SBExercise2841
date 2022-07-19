#include "Swimmer.h"
#include "SwimmingContest.h"

int main() {
    auto contest = new SwimmingContest;
    contest->inputParticipants();
    contest->startContest();
    delete contest;
}
