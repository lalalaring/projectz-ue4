#pragma once

#include "model/Position.h"

namespace prz {
    namespace mdl {

        class ZWeight {
        public:
            static const ZWeight kInfinity;

            ZWeight();
            ZWeight(int value);

            bool operator==(const ZWeight& other) const;
            bool operator!=(const ZWeight& other) const;
            bool operator>(const ZWeight& other) const;
            const ZWeight operator+(const ZWeight& other) const;

        private:
            static const int kInfiniteWeight;

            int mValue;
        };

        struct ZWeightedCell {
            ZWeightedCell();
            ZWeightedCell(const ZPosition& pPosition, const ZWeight& pPathToCellWeight, const ZWeight& pPathFromCellEstimatedWeight);

            ZWeight GetTotalPathWeight() const;

            ZPosition position;

            ZWeight pathToCellWeight;
            ZWeight pathFromCellEstimatedWeight;

        };

    }
}