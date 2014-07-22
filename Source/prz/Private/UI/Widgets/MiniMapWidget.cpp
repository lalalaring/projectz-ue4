#include "prz.h"
#include "UI/Widgets/MinimapWidget.h"

#include <map>

FColor CellToColor(prz::mdl::EDungeonCell::Type cell) {
    using namespace prz::mdl;

    static std::map<char, FColor> cellToColor = {
        {EDungeonCell::Unknown, FColor(0, 0, 0)},
        {EDungeonCell::SolidRock, FColor(42, 47, 51)},
        {EDungeonCell::Emptiness, FColor(129, 150, 154)},
        {EDungeonCell::DownStaircase, FColor(170, 198, 203)},
        {EDungeonCell::UpStaircase, FColor(86, 100, 103)},
        {EDungeonCell::Monster, FColor(236, 118, 0)},
    };

    auto pos = cellToColor.find(cell);
    if (pos != cellToColor.end()) {
        return pos->second;
    }

    return FColor(255, 0, 0);
}

void SMinimapWidget::Construct(const FArguments& InArgs) {
    OwnerHUD = InArgs._OwnerHUD;
}

int32 SMinimapWidget::OnPaint(const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const {
    if (OwnerHUD.IsValid() && mMinimap.IsValid()) {
        const FSlateBrush* brush = new FSlateBrush();
        const FVector2D cellSize = FVector2D(1, 1);

        int mapSize = mMinimap->GetSize();

        for (int32 x = 0; x < mapSize; ++x) {
            for (int32 y = 0; y < mapSize; ++y) {
                const FColor color = CellToColor(mMinimap->GetCell(x, y));
                FSlateDrawElement::MakeBox(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(FVector2D(x, y), cellSize), brush, MyClippingRect, ESlateDrawEffect::None, color);
            }
        }

    }

    return SCompoundWidget::OnPaint(AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}

void SMinimapWidget::SetMinimap(const prz::mdl::ZMinimap& minimap) {
    using namespace prz::mdl;

    mMinimap = TSharedPtr<ZMinimap>(new ZMinimap(minimap));
}