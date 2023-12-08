#pragma once
#include "BaseState.h"
#include "CoreMinimal.h"
#include "RunState.generated.h"

UCLASS()
class URunState : public UBaseState
{
	GENERATED_BODY()
public:
	URunState();
	URunState* Init(ADHPCharacter* character, UStateControllerComponent* stateController);
	void EnterState() override;
	void TickState(float DeltaTime) override;
	void ExitState() override;
};

