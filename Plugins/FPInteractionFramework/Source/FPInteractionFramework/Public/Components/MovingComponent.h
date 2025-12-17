// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Interfaces/ImInteractable.h"
#include "MovingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPINTERACTIONFRAMEWORK_API UMovingComponent : public USceneComponent, public IImInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMovingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	
	// move component
	void MoveComponentSmoothly();
	void ClearTimerValues();

	// interaction
	void Interact_Implementation() override;
	virtual EInteractableType GetInterfaceType_Implementation() const override;
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TObjectPtr<USoundBase> InteractionSound;
	
	UPROPERTY(EditAnywhere, Category = "Move Component")
	FVector ExpectedMovement = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Move Component")
	FRotator ExpectedRotation = FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere, Category = "Move Component")
	bool bReturnOnSecondInteraction = false;
	UPROPERTY(EditAnywhere, Category = "Move Component")
	TObjectPtr<UCurveFloat> MyFloatCurve = nullptr;
	UPROPERTY(EditAnywhere, Category = "Move Component")
	float Duration = 1.f;

	
	FTimerHandle MoveTimerHandle;

	FVector OriginalLocation = FVector::ZeroVector ;
	FRotator OriginalRotation = FRotator::ZeroRotator;
	
	FVector StartLocation = FVector::ZeroVector;
	FRotator StartRotation = FRotator::ZeroRotator;

	FVector TargetLocation = FVector::ZeroVector;
	FRotator TargetRotation = FRotator::ZeroRotator;

	float ElapsedTime = 0.f;
	float CurveValue = 0.f;
	
	bool bCanMove = false;
	bool bCanRotate = false;


	bool bIsMoving = false;
	bool bIsSecondInteraction = false;

	float Alpha = 0.f;


	
	UFUNCTION()
	void TickMove();

};
