// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Gun.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Collection Sphere */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* CollectionBox;
public:
	// Sets default values for this character's properties
	AFPSCharacter();

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetCurrentHealth();
	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetInitialHealth();
	UFUNCTION(BlueprintCallable, Category = "Health")
		void ChangeHealthBy(float delta);
	//required network scaffolding
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	// shut down the pawn and ragdoll it on all clients
	UFUNCTION(NetMultiCast, Reliable) //multicast function happens on server and clients so everyone will see the player ragdoll
		void OnPlayerDeath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Entry. Called when player presses a key to collect pickups
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void PickupWeapon();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void FireAgain();
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		float InitialHealth;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		float CurrentHealth;
	//called on server to process the collection of pickups
	UFUNCTION(Reliable, Server, WithValidation)
		void ServerPickupWeapon();
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FTimerHandle WeaponFireRateTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		bool IsFiring;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
		void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
		void MoveRight(float Value);

	// Sets jump flag when key is pressed.
	UFUNCTION()
		void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
		void StopJump();

	// FPS camera.
	UPROPERTY(Replicated, VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Weapon")
		class AGun* CurrentPrimary;
	//TSubclassOf<AGun> CurrentPrimary;


	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(Replicated, VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void OnShoot();


	UFUNCTION(Reliable, Server, WithValidation)
		virtual void ServerOnShoot();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void OnStopShoot();


	UFUNCTION(Reliable, Server, WithValidation)
		virtual void ServerOnStopShoot();

	UPROPERTY(EditAnywhere, Category = "Weapon")
		bool HasWeapon;


	UFUNCTION(Server,Reliable,WithValidation)
		void ServerUpdateRotation(FRotator Rotation);

	UPROPERTY(Replicated, EditDefaultsOnly)
		APawn* Shooter;

};

