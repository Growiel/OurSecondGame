// Fill out your copyright notice in the Description page of Project Settings.

#include "LootableItem.h"
#include "OurSecondGameCharacter.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Public/DataTableUtils.h"


// Sets default values
ALootableItem::ALootableItem()
{
	UE_LOG(LogTemp, Error, TEXT("Constructor"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get the BP datatable
	ConstructorHelpers::FObjectFinder<UDataTable> ItemData_DataTable(TEXT("DataTable'/Game/Inventory/ItemData_DataTable.ItemData_DataTable'"));

	if (ItemData_DataTable.Succeeded()) {
		// Force the Datatable to be the ItemInfo one (so we don't need to manually select it each time in the BP side)
		ItemHandle.DataTable = ItemData_DataTable.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("COULD NOT FIND THE ITEMINFO DATATABLE!!"));
	}

	// Add a StaticMesh component
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMeshComponent;
	//StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}

void ALootableItem::OnConstruction(const FTransform& Transform)
{
	// Check that the StaticMeshComponent was correctly created (we never know...)
	if (StaticMeshComponent)
	{
		// Get the selected RowName
		const FName& RowName = ItemHandle.RowName;
		// If None is selected, unset the staticmesh (mainly for new instances)
		if (RowName.IsNone()) {
			StaticMeshComponent->SetStaticMesh(nullptr);
		}
		else {
			// Get the ItemInfo from the Handle
			FItemData* Row = ItemHandle.GetRow<FItemData>(TEXT("FindMesh"));
			// It's a valid row
			if (Row) {
				// Set the staticmesh
				StaticMeshComponent->SetStaticMesh(Row->StaticMesh);
			}
			else {
				// Invalid row, unset the staticmesh
				StaticMeshComponent->SetStaticMesh(nullptr);
			}
		}
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("No Static MeshComponent"));
	}
}

void ALootableItem::Interact_Implementation(AActor* InteractedBy)
{
	/// Check if OurSecondGamePlayerCharacter instance
	AOurSecondGameCharacter* Character = Cast<AOurSecondGameCharacter>(InteractedBy);
	if (Character) {
		/// Put in inventory
		FItemData* Row = ItemHandle.GetRow<FItemData>(TEXT("FindMesh"));

		if (Character->AddToInventory(*Row)) {
			UE_LOG(LogTemp, Display, TEXT("Added Item: %s"), *Row->Name.ToString());
			Destroy();
		}
	}
}
