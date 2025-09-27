// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Weapon/LMABaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);

// Sets default values
ALMABaseWeapon::ALMABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	SetRootComponent(WeaponComponent);

}

// Called when the game starts or when spawned
void ALMABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmoWeapon = AmmoWeapon;
}

// Called every frame
void ALMABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALMABaseWeapon::Fire()
{
	Shoot();
	WeaponComponent->GetOwner()->GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ALMABaseWeapon::Shoot, FireFrequency, true);
}

void ALMABaseWeapon::Shoot()
{
	if (CanFire)
	{
		const FTransform SocketTransform = WeaponComponent->GetSocketTransform("Muzzle");
		const FVector TraceStart = SocketTransform.GetLocation();
		const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
		const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;
		//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 1.0f, 0, 2.0f);
		FHitResult HitResult;
		FVector TracerEnd = TraceEnd;
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
		if (HitResult.bBlockingHit)
		{
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 24, FColor::Red, false, 1.0f);
			TracerEnd = HitResult.ImpactPoint;
		}
		SpawnTrace(TraceStart, TracerEnd);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootWave, TraceStart);
		DecrementBullets();
	}
}

void ALMABaseWeapon::StopFire() {
	WeaponComponent->GetOwner()->GetWorldTimerManager().ClearTimer(FireTimerHandle);
}

void ALMABaseWeapon::ChangeClip()
{
	CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets;
}

bool ALMABaseWeapon::IsClipFull() const {
	return CurrentAmmoWeapon.Bullets == AmmoWeapon.Bullets;
}

bool ALMABaseWeapon::IsCurrentClipEmpty() const
{
	return CurrentAmmoWeapon.Bullets == 0;
}

void ALMABaseWeapon::DecrementBullets()
{
	CurrentAmmoWeapon.Bullets--;
	UE_LOG(LogWeapon, Display, TEXT("Bullets = %s"), *FString::FromInt(CurrentAmmoWeapon.Bullets));
	if (IsCurrentClipEmpty())
	{
		OnClipEmpty.Broadcast();
	}
}

void ALMABaseWeapon::SpawnTrace(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceEffect, TraceStart);
	if (TraceFX)
	{
		TraceFX->SetNiagaraVariableVec3(TraceName, TraceEnd);
	}
}