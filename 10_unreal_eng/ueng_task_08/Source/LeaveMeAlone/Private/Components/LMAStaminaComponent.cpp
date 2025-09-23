// : LeaveMeAlone Game by Netologiya. All RightsReserved.

#include "Components/LMAStaminaComponent.h"

// Sets default values for this component's properties
ULMAStaminaComponent::ULMAStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void ULMAStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	Stamina = MaxStamina;
}

// Called every frame
void ULMAStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULMAStaminaComponent::StaminaDecrease()
{
	if (!IsStaminaEmpty())
	{
		StopTimer();
		Stamina = FMath::Clamp(Stamina - DecreaseStamina, 0.0f, MaxStamina);
		OnStaminaChanged.Broadcast(Stamina/MaxStamina);
	}
}

void ULMAStaminaComponent::StaminaIncrease()
{
	if (IsStaminaFull())
	{
		// После восстановления выносливости останавливаем таймер
		StopTimer();
	}
	else
	{
		StartTimer();
	}
}

bool ULMAStaminaComponent::IsStaminaFull() const
{
	return FMath::IsNearlyEqual(Stamina, MaxStamina);
}

bool ULMAStaminaComponent::IsStaminaEmpty() const
{
	return (Stamina <= 0.0f);
}

void ULMAStaminaComponent::Increase()
{
	Stamina = FMath::Clamp(Stamina + IncreaseStamina, 0.0f, MaxStamina);
	OnStaminaChanged.Broadcast(Stamina/MaxStamina);
	StaminaIncrease();
}

void ULMAStaminaComponent::StartTimer()
{
	if (!IncreaseTimerHandle.IsValid()) // Запускаем таймер 
	{
		AActor* OwnerComponent = GetOwner();
		if (IsValid(OwnerComponent))
		{
			OwnerComponent->GetWorldTimerManager().SetTimer(
				IncreaseTimerHandle, this, &ULMAStaminaComponent::Increase, DelayIncreaseStamina, true);
		}
	}
}

void ULMAStaminaComponent::StopTimer()
{
	if (IncreaseTimerHandle.IsValid()) // останавливаем таймер
	{
		AActor* OwnerComponent = GetOwner();
		if (IsValid(OwnerComponent))
		{
			OwnerComponent->GetWorldTimerManager().ClearTimer(IncreaseTimerHandle);
		}
	}
}
