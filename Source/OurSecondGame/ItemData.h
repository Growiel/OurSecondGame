#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "ItemData.generated.h"

/** Structure to store the lookup of ItemData for use in a UDataTable */
USTRUCT(Blueprintable)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	// The name to be displayed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	FText Name;

	// The description
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	FText Description;

	// The static mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	UStaticMesh* StaticMesh;
	//TAssetPtr<UStaticMesh> StaticMesh;

	// The icon (for the UMGs)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	UTexture2D* Icon;
};