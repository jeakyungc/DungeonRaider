// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()
private:
	//Mesh Mover
	//UPROPERTY(EditAnywhere) FVector MoveOffset;
	//UPROPERTY(EditAnywhere) float MoveTime = 4;
	//FVector OriginalLocation;

	//Mesh Rotator
	UPROPERTY(EditAnywhere) FRotator TargetRotation;
	UPROPERTY(EditAnywhere) float Speed;
	
	bool b_ShouldMove = false;
	UStaticMeshComponent* LDoor;
	UStaticMeshComponent* RDoor;

public:	
	// Sets default values for this component's properties
	UMover();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldMove(bool b_ShouldMove);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void MoveMesh(float DeltaTime);
	void DoorMover(UStaticMeshComponent* HalfDoor, float DeltaTime);
};