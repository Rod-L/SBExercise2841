#include <iostream>
#include <thread>

#include "Swimmer.h"
#include "SwimmingContest.h"

void SwimmingContest::processParticipant(Swimmer* participant) {
    while (participant->position < contestLength) {
        participant->move();
        std::this_thread::sleep_for(std::chrono::milliseconds (500));
    }
    this->placementsAccess.lock();
    this->placements.push_back(*participant);
    this->placementsAccess.unlock();
    std::cout << participant->getName() << " scored at " << participant->currentTimestampRepr() << "!" << std::endl;
}

void SwimmingContest::displayContestState() {
    for (int i = 0; i < participants.size(); ++i) {
        auto p = participants[i];
        printf("Line #%d: %s %.1f\n", i + 1, p.getName().c_str(), std::min(p.position, contestLength));
    }
}

bool SwimmingContest::contestOver() {
    for (auto& p : participants) {
        if (p.position < contestLength) return false;
    }
    return true;
}

void SwimmingContest::startContest() {
    std::vector<std::thread> lines;
    for (auto & participant : participants) {
        lines.emplace_back(&SwimmingContest::processParticipant, this, &participant);
    }

    while (!contestOver()) {
        displayContestState();
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds (1));
    }

    for (auto & line : lines) {
        if (line.joinable()) line.join();
    }

    std::cout << std::endl << "Placements:" << std::endl;
    for (int i = 0; i < placements.size(); ++i) {
        std::cout << i + 1 << ". " << placements[i].getName() << " - " << placements[i].currentTimestampRepr() << std::endl;
    }
}

void SwimmingContest::inputParticipants() {
    std::cout << "What is length of the contest (meters)?" << std::endl;
    std::cin >> contestLength;

    std::cout << "How many swimmers do participate in the contest?" << std::endl;
    int amount;
    std::cin >> amount;

    for (int i = 0; i < amount; ++i) {
        std::string name;
        float speed;

        std::cout << "What is name of the swimmer #" << i + 1 << "?" << std::endl;
        std::cin >> name;
        std::cout << "What is his swimming speed (meters/second)?" << std::endl;
        std::cin >> speed;
        participants.emplace_back(name, speed);
    }
}