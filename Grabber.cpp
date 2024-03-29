// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

static UPhysicsHandleComponent* PhysicsHandle;

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// get UPhysicsHandleComponent and save in static variable
	if((PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>()) == nullptr) return;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(PhysicsHandle)
	{
		FVector HoldLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(HoldLocation, GetComponentRotation());
	}
}

void UGrabber::Grab()
{
	// Early return : Double check for null pointer exception of PhysicsHandle
	if(!PhysicsHandle) return;

	struct FHitResult HitResult;
	if(GetGrabbableInReach(HitResult)){
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();

		HitResult.GetActor()->Tags.Add("Grabbed");  // Adding Tag

		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,  	// UPremitiveComponent
			NAME_None,  	// bone : for skelatal mesh
			HitResult.ImpactPoint,
			GetComponentRotation()  // Rotation of Grabber SceneComponent.
		);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("None"));
	}
}

void UGrabber::Release()
{
	if(UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(PhysicsHandle->GetGrabbedComponent()))
	{
		Component->GetOwner()->Tags.Remove("Grabbed");  // Removing Tag
		PhysicsHandle->ReleaseComponent();
	}
}

bool UGrabber::GetGrabbableInReach(struct FHitResult& OutHitResult) const
{
	// Set sweeping range Fvector
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxDistance;

	// Sweeping
	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(Radius);  // Set sweeping shape as sphere(r=100)

	// Sweep and fill OutHitResult struct, return boolean value
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		CollisionSphere
	);
}