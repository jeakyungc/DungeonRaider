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
	UPROPERTY(EditAnywhere)FVector MoveOffset;
	UPROPERTY(EditAnywhere) float MoveTime = 4;
	UPROPERTY(EditAnywhere) bool b_ShouldMove = false;

	FVector OriginalLocation;

public:	
	// Sets default values for this component's properties
	UMover();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void MoveMesh(float DeltaTime);
};
