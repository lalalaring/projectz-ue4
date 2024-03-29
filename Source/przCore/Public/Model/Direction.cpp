#include "przCorePCH.h"

#include <algorithm>
#include <cmath>

#include "Model/Direction.h"
#include "Utils/LOG.h"

namespace prz {
namespace mdl {

static const double kPi = 3.14159265359;

typedef std::map<int, ZPositionDiff> ZPredictedMovesMap;

static const ZPredictedMovesMap kPredictedMoves = {
        {0, ZPositionDiff(1, 0)},
        {45, ZPositionDiff(1, -1)},
        {90, ZPositionDiff(0, -1)},
        {135, ZPositionDiff(-1, -1)},
        {180, ZPositionDiff(-1, 0)},
        {225, ZPositionDiff(-1, 1)},
        {270, ZPositionDiff(0, 1)},
        {315, ZPositionDiff(1, 1)}};

static const int kDirectionToAngle[] = {
        0,      // Forward
        90,     // Left
        270,    // Right
        180,    // Back
        45,     // ForwardLeft
        315,    // ForwardRight
        135,    // BackLeft
        225     // BackRight
};

const ZDirection ZDirection::kForward;
const ZDirection ZDirection::kLeft(EDirection::Left);
const ZDirection ZDirection::kRight(EDirection::Right);
const ZDirection ZDirection::kBack(EDirection::Back);

ZDirection::ZDirection()
    : mAngle(0) {
}

ZDirection::ZDirection(EDirection direction)
    : mAngle(0) {
    Turn(direction);
}

EDirection ZDirection::GetDirection() const {
    static const int kDirectionCount = sizeof(kDirectionToAngle) / sizeof(kDirectionToAngle[0]);
    for (int i = 0; i < kDirectionCount; ++i) {
        if (kDirectionToAngle[i] == mAngle) {
            return static_cast<EDirection>(i);
        }
    }
    
    LOGD("Can't find direction for angle = %d", mAngle);
    
    return EDirection::Forward;
}

ZDirection& ZDirection::Turn(EDirection direction) {
    Turn(kDirectionToAngle[(int)direction]);
    
    return *this;
}

ZDirection ZDirection::TurnCopy(EDirection direction) const {
    ZDirection directionCopy(*this);
    directionCopy.Turn(direction);

    return directionCopy;
}

float ZDirection::GetAngleFromDiff(const ZPositionDiff& diff) {
    int dx = diff.GetdX();
    int dy = -diff.GetdY();
    float alpha = atan2(dy, dx);
    alpha = alpha / kPi * 180.0;

    return alpha;
}

ZPositionDiff ZDirection::GetPositionDiff(int angle) {
    ZPredictedMovesMap::const_iterator pos = kPredictedMoves.find(angle);

    ZPositionDiff diff;
    if (pos != kPredictedMoves.end()) {
        diff = pos->second;
    } else {
        LOGE("Got unsupported angle %d", angle);
    }

    return diff;
}

ZPositionDiff ZDirection::PredictMove() const {
    return GetPositionDiff(mAngle);
}

void ZDirection::Align(const ZPositionDiff& diff) {
    int angle = GetAngleFromDiff(diff);
    int discreteDiff = round((angle - mAngle) / 45.0f) * 45;

    Turn(discreteDiff);
}

void ZDirection::Turn(int angle) {
    int newAngle = mAngle + angle;
    while (newAngle < 0) {
        newAngle += 360;
    }
    newAngle %= 360;

    mAngle = newAngle;
}

}
}
