// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"  //For 'GetWorld() and related to UWorld'
#include "DrawDebugHelpers.h"  //For Debuging Objects
//#include "Math/Vector.h"  //For '.ToCompactString()'
#include "PhysicsEngine/PhysicsHandleComponent.h"

static UPhysicsHandleComponent* PhysicsHandle;

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

	// FRotator CameraRotation = GetComponentRotation();
	// FString str = CameraRotation.ToCompactString();
	// UE_LOG(LogTemp, Display, TEXT("Rot: %s"), *str);

	// UWorld* WorldPtr = GetWorld();
	// float ElapsedTime = WorldPtr->TimeSeconds;
	// UE_LOG(LogTemp, Display, TEXT("ElapsedTime: %f"), ElapsedTime);
	
	FVector HoldLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation(HoldLocation, GetComponentRotation());
}

void UGrabber::Grab()
{
	// Early return : Double check for null pointer exception of PhysicsHandle
	if(!PhysicsHandle) return;

	// Set sweeping range Fvector
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxDistance;

	// Drawing Debug Objects
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

	// Sweeping
	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(Radius);  // Set sweeping shape as sphere(r=100)
	
	// Sweep and fill OutHitResult struct
	struct FHitResult OutHitResult;
	bool b_hasHit = GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		CollisionSphere
	);
	
	if(b_hasHit){
		// (Commented out) Debugging and Logging stuffs
		// DrawDebugSphere(GetWorld(), OutHitResult.Location, 10, 10, FColor::Yellow, false, 5);
		// DrawDebugSphere(GetWorld(), OutHitResult.ImpactPoint, 10, 10, FColor::Green, false, 5);
		// FString SweepedActorName = OutHitResult.GetActor()->GetActorNameOrLabel();
		// UE_LOG(LogTemp, Display, TEXT("Can Grab : %s"), *SweepedActorName);

		//
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			OutHitResult.GetComponent(),  //UPremitiveComponent
			NAME_None,  // bone : for skelatal mesh
			OutHitResult.ImpactPoint,
			OutHitResult.GetComponent()->GetComponentRotation()
		);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Can Grab : None"));
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("RELEASED"));
}