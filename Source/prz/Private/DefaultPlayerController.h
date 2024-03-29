#pragma once

#include "GameFramework/PlayerController.h"

#include "Model/IGame.h"

#include "DefaultPlayerController.generated.h"

/**
 *
 */
UCLASS()
class ADefaultPlayerController : public APlayerController {
    GENERATED_UCLASS_BODY()
public:
    UFUNCTION()
    void MoveForward();

    UFUNCTION()
    void MoveBackward();

    UFUNCTION()
    void StrafeLeft();

    UFUNCTION()
    void StrafeRight();

    UFUNCTION()
    void TurnRight();

    UFUNCTION()
    void TurnLeft();

    UFUNCTION()
    void Quit();

    UFUNCTION()
    void DebugAction();

protected:
    virtual void SetupInputComponent() override;

private:
    void SetupObservers();

    void Move(prz::mdl::EDirection direction);
    void Turn(prz::mdl::EDirection direction);
};
