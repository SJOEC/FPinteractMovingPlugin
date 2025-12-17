#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/ImInteractable.h"
#include "UBPInteractComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractSignature, AActor*, Interactor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPINTERACTMOVECOMP_API UBPInteractComponent : public UActorComponent, public IImInteractable
{
	GENERATED_BODY()

public:	
	UBPInteractComponent();

	// --- INTERFACE IMPLEMENTATION ---//
	virtual void Interact_Implementation() override;
	
	virtual EInteractableType GetInterfaceType_Implementation() const override
	{
		return EInteractableType::EIT_ImGenericInteractable;
	}

	// --- EVENTS --- //
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractSignature OnInteractTriggered;
};