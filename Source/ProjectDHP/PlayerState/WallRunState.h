#pragma once
#include "CoreMinimal.h"
#include "BaseState.h"
#include "Kismet/KismetMathLibrary.h"
#include "WallRunState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDHP_API UWallRunState : public UBaseState
{
	GENERATED_BODY()
public:
	UWallRunState();
	UWallRunState* Init(ADHPCharacter* character, UStateControllerComponent* stateController);
	void EnterState() override;
	void TickState(float DeltaTime) override;
	void ExitState() override;
};
