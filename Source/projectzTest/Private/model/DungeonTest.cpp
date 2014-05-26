#include "projectzTestPrivatePCH.h"

#include "model/Dungeon.h"

#include "model/PositionTest.h"

#define ASSERT_DUNGEON_WITH_FAIL_SAFE_MAP(dungeon) \
    EXPECT_EQ(kFailSafeMapWidth, dungeon.GetWidth()); \
    EXPECT_EQ(kFailSafeMapHeight, dungeon.GetHeight()); \
    ASSERT_TRUE(dungeon.CellIsEmpty(kFailSafeMapEmptyCell));

namespace prz {
    namespace testing {
        class DungeonTest : public ::testing::Test {
        protected:
            const static mdl::ZDungeon::ZMapCell* kSomeMap;
            const static int kSomeMapWidth = 5;
            const static int kSomeMapHeight = 3;
            const static mdl::ZPosition kSomeMapSomeHollowCell;
            const static mdl::ZPosition kSomeMapSomeSolidCell;
            const static mdl::ZPosition kSomeMapStairsUpCell;
            const static mdl::ZPosition kSomeMapStairsDownCell;

            const static int kSomeIncorrectMapWidth = 0;
            const static int kSomeIncorrectMapHeight = -5;

            const static int kFailSafeMapWidth = 3;
            const static int kFailSafeMapHeight = 3;
            const static mdl::ZPosition kFailSafeMapEmptyCell;
        };

        const mdl::ZDungeon::ZMapCell* DungeonTest::kSomeMap = ""
            "#####"
            "#<.>#"
            "#####";
        const mdl::ZPosition DungeonTest::kSomeMapSomeHollowCell = mdl::ZPosition(2, 1);
        const mdl::ZPosition DungeonTest::kSomeMapSomeSolidCell = mdl::ZPosition(1, 2);
        const mdl::ZPosition DungeonTest::kSomeMapStairsUpCell = mdl::ZPosition(1, 1);
        const mdl::ZPosition DungeonTest::kSomeMapStairsDownCell = mdl::ZPosition(3, 1);

        const mdl::ZPosition DungeonTest::kFailSafeMapEmptyCell = mdl::ZPosition(1, 1);

        class DungeonWithSomeMapTest : public DungeonTest {
        protected:
            void SetUp() {
                mDungeon = new mdl::ZDungeon(kSomeMapWidth, kSomeMapHeight, kSomeMap);
            }

            void TearDown() {
                delete mDungeon;
            }

            mdl::ZDungeon* mDungeon;
        };

        TEST_F(DungeonWithSomeMapTest, GetWidthAndGetHeightReturnExpectedValues) {
            EXPECT_EQ(kSomeMapWidth, mDungeon->GetWidth());
            ASSERT_EQ(kSomeMapHeight, mDungeon->GetHeight());
        }

        TEST_F(DungeonTest, IncorrectWidthCausesCreationOfDungeonWithFailSafeMap) {
            mdl::ZDungeon dungeon(kSomeIncorrectMapWidth, kSomeMapHeight, kSomeMap);

            ASSERT_DUNGEON_WITH_FAIL_SAFE_MAP(dungeon);
        }

        TEST_F(DungeonTest, IncorrectHeightCausesCreationOfDungeonWithFailSafeMap) {
            mdl::ZDungeon dungeon(kSomeMapWidth, kSomeIncorrectMapHeight, kSomeMap);

            ASSERT_DUNGEON_WITH_FAIL_SAFE_MAP(dungeon);
        }

        TEST_F(DungeonTest, MapWithSizeInconsistentWithWidthAndHeightCausesCreationOfDungeonWithFailSafeMap) {
            mdl::ZDungeon dungeon(kSomeMapWidth, kSomeMapHeight + 1, kSomeMap);

            ASSERT_DUNGEON_WITH_FAIL_SAFE_MAP(dungeon);
        }

        TEST_F(DungeonWithSomeMapTest, CellIsSolid_HollowCellsAreNotSolid) {
            ASSERT_FALSE(mDungeon->CellIsSolid(kSomeMapSomeHollowCell));
        }

        TEST_F(DungeonWithSomeMapTest, CellIsSolid_StairsUpCellsAreNotSolid) {
            ASSERT_FALSE(mDungeon->CellIsSolid(kSomeMapStairsUpCell));
        }

        TEST_F(DungeonWithSomeMapTest, CellIsSolid_StairsDownCellsAreNotSolid) {
            ASSERT_FALSE(mDungeon->CellIsSolid(kSomeMapStairsDownCell));
        }

        TEST_F(DungeonWithSomeMapTest, CellIsSolid_SolidCellsAreIndeedSolid) {
            ASSERT_TRUE(mDungeon->CellIsSolid(kSomeMapSomeSolidCell));
        }

        TEST_F(DungeonWithSomeMapTest, CellIsSolid_CoordinatesWorksJustLikePosition) {
            ASSERT_TRUE(mDungeon->CellIsSolid(kSomeMapSomeSolidCell.GetX(), kSomeMapSomeSolidCell.GetY()));
        }

        TEST_F(DungeonWithSomeMapTest, CellIsEmpty_HollowCellsAreEmpty) {
            ASSERT_TRUE(mDungeon->CellIsEmpty(kSomeMapSomeHollowCell));
        }

        TEST_F(DungeonWithSomeMapTest, CellIsEmpty_StairsUpCellsAreEmpty) {
            ASSERT_TRUE(mDungeon->CellIsEmpty(kSomeMapStairsUpCell));
        }

        TEST_F(DungeonWithSomeMapTest, CellIsEmpty_StairsDownCellsAreEmpty) {
            ASSERT_TRUE(mDungeon->CellIsEmpty(kSomeMapStairsDownCell));
        }

        TEST_F(DungeonWithSomeMapTest, CellIsEmpty_SolidCellsAreNotEmpty) {
            ASSERT_FALSE(mDungeon->CellIsEmpty(kSomeMapSomeSolidCell));
        }

        TEST_F(DungeonWithSomeMapTest, CellIsEmpty_CoordinatesWorksJustLikePosition) {
            ASSERT_TRUE(mDungeon->CellIsEmpty(kSomeMapSomeHollowCell.GetX(), kSomeMapSomeHollowCell.GetY()));
        }

        TEST_F(DungeonTest, GetStairsUp_ReturnsNoCellsForMapWithoutStairsUp) {
            const char* map = ""
                "###"
                "#>#"
                "###";
            mdl::ZDungeon dungeon(3, 3, map);

            ASSERT_EQ(0, dungeon.GetStairsUp().size());
        }

        TEST_F(DungeonTest, GetStairsUp_ReturnsExactCellForMapWithSingleStairsUp) {
            const char* map = ""
                "####"
                "#.<#"
                "####";
            mdl::ZDungeon dungeon(4, 3, map);

            ASSERT_EQ(1, dungeon.GetStairsUp().size());
            
            const mdl::ZPosition& pos = dungeon.GetStairsUp()[0];
            ASSERT_POSITION_EQ(mdl::ZPosition(2, 1), pos);
        }
    }
}
