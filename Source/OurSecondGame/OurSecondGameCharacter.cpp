// Fill out your copyright notice in the Description page of Project Settings.

#include "OurSecondGameCharacter.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "ItemFinder.h"

// Sets default values
AOurSecondGameCharacter::AOurSecondGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemFinderComponent = CreateDefaultSubobject<UItemFinder>(TEXT("ItemFinder"));
}

// Called when the game starts or when spawned
void AOurSecondGameCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AOurSecondGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOurSecondGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AOurSecondGameCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AOurSecondGameCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &AOurSecondGameCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AOurSecondGameCharacter::AddControllerPitchInput);
}

void AOurSecondGameCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AOurSecondGameCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

