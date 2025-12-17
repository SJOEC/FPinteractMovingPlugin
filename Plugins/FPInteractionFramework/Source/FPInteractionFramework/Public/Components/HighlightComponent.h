#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ImHighlightable.h"
#include "HighlightComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPINTERACTIONFRAMEWORK_API UHighlightComponent : public USceneComponent, public IImHighlightable
{
	GENERATED_BODY()
	
public:
	void Highlight_Implementation() override;
	void Unhighlight_Implementation() override;
	void SetHighlightState(bool bIsHighlighted);
	
public:
	UPROPERTY(EditAnywhere, Category="Highlight")
	float InteractTraceDistance = 300.0f;
	
	FHitResult InteractHitResult;
	
	UPROPERTY()
	TObjectPtr<AActor> CurrentHighlighted;

	UPROPERTY()
	TObjectPtr<AActor> LastHighlightable;
	
	UPROPERTY(EditAnywhere, Category="Highlight")
	TObjectPtr<UMaterialInterface> HighlightMaterial;
};
