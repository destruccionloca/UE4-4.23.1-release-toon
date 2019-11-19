// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AssetGenerationUtil.h"
#include "InteractiveTool.h"
#include "InteractiveToolManager.h"
#include "Materials/Material.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"

#include "StaticMeshComponentBuilder.h"
#include "MeshDescriptionToDynamicMesh.h"
#include "MeshDescriptionBuilder.h"
#include "DynamicMeshToMeshDescription.h"


FString AssetGenerationUtil::GetDefaultAutoGeneratedAssetPath()
{
	return FString("/Game/_GENERATED");
}


#if WITH_EDITOR

// single material case
AActor* AssetGenerationUtil::GenerateStaticMeshActor(
	IToolsContextAssetAPI* AssetAPI,
	UWorld* TargetWorld,
	const FDynamicMesh3* Mesh,
	const FTransform3d& Transform,
	FString ObjectName,
	FString PackagePath,
	UMaterialInterface* Material
)
{
	return GenerateStaticMeshActor(AssetAPI, TargetWorld, Mesh, Transform, ObjectName, PackagePath, TArrayView<UMaterialInterface*>(&Material, Material != nullptr ? 1 : 0));
}

// N-material case
AActor* AssetGenerationUtil::GenerateStaticMeshActor(
	IToolsContextAssetAPI* AssetAPI,
	UWorld* TargetWorld,
	const FDynamicMesh3* Mesh,
	const FTransform3d& Transform,
	FString ObjectName,
	FString PackagePath,
	const TArrayView<UMaterialInterface*>& Materials
)
{
	check(AssetAPI);
	check(TargetWorld);
	check(Mesh);

	// asset name and location (temp)
	FString PackageFolderPath = (PackagePath.IsEmpty()) ? GetDefaultAutoGeneratedAssetPath() : PackagePath;
	//FString PackageFolderPath = AssetAPI->GetActiveAssetFolderPath();
	FString MeshName = ObjectName;

	// create new package
	FString UniqueAssetName;
	UPackage* AssetPackage = AssetAPI->MakeNewAssetPackage(PackageFolderPath, ObjectName, UniqueAssetName);

	// create new actor
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	// @todo nothing here is specific to AStaticMeshActor...could we pass in a CDO and clone it instead of using SpawnActor?
	AStaticMeshActor* NewActor = TargetWorld->SpawnActor<AStaticMeshActor>(FVector::ZeroVector, Rotation, SpawnInfo);
	NewActor->SetActorLabel(*UniqueAssetName);

	// construct new static mesh
	FStaticMeshComponentBuilder Builder;
	Builder.Initialize(AssetPackage, FName(*UniqueAssetName), Materials.Num());

	// Populate the MeshDescription associated with the asset.
	if (Mesh != nullptr)
	{
		FDynamicMeshToMeshDescription Converter;
		Converter.Convert(Mesh, *Builder.MeshDescription);
	}
	else
	{
		// should generate default sphere here or something...
	}

	// create new mesh component and set as root of NewActor.
	// NB: This should to be called only after the mesh has been created / populated,
	// internally it calls  NewStaticMesh->CommitMeshDescription(0);
	Builder.CreateAndSetAsRootComponent(NewActor);

	// transform new component to origin
	Builder.NewMeshComponent->SetWorldTransform((FTransform)Transform);
	for (int MatIdx = 0, NumMats = Materials.Num(); MatIdx < NumMats; MatIdx++)
	{
		Builder.NewMeshComponent->SetMaterial(MatIdx, Materials[MatIdx]);
	}
	
	// force save of asset
	//AssetAPI->InteractiveSaveGeneratedAsset(Builder.NewStaticMesh, AssetPackage);
	AssetAPI->AutoSaveGeneratedAsset(Builder.NewStaticMesh, AssetPackage);

	return NewActor;
}
#endif