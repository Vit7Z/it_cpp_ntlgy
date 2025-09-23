// : LeaveMeAlone Game by Netologiya. All RightsReserved.

#include "Player/LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/LMAHealthComponent.h"
#include "Components/LMAStaminaComponent.h"
#include "Components/LMAWeaponComponent.h"

// Sets default values
ALMADefaultCharacter::ALMADefaultCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = ArmLength;
	SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetFieldOfView(FOV);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	//  6
	HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");
	// DZ 6
	StaminaComponent = CreateDefaultSubobject<ULMAStaminaComponent>("StaminaComponent");
	// 7
	WeaponComponent = CreateDefaultSubobject<ULMAWeaponComponent>("Weapon");
}

// Called when the game starts or when spawned
void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
	}
	OnHealthChanged(HealthComponent->GetHealth());
	//HealthComponent->OnDeath.AddUObject(this, &ALMADefaultCharacter::OnDeath);
	HealthComponent->OnDeath.AddDynamic(this, &ALMADefaultCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ALMADefaultCharacter::OnHealthChanged);
	//HealthComponent->OnHealthChanged.Add(this, &ALMADefaultCharacter::OnHealthChanged);

	OnStaminaChanged(StaminaComponent->GetStamina());
	StaminaComponent->OnStaminaChanged.AddDynamic(this, &ALMADefaultCharacter::OnStaminaChanged);
}

// Called every frame
void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!(HealthComponent->IsDead()))
	{
		RotationPlayerOnCursor();
	}
}

// Called to bind functionality to input
void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);
	// DZ 5
	PlayerInputComponent->BindAxis("CameraZoom", this, &ALMADefaultCharacter::CameraZoom);
	// DZ 6
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ALMADefaultCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALMADefaultCharacter::StopSprint);
	// 7
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &ULMAWeaponComponent::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &ULMAWeaponComponent::FireStop);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &ULMAWeaponComponent::Reload);
}

void ALMADefaultCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		Sprint(Value);
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ALMADefaultCharacter::MoveRight(float Value)
{
	if ( Value != 0.0f)
	{
		Sprint(Value);
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ALMADefaultCharacter::CameraZoom(float Value)
{
	float tmpArmLength = ArmLength + ZoomSpeed * Value;
	if (tmpArmLength > ArmLengthMax)
	{
		tmpArmLength = ArmLengthMax;
	}
	else if (tmpArmLength < ArmLengthMin)
	{
		tmpArmLength = ArmLengthMin;
	}
	ArmLength = tmpArmLength;
	SpringArmComponent->TargetArmLength = ArmLength;
}

void ALMADefaultCharacter::OnDeath()
{
	CurrentCursor->DestroyRenderState_Concurrent();
	PlayAnimMontage(DeathMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ALMADefaultCharacter::RotationPlayerOnCursor()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
		if (CurrentCursor)
		{
			CurrentCursor->SetWorldLocation(ResultHit.Location);
		}
	}
}

void ALMADefaultCharacter::OnHealthChanged(float NewHealth)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"), NewHealth));
}

void ALMADefaultCharacter::StartSprint()
{
	IsSprint = true;
}

void ALMADefaultCharacter::StopSprint()
{
	IsSprint = false;
}

void ALMADefaultCharacter::OnStaminaChanged(float NewStamina)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Stamina = %f"), NewStamina));
}

void ALMADefaultCharacter::Sprint(float Value)
{
	if (IsSprint && Value != 0.0f)
	{
		if (!StaminaComponent->IsStaminaEmpty())
		{
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
			StaminaComponent->StaminaDecrease();
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = 300.0f;
			StaminaComponent->StaminaIncrease();
		}
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		StaminaComponent->StaminaIncrease();

	}
}
