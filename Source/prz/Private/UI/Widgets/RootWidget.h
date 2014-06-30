#pragma once

#include "Slate.h"

class SRootWidget : public SCompoundWidget {
    SLATE_BEGIN_ARGS(SRootWidget) {
    }
    SLATE_ARGUMENT(TWeakObjectPtr<class ADefaultHUD>, OwnerHUD)
    SLATE_END_ARGS()

public:
    void Construct(const FArguments& InArgs);

    float GetDPIScale() const;
    void SetDPIScale(int32 scale);

    SOverlay::FOverlaySlot& AddSlot(int32 zOrder = INDEX_NONE);

private:
    TSharedPtr<SOverlay> mDPIScaledOverlay;
    int32 mScale = 1;
    TWeakObjectPtr<class ADefaultHUD> OwnerHUD;
};