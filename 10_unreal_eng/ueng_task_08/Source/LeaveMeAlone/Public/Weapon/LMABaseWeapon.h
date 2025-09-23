// : LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCurrentlyClipEmpty)

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float FireRate;
};

UCLASS() class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALMABaseWeapon();

	void Fire();
	void FireStop();
	void ChangeClip();
	bool IsCurrentClipFull() const;

	FOnCurrentlyClipEmpty OnCurrentlyClipEmpty;

	FAmmoWeapon GetCurrentAmmoWeapon() const { return CurrentAmmoWeapon; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon AmmoWeapon{30, 0, true, 0.2f};

	void Shoot();

	void DecrementBullets();
	bool IsCurrentClipEmpty() const;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FAmmoWeapon CurrentAmmoWeapon;
	FTimerHandle FireRateTimer;
	FTimerHandle TimerClearTimerFire;
};
