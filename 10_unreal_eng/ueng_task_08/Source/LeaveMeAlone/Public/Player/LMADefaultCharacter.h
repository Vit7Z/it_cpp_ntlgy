// : LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;
class UAnimMontage;
class ULMAStaminaComponent;
class ULMAWeaponComponent;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALMADefaultCharacter();

	UFUNCTION()
	ULMAHealthComponent* GetHealthComponent() const { return HealthComponent; }
	UFUNCTION(BlueprintCallable)
	bool OnSprint() const { return IsSprint; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;
	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);
	//DZ 5
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom")
	float ArmLengthMax = 4000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom")
	float ArmLengthMin = 400.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom")
	float ZoomSpeed = 75.0f;
	// 6
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
	ULMAHealthComponent* HealthComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;
	//DZ 6
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Stamina")
	ULMAStaminaComponent* StaminaComponent;
	//7
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components");
	ULMAWeaponComponent* WeaponComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float YRotation = -75.0f;
	float ArmLength = 1400.0f;
	float FOV = 55.0f;
	bool IsSprint = false;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void CameraZoom(float Value);
	//6
	UFUNCTION()
	void OnDeath();
	void RotationPlayerOnCursor();
	void OnHealthChanged(float NewHealth);
	//DZ6
	void StartSprint();
	void StopSprint();
	UFUNCTION()
	void OnStaminaChanged(float NewStamina);
	void Sprint(float Value);
};
