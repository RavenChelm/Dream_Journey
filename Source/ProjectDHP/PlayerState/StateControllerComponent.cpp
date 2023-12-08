

#include "../PlayerState/StateControllerComponent.h"
#include "../Player/DHPCharacter.h"
UStateControllerComponent::UStateControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	character = Cast<ADHPCharacter>(GetOwner()); 

	idleState = NewObject<UIdleState>()->Init(character, this);
	runState = NewObject<URunState>()->Init(character, this);
	jumpState = NewObject<UJumpState>()->Init(character, this);
	crouchState = NewObject<UCrouchState>()->Init(character, this);
	climbState = NewObject<UClimbState>()->Init(character, this);
	slideState = NewObject<USlideState>()->Init(character, this);
	wallRunState = NewObject<UWallRunState>()->Init(character, this);
	walkState = NewObject<UWalkState>()->Init(character, this);

	HitLeftResult = new FHitResult();
	HitRightResult = new FHitResult();

	currentState = idleState;
}


void UStateControllerComponent::BeginPlay()
{
	Super::BeginPlay();
	capsule = character->GetComponentByClass<UCapsuleComponent>();

	character->movementComponent->JumpZVelocity = JumpHeight;
	character->movementComponent->AirControl = AirConroll;
	character->movementComponent->GravityScale = GravityScale;
	character->movementComponent->GroundFriction = GroundFrictionGeneral;
	currentState->EnterState();


	//TimeLine For Crouch
	FOnTimelineFloat crouchTimeLineProgress;
	crouchTimeLineProgress.BindUFunction(this, FName("CrouchTimeLineProgress"));
	character->CrouchTimelineComponent->AddInterpFloat(CrouchCurve, crouchTimeLineProgress);
	character->CrouchTimelineComponent->SetLooping(false);
	character->CrouchTimelineComponent->SetTimelineLength(0.5f);

	//TimeLine For Slide
	FOnTimelineFloat slideTimeLineProgress;
	slideTimeLineProgress.BindUFunction(this, FName("SlideTimeLineProgress"));
	character->SlideTimelineComponent->AddInterpFloat(SlideCurve, slideTimeLineProgress);
	character->SlideTimelineComponent->SetLooping(true);
	
	//TimeLine For Slide Camera
	FOnTimelineFloat cameraTimeLineProgress;
	cameraTimeLineProgress.BindUFunction(this, FName("CameraTimeLineProgress"));
	character->CameraTimelineComponent->AddInterpFloat(CameraCurve, cameraTimeLineProgress);
	character->CameraTimelineComponent->SetLooping(false);
	character->CameraTimelineComponent->SetTimelineLength(0.3f);

	//TimeLine For Climb
	FOnTimelineFloat climbTimeLineProgress;
	climbTimeLineProgress.BindUFunction(this, FName("ClimbTimeLineProgress"));
	character->ClimbTimelineComponent->AddInterpFloat(ClimbCurve, climbTimeLineProgress);
	character->ClimbTimelineComponent->SetLooping(false);
	character->ClimbTimelineComponent->SetTimelineLength(0.3f);
}


void UStateControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	currentState->TickState(DeltaTime);
}

bool UStateControllerComponent::EnterInNewState(UBaseState* newState)
{
	if (newState) {
		currentState->ExitState();
		currentState = newState;
		currentState->EnterState();
		return true;
	}
	else return false;
}

//Jump, Climb, WallRun

bool UStateControllerComponent::CanStande()
{

	FHitResult HitResult;
	FVector Head;
	FVector Foot;
	Head = Foot = character->GetActorLocation();
	 
	Head.Z += StandingCapsuleHalfHeight + 5;
	Foot.Z -= (StandingCapsuleHalfHeight - 20);

	FCollisionQueryParams TraceParams(FName(TEXT("CanStande")), true, character);
	bool bHitFromFootToHead = character->GetWorld()->LineTraceSingleByChannel(HitResult, Foot, Head, ECC_Visibility, TraceParams);


	DrawDebugLine(character->GetWorld(), Foot, Head, FColor::Red, false, -1, 0, 10);


	return !bHitFromFootToHead;
}

