// Fill out your copyright notice in the Description page of Project Settings.


#include "FPInteractionFramework/Public/Components/MovingComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMovingComponent::UMovingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UMovingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		StartLocation = GetOwner()->GetActorLocation();
		StartRotation = GetOwner()->GetActorRotation();

		OriginalLocation = StartLocation;
		OriginalRotation = StartRotation;

		UE_LOG(LogTemp, Log, TEXT("Start Pos: %s"), *StartLocation.ToString());
		UE_LOG(LogTemp, Log, TEXT("Start Rot: %s"), *StartRotation.ToString());
	}


}

void UMovingComponent::MoveComponentSmoothly()
{
	if (bIsMoving)
	{
		return;
	}

	StartLocation = GetOwner()->GetActorLocation();
	StartRotation = GetOwner()->GetActorRotation();

	ClearTimerValues();

	if (bReturnOnSecondInteraction && bIsSecondInteraction)
	{
		TargetLocation = OriginalLocation;
		TargetRotation = OriginalRotation;

	}
	else
	{
		TargetLocation = StartLocation + ExpectedMovement;
		TargetRotation = StartRotation + ExpectedRotation;
	}

	bCanMove = true;
	bIsMoving = true;

	if (GetOwner()->GetWorld())
	{
		GetOwner()->GetWorld()->GetTimerManager().SetTimer(
			MoveTimerHandle,
			this,
			&UMovingComponent::TickMove,
			0.01f, // 100 updates por segundo
			true
		);
	}


}

void UMovingComponent::TickMove()
{
	if (GetWorld())
	{
		ElapsedTime += GetWorld()->GetDeltaSeconds();
	}

	Alpha = FMath::Clamp(ElapsedTime / Duration, 0.f, 1.f);

	if (MyFloatCurve)
	{
		CurveValue = MyFloatCurve->GetFloatValue(Alpha);
	}
	else
	{
		CurveValue = Alpha;
	}

	FVector NewPos = FMath::Lerp(StartLocation, TargetLocation, CurveValue);

	FRotator NewRot = FMath::Lerp(StartRotation, TargetRotation, CurveValue);

	GetOwner()->SetActorLocationAndRotation(NewPos, NewRot);

	if (Alpha >= 1.f)
	{
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
		}
		GetOwner()->SetActorLocationAndRotation(TargetLocation, TargetRotation);

		bIsSecondInteraction = !bIsSecondInteraction;
		bIsMoving = false;
	}
}

void UMovingComponent::ClearTimerValues()
{
	Alpha = 0;
	ElapsedTime = 0;
}

void UMovingComponent::Interact_Implementation()
{
	MoveComponentSmoothly();
	
	if (InteractionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, InteractionSound, GetOwner()->GetActorLocation());
	}
}

EInteractableType UMovingComponent::GetInterfaceType_Implementation() const
{
	return EInteractableType::EIT_ImGenericInteractable;
}
