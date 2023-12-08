#pragma once
#include "BaseState.h"
#include "CoreMinimal.h"
#include "JumpState.generated.h"

UCLASS()
class UJumpState : public UBaseState
{
	GENERATED_BODY()
public:
	UJumpState();
	UJumpState* Init(ADHPCharacter* character, UStateControllerComponent* stateController);
	virtual void EnterState() override;
	virtual void TickState(float DeltaTime) override;
	virtual void ExitState() override;

};