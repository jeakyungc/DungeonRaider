// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"

class UInputAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
private:
	//FRotator CameraRotation;
	UPROPERTY(EditAnywhere, Category="Grab")
	float MaxDistance = 400;
	UPROPERTY(EditAnywhere, Category="Grab")
	float Radius = 100;
	UPROPERTY(EditAnywhere, Category="Grab")
	float HoldDistance = 200;

	UFUNCTION(BlueprintCallable)
	void Grab();
	UFUNCTION(BlueprintCallable)
	void Release();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
