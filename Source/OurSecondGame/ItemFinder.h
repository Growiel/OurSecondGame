// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemFinder.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OURSECONDGAME_API UItemFinder : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemFinder();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

private:
	// How far can the user reach in cm (arms length)
	UPROPERTY(EditAnywhere)
	float Reach = 100.f;

	UInputComponent* InputComponent = nullptr;

	// Ray cast and take what's in reach
	void TakeItem();

	// Setup (assumed) attached input component
	void SetupInputComponent();

	// Return hit for first item in reach
	const FHitResult GetFirstItemInReach();

	// Returns current start of reach line
	FVector GetReachLineStart();

	// Returns current end of reach line
	FVector GetReachLineEnd();
};
