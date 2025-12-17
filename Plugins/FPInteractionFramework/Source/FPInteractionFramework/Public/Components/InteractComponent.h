#pragma once


#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractComponent.generated.h"

UCLASS()
class FPINTERACTIONFRAMEWORK_API UInteractComponent : public USceneComponent
{
	GENERATED_BODY()
public:
	UInteractComponent();
	
	void BeginPlay() override;
	
	void TryInteract(const USceneComponent* Origin);
	void TryHighlight(const USceneComponent* Origin);

protected:
	
	UPROPERTY(EditAnywhere, Category="Interaction")
	float InteractTraceDistance = 300.0f;

	UPROPERTY(VisibleInstanceOnly, Category="Interaction")
	TObjectPtr<AActor> CurrentHighlightedActor = nullptr;
	
	UPROPERTY()
	TObjectPtr<UActorComponent> CurrentHighlightedComponent = nullptr;

	FHitResult InteractHitResult;

	bool bCanInteract = true;
	
};