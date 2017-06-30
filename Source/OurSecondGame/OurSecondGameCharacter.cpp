// Fill out your copyright notice in the Description page of Project Settings.

#include "OurSecondGameCharacter.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "InteractableInterface.h"

#define OUT

// Sets default values
AOurSecondGameCharacter::AOurSecondGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

	GetFirstInteractableInReach();
}

// Called to bind functionality to input
void AOurSecondGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AOurSecondGameCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AOurSecondGameCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &AOurSecondGameCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AOurSecondGameCharacter::AddControllerPitchInput);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AOurSecondGameCharacter::Interact);
}

void AOurSecondGameCharacter::Interact()
{
	if (InteractableActor) {
		// Let Blueprints of this class do whatever they want when we interact (like play an animation)
		OnInteract(InteractableActor);

		UE_LOG(LogTemp, Display, TEXT("Interacted"));
		IInteractableInterface::Execute_Interact(InteractableActor, this);
	}
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

bool AOurSecondGameCharacter::AddToInventory(const FItemData& Item)
{
	// We can only have the Item once in the Inventory. If already present we return false.
	if (IsInInventory(Item)) {
		return false;
	}
	Inventory.AddUnique(Item);
	return true;
}

bool AOurSecondGameCharacter::IsInInventory(const FItemData& Item)
{
	return Inventory.Contains(Item);
}

void AOurSecondGameCharacter::RemoveFromInventory(const FItemData& Item)
{
	Inventory.Remove(Item);
}

TArray<FItemData> AOurSecondGameCharacter::GetInventory()
{
	return Inventory;
}

void AOurSecondGameCharacter::GetFirstInteractableInReach()
{
	/// Line-trace (AKA Ray-cast) out to reach distance
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, this);
	/*DrawDebugLine(
		GetWorld(),
		GetReachLineStart(),
		GetReachLineEnd(),
		FColor(255, 0, 0),
		5,
		12.333
	);*/
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(),
		TraceParameters
	);

	/// Line trace and see if we reach any actors with physics body collision channel set
	auto ActorHit = HitResult.GetActor();

	/// If we hit something
	if (ActorHit)
	{
		/// Check that the something implements our interface
		if (ActorHit->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass())) {
			/// Store it!
			InteractableActor = ActorHit;
		} else if(InteractableActor){
			InteractableActor = nullptr;
		}
	}
	else if (InteractableActor) {
		InteractableActor = nullptr;
	}
}

FVector AOurSecondGameCharacter::GetReachLineStart()
{
	/// Get the player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}

FVector AOurSecondGameCharacter::GetReachLineEnd()
{
	/// Get the player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;
}
