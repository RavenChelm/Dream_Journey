#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseState.h"
#include "IdleState.h"
#include "RunState.h"
#include "JumpState.h"
#include "CrouchState.h"
#include "ClimbState.h"
#include "SlideState.h"
#include "WallRunState.h"
#include "WalkState.h"

#include "Components/TimelineComponent.h"

#include "StateControllerComponent.generated.h"
class ADHPCharacter;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTDHP_API UStateControllerComponent : public UActorComponent 
{
	GENERATED_BODY()
public:	
	enum class WallDirection { None, Left, Right };

	UStateControllerComponent();
	UBaseState* currentState;
	UIdleState* idleState;
	URunState* runState;
	UJumpState* jumpState;
	UCrouchState* crouchState;
	UClimbState* climbState;
	USlideState* slideState;
	UWallRunState* wallRunState;
	UWalkState* walkState;
	
	//Actor
	ADHPCharacter* character;
	UCapsuleComponent* capsule;



	//GeneralMovementSettings
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Movement")
	//float GroundFriction = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Movement")
		float AirConroll = 0.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Movement")
		float GravityScale = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Movement")
		float JumpHeight = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Movement")
		float GroundFrictionGeneral = 8.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Movement")
		float BrakingDecelerationGeneral = 2048.f;
	//IdleState Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	float IdleMaxSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	float IdleMaxAcceleration = 200.f;
	//WalkState Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Walk")
	float WalkMaxSpeed = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Walk")
	float WalkMaxAcceleration = 500.f;
	//RunState Settings
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Run")
		float RunMaxSpeed = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Run")
		float RunMaxAcceleration = 1000.f;
	//JumpState Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
		float JumpMaxSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Jump")
		float JumpMaxAcceleration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
		float WallDistance = 40.f;
	//SlideState Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
	float SlideMaxSpeed = 700.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
	float SlideMaxAcceleration = 700.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
	float GroundFrictionSlide = 8.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
	float BrakingDecelerationSlide = 2048.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
	double thresholdVelosity = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
	UCurveFloat* SlideCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
	UCurveFloat* CameraCurve;


	//Crouch Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")
	float CrouchMaxSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")
	float CrouchMaxAcceleration = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")
	float StandingCapsuleHalfHeight =90 ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")
	float SitingCapsuleHalfHeight = 45;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")
	float StandingCameraZOffeset = 60;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")
	float SitingCameraZOffeset = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")
	UCurveFloat* CrouchCurve;
	//WallRun Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallRun")
	float FVup = 700.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallRun")
	float FVforward = 1000.f; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WallRun")
	float MaxTimeRun = 1.f;
	float CurrentTimeRun = 0.f;
	//Climb Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float ClimbSpeed = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float JumpFromWallSpeed_XY = 700.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float JumpFromWallSpeed_Z = 700.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	UCurveFloat* ClimbCurve;


	//For WallRun
	WallDirection wallDirection = WallDirection::None;
	WallDirection prevWallDirection = WallDirection::None;
	FHitResult* HitLeftResult = new FHitResult();
	FHitResult* HitRightResult = new FHitResult();

	
protected:
	virtual void BeginPlay() override;
	bool VectorsEqual(const FVector& Vector1, const FVector& Vector2, float Tolerance);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool EnterInNewState(UBaseState* newState);
	bool CanStande();
	bool CanClimb();
	bool WallIsNear(WallDirection& wallDir, FHitResult* HitLeft, FHitResult* HitRight);
	bool MoveCharacter(FVector& Target, float DeltaTime);
	void SwitchInput(bool state);
	void ChangeCapsula(bool bSetToStanding);
	UFUNCTION() void CrouchTimeLineProgress(float Value);
	UFUNCTION() void SlideTimeLineProgress(float Value);
	UFUNCTION() void CameraTimeLineProgress(float Value);
	UFUNCTION() void ClimbTimeLineProgress(float Value);
	FVector CalculateFloorInfluence(FVector FloorNormal);


};
