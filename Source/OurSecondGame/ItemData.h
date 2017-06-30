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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FName Name;

	// The description
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FText Description;

	// The static mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	UStaticMesh* StaticMesh;
	//TAssetPtr<UStaticMesh> StaticMesh;

	// The Id (mapped from the row name)
	FName Id;

	virtual void OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems) override {
		Super::OnPostDataImport(InDataTable, InRowName, OutCollectedImportProblems);
		Id = InRowName;
	}

	bool operator==(const FItemData& Other) const
	{
		return Other.Id == Id;
	}
};