// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// ! Addtional Check : SM is Door_Secrete
	TArray<UStaticMeshComponent*> SMDoors;
	GetOwner()->GetComponents<UStaticMeshComponent>(SMDoors);
	LDoor = SMDoors[1];
	RDoor = SMDoors[2];
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//MoveMesh(DeltaTime);
	DoorMover(LDoor, DeltaTime);
	DoorMover(RDoor, DeltaTime);
}

void UMover::MoveMesh(float DeltaTime)
{
	// if(!b_ShouldMove) return;
	// FVector CurrentLocation = GetOwner()->GetActorLocation();
	// FVector TargetLocation = OriginalLocation + MoveOffset;
	// float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;

	// FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	// GetOwner()->SetActorLocation(NewLocation);
}

void UMover::DoorMover(UStaticMeshComponent* HalfDoor, float DeltaTime)
{
	if(!b_ShouldMove) return;

	FRotator CurrentRotation = HalfDoor->GetComponentRotation();
	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, Speed);
	
	HalfDoor->SetWorldRotation(NewRotation);
}

void UMover::SetShouldMove(bool b_value)
{
	b_ShouldMove = b_value;
}