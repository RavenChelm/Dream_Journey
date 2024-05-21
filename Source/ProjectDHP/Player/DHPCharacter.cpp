#include "DHPCharacter.h"

ADHPCharacter::ADHPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	movementComponent = GetCharacterMovement();
	stateControllerComponent = CreateDefaultSubobject<UStateControllerComponent>("StateController");

	CrouchTimelineComponent = CreateDefaultSubobject<UTimelineComponent>("CrouchTimelineComponent");
	SlideTimelineComponent = CreateDefaultSubobject<UTimelineComponent>("SlideTimelineComponent");
	CameraTimelineComponent = CreateDefaultSubobject<UTimelineComponent>("CameraTimelineComponent");
	ClimbTimelineComponent = CreateDefaultSubobject<UTimelineComponent>("ClimbTimelineComponent");

	SaveLoadComponent = CreateDefaultSubobject<USaveLoadComponent>("SaveLoadComponent");
	SaveLoadComponent->playerLastLocation = GetActorLocation();

	movementComponent->bRequestedMoveUseAcceleration = true;
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

}

void ADHPCharacter::BeginPlay()
{
	Super::BeginPlay();
	Camera = GetComponentByClass<UCameraComponent>();
	//bSimGravityDisabled = false;
	//movementComponent->GravityScale = 0;
}

void ADHPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
    	if (HeldObject)
    	{
     		FVector HoldLocation = GetActorLocation() + GetActorForwardVector() * 200.0f;
     	 	PhysicsHandle->SetTargetLocation(HoldLocation);
   	}
}

void ADHPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ADHPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &ADHPCharacter::MoveStrafe);
	PlayerInputComponent->BindAxis("Yaw", this, &ADHPCharacter::Yaw);
	PlayerInputComponent->BindAxis("Pitch", this, &ADHPCharacter::Pitch);
	

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADHPCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ADHPCharacter::StopJump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ADHPCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ADHPCharacter::StopRun);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ADHPCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ADHPCharacter::StopCrouch);

	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &ADHPCharacter::PickupObject);
    	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &ADHPCharacter::ThrowObject);

}

void ADHPCharacter::MoveForward(float amount) {
	if (amount) {
		FVector frw = GetActorForwardVector();
		
		//AddMovementInput(frw, amount);
		movementComponent->AddInputVector(frw*amount );
	}
}
void ADHPCharacter::MoveStrafe(float amount) {
	if (amount) {
		FVector rgt = GetActorRightVector();
		//AddMovementInput(rgt, amount);
		movementComponent->AddInputVector(rgt* amount);

	}
}

void ADHPCharacter::Yaw(float amount) {
	AddControllerYawInput(YSensivity  * amount* GetWorld()->GetDeltaSeconds());
	}
void ADHPCharacter::Pitch(float amount) {
	AddControllerPitchInput(XSensivity * -1 * amount * GetWorld()->GetDeltaSeconds());
}
void ADHPCharacter::StartJump() {
	if(movementComponent->IsMovingOnGround())
	{
		SaveLoadComponent->playerLastLocation = GetActorLocation();
	}
	bPressedJump = true;
	
}
void ADHPCharacter::StopJump() {
	bPressedJump = false;
}
void ADHPCharacter::StartRun() {
	bPressedRun = true;
}
void ADHPCharacter::StopRun() {
	bPressedRun = false;
}
void ADHPCharacter::StartCrouch() {
		movementComponent->bWantsToCrouch = true;
		bPressedCrouch = true;
}
void ADHPCharacter::StopCrouch() {
	//if(stateControllerComponent->CanStande())
	//{
		bPressedCrouch = false;
		movementComponent->bWantsToCrouch = false;
	//}


}

void ADHPCharacter::PickupObject()
{
    if (HeldObject) return;

    FVector Start = GetActorLocation();
    FVector End = Start + GetActorForwardVector() * 200.0f;

    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
    if (bHit && HitResult.GetActor()->IsA(APickupObject::StaticClass()))
    {
        HeldObject = HitResult.GetActor();
        PhysicsHandle->GrabComponentAtLocation(HeldObject->FindComponentByClass<UStaticMeshComponent>(), NAME_None, HeldObject->GetActorLocation());
    }
}

void ADHPCharacter::ThrowObject()
{
    if (HeldObject)
    {
        UStaticMeshComponent* MeshComponent = HeldObject->FindComponentByClass<UStaticMeshComponent>();
        if (MeshComponent)
        {
            PhysicsHandle->ReleaseComponent();
            FVector ThrowDirection = GetActorForwardVector();
            MeshComponent->AddImpulse(ThrowDirection * 1000.0f);
            HeldObject = nullptr;
        }
    }
}


