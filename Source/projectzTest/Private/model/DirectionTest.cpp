#include "projectzTestPrivatePCH.h"

#include "model/Direction.h"

#define ASSERT_POSITION_DIFF_EQ(x, y)  \
    EXPECT_EQ(x##.GetdX(), y##.GetdX()); \
    ASSERT_EQ(x##.GetdY(), y##.GetdY());

namespace prz {
    namespace testing {
        class DirectionTest : public ::testing::Test {
        public:
            static const mdl::ZPositionDiff kPositionDiffs[];

        protected:
            static const int kSomeBigCoordinateDiff = 42;
            static const int kSomeSmallCoordinateDiff = 2;
            mdl::ZDirection dir;
        };

        const mdl::ZPositionDiff DirectionTest::kPositionDiffs[] = {
            mdl::ZPositionDiff(1, 0),
            mdl::ZPositionDiff(0, -1),
            mdl::ZPositionDiff(0, 1),
            mdl::ZPositionDiff(-1, 0),
            mdl::ZPositionDiff(1, -1),
            mdl::ZPositionDiff(1, 1),
            mdl::ZPositionDiff(-1, -1),
            mdl::ZPositionDiff(-1, 1)
        };

        namespace EDirection {
            enum Type {
                Forward = 0,
                Left,
                Right,
                Backward,
                HalfLeft,
                HalfRight
            };
        }

        TEST_F(DirectionTest, DefaultDirectionPredictsForwardMove) {
            mdl::ZPositionDiff diff = dir.PredictMove();

            ASSERT_POSITION_DIFF_EQ(kPositionDiffs[EDirection::Forward], diff);
        }

        TEST_F(DirectionTest, RotateLeft_PredictsLeftMove) {
            dir.RotateLeft();
            mdl::ZPositionDiff diff = dir.PredictMove();

            ASSERT_POSITION_DIFF_EQ(kPositionDiffs[EDirection::Left], diff);
        }

        TEST_F(DirectionTest, RotateLeft_PredictsRightMove) {
            dir.RotateRight();
            mdl::ZPositionDiff diff = dir.PredictMove();

            ASSERT_POSITION_DIFF_EQ(kPositionDiffs[EDirection::Right], diff);
        }

        TEST_F(DirectionTest, RotateLeft_PredictsBackwardMove) {
            dir.RotateBack();
            mdl::ZPositionDiff diff = dir.PredictMove();

            ASSERT_POSITION_DIFF_EQ(kPositionDiffs[EDirection::Backward], diff);
        }

        TEST_F(DirectionTest, RotateLeft_PredictsHalfLeftMove) {
            dir.RotateHalfLeft();
            mdl::ZPositionDiff diff = dir.PredictMove();

            ASSERT_POSITION_DIFF_EQ(kPositionDiffs[EDirection::HalfLeft], diff);
        }

        TEST_F(DirectionTest, RotateLeft_PredictsHalfRightMove) {
            dir.RotateHalfRight();
            mdl::ZPositionDiff diff = dir.PredictMove();

            ASSERT_POSITION_DIFF_EQ(kPositionDiffs[EDirection::HalfRight], diff);
        }

        TEST_F(DirectionTest, RotateLeft_FourthRotateLeftsRotateToForward) {
            for (int i = 0; i < 4; ++i) {
                dir.RotateLeft();
            }

            mdl::ZPositionDiff diff = dir.PredictMove();

            ASSERT_POSITION_DIFF_EQ(kPositionDiffs[EDirection::Forward], diff);
        }

        TEST_F(DirectionTest, RotateLeft_400RotateLeftsRotateToForward) {
            for (int i = 0; i < 400; ++i) {
                dir.RotateLeft();
            }

            mdl::ZPositionDiff diff = dir.PredictMove();

            ASSERT_POSITION_DIFF_EQ(kPositionDiffs[EDirection::Forward], diff);
        }

        class DirectionAlignTest : public DirectionTest,
            public ::testing::WithParamInterface<mdl::ZPositionDiff> {
        };

        TEST_P(DirectionAlignTest, Align_AlignsExactlyToPassedBaseDiff) {
            dir.Align(GetParam());
            mdl::ZPositionDiff diff = dir.PredictMove();

            ASSERT_POSITION_DIFF_EQ(GetParam(), diff);
        }

        INSTANTIATE_TEST_CASE_P(BaseDiffs, DirectionAlignTest, ::testing::ValuesIn(DirectionAlignTest::kPositionDiffs));

        TEST_F(DirectionTest, Align_AlignsToAlmostForwardDiff) {
            mdl::ZPositionDiff diff(kSomeBigCoordinateDiff, kSomeSmallCoordinateDiff);
            dir.Align(diff);

            diff = dir.PredictMove();

            ASSERT_POSITION_DIFF_EQ(kPositionDiffs[EDirection::Forward], diff);
        }

        TEST_F(DirectionTest, Align_AlignsToAlmostBackwardDiff) {
            mdl::ZPositionDiff diff(-kSomeBigCoordinateDiff, -kSomeSmallCoordinateDiff);
            dir.Align(diff);

            diff = dir.PredictMove();

            ASSERT_POSITION_DIFF_EQ(kPositionDiffs[EDirection::Backward], diff);
        }

        TEST_F(DirectionTest, Align_AlignsToAlmostHalfLeftDiff) {
            mdl::ZPositionDiff diff(kSomeBigCoordinateDiff + kSomeSmallCoordinateDiff, -kSomeBigCoordinateDiff + kSomeSmallCoordinateDiff);
            dir.Align(diff);

            diff = dir.PredictMove();

            ASSERT_POSITION_DIFF_EQ(kPositionDiffs[EDirection::HalfLeft], diff);
        }

        TEST_F(DirectionTest, Align_AlignsToCloseToRightDiff) {
            mdl::ZPositionDiff diff(-kSomeBigCoordinateDiff, kSomeBigCoordinateDiff * 3);
            dir.Align(diff);

            diff = dir.PredictMove();

            ASSERT_POSITION_DIFF_EQ(kPositionDiffs[EDirection::Right], diff);
        }
    }
}
