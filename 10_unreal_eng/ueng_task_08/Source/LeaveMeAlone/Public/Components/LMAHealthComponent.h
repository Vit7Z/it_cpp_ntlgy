// : LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAHealthComponent.generated.h"


//DECLARE_MULTICAST_DELEGATE(FOnDeath1)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LEAVEMEALONE_API ULMAHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULMAHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth = 100.0f;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return Health; }
	UFUNCTION(BlueprintCallable)
	float GetPercentHealth() const { return Health / MaxHealth; }

	//UFUNCTION(BlueprintCallable)
	bool IsDead() const;

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	//UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	bool AddHealth(float NewHealth);
	bool IsHealthFull() const;

private:
	float Health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(
		AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
