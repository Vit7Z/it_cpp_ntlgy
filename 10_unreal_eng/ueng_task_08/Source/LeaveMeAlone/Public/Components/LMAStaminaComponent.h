// : LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAStaminaComponent.generated.h"

//DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, NewStamina);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LEAVEMEALONE_API ULMAStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULMAStaminaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxStamina = 100.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DecreaseStamina = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float IncreaseStamina = 5.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DelayIncreaseStamina = 2.0f;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnStaminaChanged OnStaminaChanged;

	UFUNCTION(BlueprintCallable)
	float GetStamina() const { return Stamina; }

	void StaminaDecrease();
	void StaminaIncrease();
	bool IsStaminaFull() const;
	bool IsStaminaEmpty() const;

private:
	float Stamina = 0.0f;
	FTimerHandle IncreaseTimerHandle;
	void Increase();
	void StartTimer();
	void StopTimer();
};
