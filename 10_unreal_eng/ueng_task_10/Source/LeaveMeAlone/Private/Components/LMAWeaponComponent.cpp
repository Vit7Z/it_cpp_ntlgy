// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Components/LMAWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/LMABaseWeapon.h"
#include "Animations/LMAReloadFinishedAnimNotify.h"

// Sets default values for this component's properties
ULMAWeaponComponent::ULMAWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULMAWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	InitAnimNotify();

	// ...
	
}


// Called every frame
void ULMAWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULMAWeaponComponent::SpawnWeapon()
{
	Weapon = GetWorld()->SpawnActor<ALMABaseWeapon>(WeaponClass);
	if (Weapon)
	{
		const auto Character = Cast<ACharacter>(GetOwner());
		if (Character)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "r_Weapon_Socket");
		}
	}
	Weapon->OnClipEmpty.AddUObject(this, &ULMAWeaponComponent::Reload);
}

void ULMAWeaponComponent::Fire()
{
	if (Weapon && !AnimReloading)
	{
		FiringOn = true;
		Weapon->CanFire = CanFire();
		Weapon->Fire();
	}
}

void ULMAWeaponComponent::SetCanFire(const bool PlayerCanFire_)
{
	PlayerCanFire = PlayerCanFire_;
	Weapon->CanFire = CanFire();
}


void ULMAWeaponComponent::StopFire()
{
	FiringOn = false;
	Weapon->CanFire = CanFire();
	Weapon->StopFire();
}

void ULMAWeaponComponent::InitAnimNotify()
{
	if (!ReloadMontage)
		return;
	const auto NotifiesEvents = ReloadMontage->Notifies;
	for (auto NotifyEvent : NotifiesEvents)
	{
		auto ReloadFinish = Cast<ULMAReloadFinishedAnimNotify>(NotifyEvent.Notify);
		if (ReloadFinish)
		{
			ReloadFinish->OnNotifyReloadFinished.AddUObject(this, &ULMAWeaponComponent::OnNotifyReloadFinished);
			break;
		}
	}
}

void ULMAWeaponComponent::OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh)
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (Character->GetMesh() == SkeletalMesh)
	{
		AnimReloading = false;
		Weapon->CanFire = CanFire();
	}
}

bool ULMAWeaponComponent::CanReload() const
{
	return !AnimReloading && !Weapon->IsClipFull();
}

bool ULMAWeaponComponent::CanFire() const
{
	return PlayerCanFire && FiringOn && !AnimReloading;
}

void ULMAWeaponComponent::Reload()
{
	if (!CanReload())
		return;
	Weapon->ChangeClip();
	AnimReloading = true;
	Weapon->CanFire = CanFire();
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->PlayAnimMontage(ReloadMontage);
}

bool ULMAWeaponComponent::GetCurrentWeaponAmmo(FAmmoWeapon& AmmoWeapon) const
{
	if (Weapon)
	{
		AmmoWeapon = Weapon->GetCurrentAmmoWeapon();
		return true;
	}
	return false;
}