// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppHubActor.generated.h"

class ACppBaseActor;

UCLASS()
class MYPROJECT_API ACppHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACppHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//переменные будут отвечать за частоту срабатывания таймера в секундах
	UPROPERTY(EditAnywhere)
	float SpawnTimerRate = 2.0f;

	UPROPERTY(EditAnywhere)
	float DestroyTimerRate = 1.0f;

	FTimerHandle SpawnTimerHandle;
	FTimerHandle DestroyTimerHandle;

	//методы, которые будут вызываться при срабатывании таймера
	void OnTimeToSpawn();
	void OnTimeToDestroy();


	//const int32 TotalCount = 10; // -данная переменная будет хранить информацию о максимальной количестве срабатываний таймера.
	const int32 TotalTimerCount = 10; //-данная переменная будет хранить информацию о максимальной количестве срабатываний таймера.
	int32 CurrentTimerCount = 0; //-текущее число срабатываний.

	UPROPERTY()
	TArray<ACppBaseActor*> SpawnedObjects; //массив объектов, который будем заполнять по мере спауна новых объектов

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACppBaseActor> CppClass; //указатель на класс, который мы планируем спаунить.

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
