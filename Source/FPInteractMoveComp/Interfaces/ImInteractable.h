#pragma once

#include "CoreMinimal.h"
#include "Enums/EInteractableType.h"
#include "ImInteractable.generated.h"

UINTERFACE(BlueprintType)
class FPINTERACTMOVECOMP_API UImInteractable : public UInterface
{
	GENERATED_BODY()
};

class FPINTERACTMOVECOMP_API IImInteractable
{
	GENERATED_BODY()

public:

	// Called when the player interacts
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void Interact();

	// Used to identify interactable type
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	EInteractableType GetInterfaceType() const;
};