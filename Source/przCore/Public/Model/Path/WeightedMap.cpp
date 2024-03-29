#include "przCorePCH.h"
#include "Model/Path/WeightedMap.h"

#include <algorithm>
#include <sstream>

#include "Utils/MatrixHelpers.h"

namespace prz {
namespace mdl {
namespace path {

ZWeightedMap::ZWeightedMap(int width, int height, const ZWeight& defaultCellWeight)
    : mWidth(width),
        mHeight(height) {
    utl::ZMatrix::Allocate(&mCellWeights, mWidth, mHeight, defaultCellWeight);
};

ZWeightedMap::ZWeightedMap(const ZWeightedMap& other)
    : mWidth(other.mWidth),
        mHeight(other.mHeight) {
    utl::ZMatrix::AllocateAndCopy(&mCellWeights, other.mCellWeights, mWidth, mHeight);
}

ZWeightedMap::~ZWeightedMap() {
    utl::ZMatrix::Deallocate(&mCellWeights, mHeight);
}

ZWeightedMap& ZWeightedMap::operator=(ZWeightedMap other) {
    swap(*this, other);

    return *this;
}

void swap(ZWeightedMap& left, ZWeightedMap& right) {
    using std::swap;

    swap(left.mWidth, right.mWidth);
    swap(left.mHeight, right.mHeight);
    swap(left.mCellWeights, right.mCellWeights);
}

int ZWeightedMap::GetWidth() const {
    return mWidth;
}

int ZWeightedMap::GetHeight() const {
    return mHeight;
}

void ZWeightedMap::SetCellWeight(const ZPosition& pos, const ZWeight& weight) {
    SetCellWeight(pos.GetX(), pos.GetY(), weight);
}

void ZWeightedMap::SetCellWeight(int x, int y, const ZWeight& weight) {
    mCellWeights[x][y] = weight;
}

const ZWeight& ZWeightedMap::GetCellWeight(const ZPosition& pos) const {
    return GetCellWeight(pos.GetX(), pos.GetY());
}

const ZWeight& ZWeightedMap::GetCellWeight(int x, int y) const {
    if (x < 0 || x >= mWidth
        || y < 0 || y >= mHeight) {
        return ZWeight::kInfinity;
    }

    return mCellWeights[x][y];
}

char GetWeightChar(const ZWeight& weight) {
    static const char kZeroWeight = '.';
    static const char kInfinityWeight = 'x';
    static const char kPositiveWeight = '#';

    if (weight == ZWeight::kZero) {
        return kZeroWeight;
    } else if (weight == ZWeight::kInfinity) {
        return kInfinityWeight;
    } 
    
    return kPositiveWeight;
}

const std::string ZWeightedMap::ToString() const {
    std::stringstream ss;
    for (int x = mWidth - 1; x >= 0; --x) {
        for (int y = 0; y < mHeight; ++y) {
            ss << GetWeightChar(mCellWeights[x][y]);
        }
        ss << std::endl;
    }

    return ss.str();
}

}
}
}