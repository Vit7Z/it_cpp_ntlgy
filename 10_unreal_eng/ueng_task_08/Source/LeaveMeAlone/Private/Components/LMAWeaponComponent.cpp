// : LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Components/LMAWeaponComponent.h"
#include "Weapon/LMABaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/LMAReloadFinishedAnimNotify.h"

// Sets default values for this component's properties
ULMAWeaponComponent::ULMAWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void ULMAWeaponComponent::Fire() {
	if (IsValid(Weapon) && !AnimReloading)
	{
		Weapon->Fire();
	}
	DoFire = true;
}

void ULMAWeaponComponent::FireStop() {
	if (IsValid(Weapon))
	{
		Weapon->FireStop();
	}
	DoFire = false;
}

void ULMAWeaponComponent::Reload() {
	DoReload();
}

bool ULMAWeaponComponent::GetCurrentWeaponAmmo(FAmmoWeapon& AmmoWeapon) const
{
	if (IsValid(Weapon))
	{
		AmmoWeapon = Weapon->GetCurrentAmmoWeapon();
		return true;
	}
	return false;
}


// Called when the game starts
void ULMAWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	InitAnimNotify();
}


// Called every frame
void ULMAWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULMAWeaponComponent::SpawnWeapon() {
	Weapon = GetWorld()->SpawnActor<ALMABaseWeapon>(WeaponClass);
	if (Weapon)
	{
		const auto Character = Cast<ACharacter>(GetOwner());
		if (Character)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "r_Weapon_Socket");
			Weapon->OnCurrentlyClipEmpty.AddUObject(this, &ULMAWeaponComponent::DoReload);
		}
	}
}

void ULMAWeaponComponent::InitAnimNotify() {
	if (!IsValid(ReloadMontage))
		return;
	const auto NotifiesEvents = ReloadMontage->Notifies;
	for (auto NotifyEvent : NotifiesEvents)
	{
		auto ReloadFinish = Cast<ULMAReloadFinishedAnimNotify>(NotifyEvent.Notify);
		{
			ReloadFinish->OnNotifyReloadFinished.AddUObject(this, &ULMAWeaponComponent::OnNotifyReloadFinished);
			break;
		}
	}
}

void ULMAWeaponComponent::OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh) {
	const auto Charactr = Cast<ACharacter>(GetOwner());
	if (Charactr->GetMesh() == SkeletalMesh)
	{
		AnimReloading = false;
		if (DoFire)
		{
			Fire();
		}
	}
}

bool ULMAWeaponComponent::CanReload() const
{
	return (!AnimReloading && !Weapon->IsCurrentClipFull());
}

void ULMAWeaponComponent::DoReload() {
	if (!CanReload())
		return;
	if (DoFire)
	{
		FireStop();
		DoFire = true;
	}
	Weapon->ChangeClip();
	AnimReloading = true;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->PlayAnimMontage(ReloadMontage);
}

