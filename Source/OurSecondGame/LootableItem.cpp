// Fill out your copyright notice in the Description page of Project Settings.

#include "LootableItem.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"


// Sets default values
ALootableItem::ALootableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALootableItem::BeginPlay()
{
	Super::BeginPlay();

	if (UPrimitiveComponent* PrimitiveComponent = this->FindComponentByClass<UPrimitiveComponent>())
	{
		PrimitiveComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	}
}