bool UStateControllerComponent::WallIsNear(WallDirection& wallDir, FHitResult* HitLeft, FHitResult* HitRight)
{
	FVector Start = character->GetActorLocation();
	FVector EndRight = Start + (character->GetActorRightVector() * WallDistance);
	FVector EndLeft = Start + (character->GetActorRightVector() * WallDistance * (-1));
	FCollisionQueryParams TraceParams(FName(TEXT("WallTrace")), true, character);


	bool bHitRight = character->GetWorld()->LineTraceSingleByChannel(*HitRight, Start, EndRight, ECC_Visibility, TraceParams);
	bool bHitLeft = character->GetWorld()->LineTraceSingleByChannel(*HitLeft, Start, EndLeft, ECC_Visibility, TraceParams);


	DrawDebugLine(character->GetWorld(), Start, EndRight, FColor::Green, false, -1, 0, 10);
	DrawDebugLine(character->GetWorld(), Start, EndLeft, FColor::Blue, false, -1, 0, 10);


	if (bHitRight)
	{
		DrawDebugLine(character->GetWorld(), HitRight->ImpactPoint, HitRight->ImpactPoint+HitRight->Normal, FColor::Magenta, false, -1, 0, 10);
		wallDir = WallDirection::Right;
	}
	else if (bHitLeft) 
	{
		DrawDebugLine(character->GetWorld(), HitLeft->ImpactPoint, HitLeft->ImpactPoint+ HitLeft->Normal, FColor::Magenta, false, -1, 0, 10);
		wallDir = WallDirection::Left;
	}
	//else wallDir = WallDirection::None;

	return bHitRight || bHitLeft;
}

bool UStateControllerComponent::CanClimb()
{
	FHitResult HitResult;
	FVector StartHead;
	FVector StartFoot; 
	StartFoot = StartHead = character->GetActorLocation();

	StartHead.Z += character->GetDefaultHalfHeight() + 30;
	StartFoot.Z -= character->GetDefaultHalfHeight() - 40;
	FVector EndForwardFoot = StartFoot + (character->GetActorForwardVector() * WallDistance);
	FVector EndForwardHead = StartHead + (character->GetActorForwardVector() * WallDistance);

	FCollisionQueryParams TraceParams(FName(TEXT("WallTrace")), true, character);


	bool bHitForwardFoot = character->GetWorld()->LineTraceSingleByChannel(HitResult, StartFoot, EndForwardFoot, ECC_Visibility, TraceParams);
	bool bHitForwardHead = character->GetWorld()->LineTraceSingleByChannel(HitResult, StartHead, EndForwardHead, ECC_Visibility, TraceParams);


	DrawDebugLine(character->GetWorld(), StartFoot, EndForwardFoot, FColor::Red, false, -1, 0, 10);
	DrawDebugLine(character->GetWorld(), StartHead, EndForwardHead, FColor::Yellow, false, -1, 0, 10);

	FVector direction = character->GetActorLocation() - HitResult.ImpactPoint;
	direction.Normalize();
	FVector target = bHitForwardHead ? HitResult.ImpactPoint + direction * capsule->GetUnscaledCapsuleRadius() : EndForwardHead + character->GetActorUpVector() * StandingCapsuleHalfHeight;
	FVector targetDown = target + character->GetActorUpVector()*(-1) * 1000 ;
	bool bHitClimbPoint = character->GetWorld()->LineTraceSingleByChannel(HitResult, target, targetDown, ECC_Visibility, TraceParams);
	if(bHitClimbPoint)
		climbState->target = HitResult.ImpactPoint+ character->GetActorUpVector() * (StandingCapsuleHalfHeight);
	return bHitForwardFoot && !bHitForwardHead;
}

