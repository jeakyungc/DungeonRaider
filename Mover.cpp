// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// AActor* Owner = GetOwner();
	// FString OwnerName = Owner->GetActorNameOrLabel();
	
	// TArray<UStaticMeshComponent*> Components;
	// Owner->GetComponents<UStaticMeshComponent>(Components);

	// for(UStaticMeshComponent* Component : Components)
	// {
	// 	FString ComponentName = Component->GetComp
	// 	UE_LOG(LogTemp, Display, TEXT("Mover %s"), *ComponentName);
	// }
	// FVector OwnerLocation = Owner->GetActorLocation();
	// FString OwnerLocationString = OwnerLocation.ToCompactString();
	
	//UE_LOG(LogTemp, Display, TEXT("Mover %s"), *OwnerName);

	OriginalLocation = GetOwner()->GetActorLocation();	
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		
	MoveMesh(DeltaTime);
}

void UMover::MoveMesh(float DeltaTime)
{
	if(b_ShouldMove)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = OriginalLocation + MoveOffset;
		float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);
	}
}