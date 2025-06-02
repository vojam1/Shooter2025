//
// Created by sputnik on 6/2/25.
//

#ifndef SCORETRACKERCOMPONENT_H
#define SCORETRACKERCOMPONENT_H

#include "../Common.h"

struct ScoreTrackerComponent {
    int32_t score;

    explicit ScoreTrackerComponent(const int32_t score = 0) : score(score) {}
};

#endif //SCORETRACKERCOMPONENT_H
