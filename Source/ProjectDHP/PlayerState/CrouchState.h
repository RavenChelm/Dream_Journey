#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "Components/CapsuleComponent.h"
#include "CrouchState.generated.h"
/**
 * 
 */
UCLASS()
class PROJECTDHP_API UCrouchState : public UBaseState
{
	GENERATED_BODY()
private:
	bool StateOn;
public:
	UCrouchState();
	UCrouchState* Init(ADHPCharacter* character, UStateControllerComponent* stateController);
	void EnterState() override;
	void TickState(float DeltaTime) override;
	void ExitState() override;
};
