#include "przCorePrivatePCH.h"

#include <algorithm>
#include <cmath>

#include "model/Direction.h"
#include "utils/LOG_ANSI.h"

namespace prz {
    namespace mdl {
        const double ZDirection::kPi = 3.14159265359;

        const ZDirection::ZPredictedMovesMap ZDirection::kPredictedMoves = {
            {0, ZPositionDiff(1.0f, 0.0f)},
            {45, ZPositionDiff(1.0f, -1.0f)},
            {90, ZPositionDiff(0.0f, -1.0f)},
            {135, ZPositionDiff(-1.0f, -1.0f)},
            {180, ZPositionDiff(-1.0f, 0.0f)},
            {225, ZPositionDiff(-1.0f, 1.0f)},
            {270, ZPositionDiff(0.0f, 1.0f)},
            {315, ZPositionDiff(1.0f, 1.0f)}};

        const ZDirection::ZTurnDirectionToAngleMap ZDirection::kTurnDirectionToAngle = {
            {ETurnDirection::Forward, 0},
            {ETurnDirection::Left, 90},
            {ETurnDirection::Right, -90},
            {ETurnDirection::Back, 180},
            {ETurnDirection::ForwardLeft, 45},
            {ETurnDirection::ForwardRight, -45},
        };

        ZDirection::ZDirection() {
            mAngle = 0;
        }

        ZDirection::~ZDirection() {
        }

        void ZDirection::Turn(ETurnDirection::Type direction) {
            auto pos = kTurnDirectionToAngle.find(direction);
            if (pos != kTurnDirectionToAngle.end()) {
                Turn(pos->second);
            } else {
                LOGE("Got unsupported ETurnDirection = %d", direction);
            }
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