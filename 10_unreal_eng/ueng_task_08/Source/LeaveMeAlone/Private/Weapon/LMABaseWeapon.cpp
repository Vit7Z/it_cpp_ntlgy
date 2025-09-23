// : LeaveMeAlone Game by Netologiya. All RightsReserved.

#include "Weapon/LMABaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);

// Sets default values
ALMABaseWeapon::ALMABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	SetRootComponent(WeaponComponent);
}

void ALMABaseWeapon::Fire()
{
	if (GetWorldTimerManager().IsTimerActive(TimerClearTimerFire))
	{
		GetWorldTimerManager().SetTimer(FireRateTimer, this, &ALMABaseWeapon::Shoot, CurrentAmmoWeapon.FireRate, true,
			GetWorldTimerManager().GetTimerRemaining(TimerClearTimerFire));
		GetWorldTimerManager().ClearTimer(TimerClearTimerFire);
		
	}
	else
	{
		GetWorldTimerManager().SetTimer(FireRateTimer, this, &ALMABaseWeapon::Shoot, CurrentAmmoWeapon.FireRate, true, 0);
	}
}

void ALMABaseWeapon::FireStop()
{
	GetWorldTimerManager().SetTimer(TimerClearTimerFire, GetWorldTimerManager().GetTimerRemaining(FireRateTimer), false);
	GetWorldTimerManager().ClearTimer(FireRateTimer);
}

void ALMABaseWeapon::ChangeClip()
{
	CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets;
}

// Called when the game starts or when spawned
void ALMABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmoWeapon = AmmoWeapon;
}

void ALMABaseWeapon::Shoot()
{
	const FTransform SocketTransform = WeaponComponent->GetSocketTransform("Muzzle");
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 1.0f, 0, 2.0f);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	if (HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 24, FColor::Red, false, 1.0f);
	}

	DecrementBullets();
}

void ALMABaseWeapon::DecrementBullets()
{
	CurrentAmmoWeapon.Bullets--;
	if (IsCurrentClipEmpty())
	{
		OnCurrentlyClipEmpty.Broadcast();
		ChangeClip();
	}
}

bool ALMABaseWeapon::IsCurrentClipEmpty() const
{
	return CurrentAmmoWeapon.Bullets == 0;
}

bool ALMABaseWeapon::IsCurrentClipFull() const
{
	return CurrentAmmoWeapon.Bullets == AmmoWeapon.Bullets;
}

// Called every frame
void ALMABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
