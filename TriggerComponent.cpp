// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//if(AActor* KeyActor = GetKeyActor()) UE_LOG(LogTemp, Display, TEXT("%s"), *(KeyActor->GetActorNameOrLabel()))
	//else UE_LOG(LogTemp, Display, TEXT("RElocking"));
}

AActor* UTriggerComponent::GetKeyActor() const
{
	TArray<AActor*> OverlappingActors;  // Out parameter
	GetOverlappingActors(OverlappingActors);

	if(OverlappingActors.Num() < 1) return nullptr;
	if(OverlappingActors[0]->ActorHasTag(ActorTagName)) return OverlappingActors[0];
	
	return nullptr;
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}