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
	
	if(AActor* KeyActor = GetKeyActor())  // nullptr check here
	{
		// check rootComponent USceneComponent is UPrimitiveComponent. If not, returns nullptr
		if(UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(KeyActor->GetRootComponent()))
			RootComponent->SetSimulatePhysics(false);
		KeyActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else Mover->SetShouldMove(false);
}

AActor* UTriggerComponent::GetKeyActor() const
{
	TArray<AActor*> OverlappingActors;  // Out parameter
	GetOverlappingActors(OverlappingActors);

	if(OverlappingActors.Num() < 1) return nullptr;
	
	AActor* OverlappedActor = OverlappingActors[0];
	if(OverlappedActor->ActorHasTag(ActorTagName) && !OverlappedActor->ActorHasTag("Grabbed")) return OverlappedActor;
	
	return nullptr;
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}