void UStateControllerComponent::SwitchInput(bool state)
{
	character->SetActorEnableCollision(state);
	character->bSimGravityDisabled = !state;
	character->bBlockInput = !state;
}
//Move to ClimbState
bool UStateControllerComponent::MoveCharacter(FVector& Target, float DeltaTime)
{
	FVector CurrentPosition = character->GetActorLocation();
	FVector NewPosition = FMath::Lerp(CurrentPosition, Target, climbState->LerpAlpha);
	climbState->LerpAlpha += DeltaTime * ClimbSpeed ;
	character->SetActorLocation(NewPosition, false);
	if (climbState->LerpAlpha >= 0.98f || FVector::DistSquared(Target, CurrentPosition) <= 2.f) {
		capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		character->SetActorLocation(Target, false);
		climbState->LerpAlpha = 0;
		return true;
	}		
	return false;
}

//Crouch, Slide
void UStateControllerComponent::ChangeCapsula(bool bSetToStanding)
{
	if (bSetToStanding) character->CrouchTimelineComponent->Reverse();
	else character->CrouchTimelineComponent->Play();

}


void UStateControllerComponent::CrouchTimeLineProgress(float Value)
{	
	character->bSimGravityDisabled = true;

	float _value = UKismetMathLibrary::Lerp(SitingCapsuleHalfHeight, StandingCapsuleHalfHeight, Value);
	auto oldHeight = capsule->GetScaledCapsuleHalfHeight();
	capsule->SetCapsuleHalfHeight(_value);
	auto offset = capsule->GetScaledCapsuleHalfHeight() - oldHeight;
	auto newHeight = capsule->GetRelativeLocation();
	newHeight.Z += offset;

	capsule->SetRelativeLocation(newHeight);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), newHeight.Z));


	FVector newLocCam = character->Camera->GetRelativeLocation();
	 float _valueCam = FMath::GetMappedRangeValueClamped(TRange<float>(0.f, 1.f), TRange<float>(SitingCameraZOffeset, StandingCameraZOffeset), Value);
	newLocCam.Z = _valueCam;
	character->Camera->SetRelativeLocation(newLocCam);
}
void UStateControllerComponent::SlideTimeLineProgress(float Value)
{
	FVector Force = CalculateFloorInfluence(character->movementComponent->CurrentFloor.HitResult.Normal);
	character->movementComponent->AddForce(Force * 150000);
	FVector velosity = character->movementComponent->Velocity;
	if (velosity.Length() > SlideMaxSpeed)
	{
		velosity.Normalize();
		character->movementComponent->Velocity = velosity * SlideMaxSpeed;
	}
}
void UStateControllerComponent::CameraTimeLineProgress(float Value)
{
	auto controller = character->GetController();
	auto Rotation = controller->GetControlRotation();
	FRotator rotator { Rotation.Pitch,Rotation.Yaw,  (wallDirection == WallDirection::Right  || currentState == slideState) ? Value : -Value };

	controller->SetControlRotation(rotator);
}
void UStateControllerComponent::ClimbTimeLineProgress(float Value)
{
	auto controller = character->GetController();
	auto Rotation = controller->GetControlRotation();
	FRotator rotator{ Value, Rotation.Yaw, Rotation.Roll};

	controller->SetControlRotation(rotator);
}
FVector UStateControllerComponent::CalculateFloorInfluence(FVector FloorNormal)
{
	if (VectorsEqual(FloorNormal, character->GetActorUpVector(), 0.0001f) ){
		return FVector(0,0,0);
	}
	FVector vec =  FVector::CrossProduct(FloorNormal, (FVector::CrossProduct(FloorNormal, character->GetActorUpVector() )));
	vec.Normalize();
	return vec;

}
bool UStateControllerComponent::VectorsEqual(const FVector& Vector1, const FVector& Vector2, float Tolerance)
{
	if (FMath::Abs(Vector1.X - Vector2.X) <= Tolerance &&
		FMath::Abs(Vector1.Y - Vector2.Y) <= Tolerance &&
		FMath::Abs(Vector1.Z - Vector2.Z) <= Tolerance)
	{
		return true;
	}

	return false;
}



