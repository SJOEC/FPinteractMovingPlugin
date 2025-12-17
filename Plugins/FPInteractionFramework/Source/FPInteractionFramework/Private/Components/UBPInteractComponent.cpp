#include "FPInteractionFramework/Public/Components/UBPInteractComponent.h"

UBPInteractComponent::UBPInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBPInteractComponent::Interact_Implementation()
{
	if (OnInteractTriggered.IsBound())
	{
		OnInteractTriggered.Broadcast(GetOwner());
        
		UE_LOG(LogTemp, Log, TEXT("Evento enviado a Blueprints desde C++"));
	}
}
