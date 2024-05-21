// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../PlayerState/StateControllerComponent.h"
#include "SaveLoadComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/TimelineComponent.h"
#include "Camera/CameraComponent.h"

#include "DHPCharacter.generated.h"


//DHP - DisHonored Portfolio
UCLASS()
class PROJECTDHP_API ADHPCharacter : public ACharacter
{
	GENERATED_BODY()
private:

public:
	ADHPCharacter();
	UPROPERTY(BlueprintReadWrite, Category = "Sensivity")
	float XSensivity = 200.f;
	UPROPERTY(BlueprintReadWrite, Category = "Sensivity")
	float YSensivity = 200.f;

	
	UCharacterMovementComponent* movementComponent;


	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = "Movement")
	UStateControllerComponent* stateControllerComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTimelineComponent* CrouchTimelineComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTimelineComponent* SlideTimelineComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTimelineComponent* CameraTimelineComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTimelineComponent* ClimbTimelineComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USaveLoadComponent* SaveLoadComponent;
	bool bPressedRun = false;
	bool bPressedCrouch = false;
   	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    	class UPhysicsHandleComponent* PhysicsHandle;

    	void PickupObject();
    	void ThrowObject();

    	AActor* HeldObject;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//Basic Move
	virtual void MoveStrafe(float amount);
	virtual void MoveForward(float amount);
	//Another Move
	virtual void StartJump();
	virtual void StopJump();
	virtual void StartRun();
	virtual void StopRun();
	virtual void StartCrouch();
	virtual void StopCrouch();

	//View
	virtual void Yaw(float amount);
	virtual void Pitch(float amount);

};

