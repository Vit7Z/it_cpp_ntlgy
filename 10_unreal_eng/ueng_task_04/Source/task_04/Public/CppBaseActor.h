// Fill out your copyright notice in the Description page of Project Settings.

#pragma once //контроль единичного подключения данного файла

#include "CoreMinimal.h"//в этом заголовочном файле определены базовые данные о классах и типах, а также инструменты для логирования
#include "GameFramework/Actor.h" //заголовочный файл класса, от которого происходит наследование
//CppBaseActor.generated.h - автоматически генерируемый заголовочный файл. Движок генерирует подобный файл для каждого класса, 
// а также в нем находится мета-информация о классе.
//Важно!!! Он должен всегда идти последним в списке директив.
#include "CppBaseActor.generated.h"

//UCLASS(), MYPROJECT_API, GENERATED_BODY() - специализированные макросы, необходимые для того, чтобы UE видел данный класс в дальнейшем

UENUM(BlueprintType)
enum class EMovementState : uint8 //Все Enum’ы в Unreal Engine строго типизированные, они имеют тип uint8. В движке реализована система собственных типов, данный тип означает, что у Enum’а не может быть более чем 255 элементов.
{
	Mobility,
	Static
};

USTRUCT(BlueprintType)
struct FTransformStruct
{
	GENERATED_USTRUCT_BODY() //данный макрос необходим для корректной обработки сгенерированного кода анализатором IntelliSense. Данный анализатор осуществляет синтаксический анализ объявленной структуры.
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CurrentLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator CurrentRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CurrentScale = FVector(1.0f, 1.0f, 1.0f);

};

UCLASS()
class MYPROJECT_API ACppBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACppBaseActor(); //конструктор класса

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; //эта функция вызывается один раз при старте игры, или когда актор заспаунен (создан в процессе игры)
	
	UPROPERTY(VisibleAnywhere) // свойство отображается во всех окнах свойств, но не может быть изменено;
	UStaticMeshComponent* Mesh; //StaticMeshComponent используется для создания экземпляра UStaticMesh, или же статической сетки, т.е. части геометрии, состоящей из статического набора полигонов.

	//UPROPERTY(VisibleAnywhere) // свойство отображается во всех окнах свойств, но не может быть изменено;
	//FString PlayerName = GetName(); 

	UPROPERTY(EditInstanceOnly) // свойство отображается во всех окнах свойств, но не может быть изменено;
	FString PlayerName = "A_CppBase_name_test";

	UPROPERTY(EditAnywhere)  //свойство можно редактировать в окнах свойств на архетипах и экземплярах;
	//UPROPERTY(EditInstanceOnly)  //свойство можно редактировать в окнах свойств, но только в экземплярах
	int EnemyNum = 20;

	UPROPERTY(EditDefaultsOnly)  //свойство можно редактировать в окнах свойств, но только на архетипах;
	float CurrentHealth = 57.54687;

	UPROPERTY(EditInstanceOnly)  //свойство можно редактировать в окнах свойств, но только в экземплярах
	bool IsAlive = true;
	
	UPROPERTY(EditAnywhere) 
	float Amplitude2 = 100;
	
	UPROPERTY(EditAnywhere) 
	float Frequency2 = 10;
	
	UPROPERTY(EditAnywhere) 
	FVector InitialLocation2 = FVector::ZeroVector;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; //эта функция срабатывает каждый frame процессора. Параметр DefaultTime - это разница по времени между текущим и предыдущим фреймами

private:
	
	void ShowActorInformation();

protected:
	UFUNCTION(BlueprintCallable) //доступ, чтобы работать с функцией внутри редактора
	void ShowInformation();

	UFUNCTION(BlueprintCallable)
	FVector SinMovement();
};
