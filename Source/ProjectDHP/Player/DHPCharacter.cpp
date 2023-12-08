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



