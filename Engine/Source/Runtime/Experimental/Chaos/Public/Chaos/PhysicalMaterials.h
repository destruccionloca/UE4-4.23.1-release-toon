// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Chaos/Core.h"
#include "Chaos/Defines.h"
#include "Chaos/Framework/Handles.h"

namespace Chaos
{
	using FMaterialArray = THandleArray<FChaosPhysicsMaterial>;
	using FChaosMaterialHandle = FMaterialArray::FHandle;
	using FChaosConstMaterialHandle = FMaterialArray::FConstHandle;

	/** 
	 * Helper wrapper to encapsulate the access through the material manager
	 * Handles returned from the material manager are only designed to be used (resolved) on the game thread
	 * by the physics interface.
	 */
	struct CHAOS_API FMaterialHandle
	{
		FChaosPhysicsMaterial* Get() const;
		FChaosMaterialHandle InnerHandle;

		bool IsValid() const { return Get() != nullptr; }

		friend bool operator ==(const FMaterialHandle& A, const FMaterialHandle& B) { return A.InnerHandle == B.InnerHandle; }

		friend FArchive& operator <<(FArchive& Ar, FMaterialHandle& Value) { Ar << Value.InnerHandle; return Ar; }
	};

	/**
	 * Helper wrapper to encapsulate the access through the material manager
	 * Handles returned from the material manager are only designed to be used (resolved) on the game thread
	 * by the physics interface.
	 */
	struct CHAOS_API FConstMaterialHandle
	{
		const FChaosPhysicsMaterial* Get() const;
		FChaosConstMaterialHandle InnerHandle;

		bool IsValid() const { return Get() != nullptr; }

		friend bool operator ==(const FConstMaterialHandle& A, const FConstMaterialHandle& B) { return A.InnerHandle == B.InnerHandle; }

		friend FArchive& operator <<(FArchive& Ar, FConstMaterialHandle& Value) { Ar << Value.InnerHandle; return Ar; }
	};

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnMaterialCreated, FMaterialHandle);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnMaterialDestroyed, FMaterialHandle);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnMaterialUpdated, FMaterialHandle);
	using FMaterialCreatedDelegate = FOnMaterialCreated::FDelegate;
	using FMaterialDestroyedDelegate = FOnMaterialDestroyed::FDelegate;
	using FMaterialUpdatedDelegate = FOnMaterialUpdated::FDelegate;

	/** 
	 * Global manager for physical materials.
	 * Materials are created, updated and destroyed only on the game thread and an immutable
	 * copy of the materials are stored on each solver. The solvers module binds to the updated event
	 * in this manager and enqueues updates to all active solvers when a material is updated.
	 *
	 * The material manager provides handles for the objects which should be stored instead of the
	 * material pointer. When accessing the internal material always use the handle rather than
	 * storing the result of Get()
	 */
	class CHAOS_API FPhysicalMaterialManager
	{
	public:

		static FPhysicalMaterialManager& Get();

		/** Create a new material, returning a stable handle to it - this should be stored and not the actual material pointer */
		FMaterialHandle Create();

		/** Destroy the material referenced by the provided handle */
		void Destroy(FMaterialHandle InHandle);

		/** Get the actual material from a handle */
		FChaosPhysicsMaterial* Resolve(FChaosMaterialHandle InHandle) const;
		const FChaosPhysicsMaterial* Resolve(FChaosConstMaterialHandle InHandle) const;

		/** Signals stakeholders that the stored material for the provided handle has changed */
		void UpdateMaterial(FMaterialHandle InHandle);

		/** Gets the internal list of master materials representing the current user state of the material data */
		const THandleArray<FChaosPhysicsMaterial>& GetMasterMaterials() const;

		/** Events */
		FOnMaterialUpdated OnMaterialUpdated;
		FOnMaterialCreated OnMaterialCreated;
		FOnMaterialDestroyed OnMaterialDestroyed;

	private:

		/** Initial size for the handle-managed array */
		static constexpr int32 InitialCapacity = 4;

		/** Material manager is a singleton - access with Get() */
		FPhysicalMaterialManager();

		/** Handle-managed array of global materials. This is pushed to all solvers who all maintain a copy */
		THandleArray<FChaosPhysicsMaterial> Materials;
	};
}
