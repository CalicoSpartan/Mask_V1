// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "FPSCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Gun.generated.h"

/**
*
*/
UCLASS()
class FPSPROJECT_API AGun : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AGun();
	UPROPERTY(EditAnywhere, Category = "Weapon")
		bool IsProjectile;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		bool IsAutomatic;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		bool IsBurst;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		int32 BulletsPerBurst;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		float FireRate;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		float ReloadTime;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		float BulletDamage;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		int32 TotalAmmo;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		int32 AmmoLeftInMag;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		int32 MagazineSize;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		int32 NumberOfMagazines;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		int32 Range;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		bool IsExplosive;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		USceneComponent* MuzzleLocation;
	//required network scaffolding
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// returns whether or not the pickup is active
	UFUNCTION(BlueprintPure, Category = "Weapon")
		bool IsActive();

	//allows other classes to safely change the pickup's activation state
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetActive(bool NewWeaponState);
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
		void WasCollected();
	virtual void WasCollected_Implementation();
	//server side handling of being picked up
	UFUNCTION(BlueprintAuthorityOnly, Category = "Weapon")
		virtual void PickedUpBy(APawn* Pawn);

protected:




	//true when the pickup can be used, false when the pickup is deactivated
	UPROPERTY(Replicated = OnRep_IsActive)
		bool bIsActive;
	//this is called whenever bIsActive is updated
	UFUNCTION()
		virtual void OnRep_IsActive();

	// the pawn who picked up the pickup
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		APawn* WeaponInstigator;

private:
	// client side handling of being picked up
	UFUNCTION(NetMulticast, Unreliable)
		void ClientOnPickedUpBy(APawn* Pawn);

};
