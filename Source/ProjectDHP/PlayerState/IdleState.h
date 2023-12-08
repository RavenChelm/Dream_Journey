#pragma once
#include "CoreMinimal.h"
#include "BaseState.h"
#include "IdleState.generated.h"
UCLASS()
class UIdleState : public UBaseState {
	GENERATED_BODY()
public:
	UIdleState();
	UIdleState* Init(ADHPCharacter* character, UStateControllerComponent* stateController);
	void EnterState() override;
	void TickState(float DeltaTime) override;
	void ExitState() override;
};