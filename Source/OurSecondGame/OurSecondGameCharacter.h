// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ItemData.h"
#include "OurSecondGameCharacter.generated.h"

UCLASS()
class OURSECONDGAME_API AOurSecondGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOurSecondGameCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Interact();

	//handles moving forward/backward
	UFUNCTION()
	void MoveForward(float Val);

	//handles strafing
	UFUNCTION()
	void MoveRight(float Val);
	
	// Return hit for first item in reach
	void GetFirstInteractableInReach();

	// Returns current start of reach line
	FVector GetReachLineStart();

	// Returns current end of reach line
	FVector GetReachLineEnd();

	// How far can the user reach in cm (arms length)
	UPROPERTY(EditAnywhere, Category = "Interact")
	float Reach = 100.f;

	TArray<FName> Inventory;

	AActor* InteractableActor = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	

	// Adds an item to the inventory
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddToInventory(FName ItemName);

	// Checks if an Item is in the Inventory
	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool IsInInventory(FName ItemName);

	// Removes an Item from the Inventory
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveFromInventory(FName ItemName);

	// Returns the entire Inventory
	UFUNCTION(BlueprintPure, Category = "Inventory")
	TArray<FName> GetInventory();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interact")
	void OnInteract(AActor* InteractedActor);
};
