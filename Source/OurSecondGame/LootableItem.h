// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "ItemData.h"
#include "Runtime/Core/Public/Math/TransformNonVectorized.h"
#include "LootableItem.generated.h"

UCLASS()
class OURSECONDGAME_API ALootableItem : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALootableItem();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interact")
	void OnLooted(AActor* InteractedBy);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle ItemHandle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	virtual void Interact_Implementation(AActor* InteractedBy) override;

	virtual void OnConstruction(const FTransform& Transform);
};
