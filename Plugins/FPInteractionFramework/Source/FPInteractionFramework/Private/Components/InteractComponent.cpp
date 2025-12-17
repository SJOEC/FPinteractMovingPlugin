#include "FPInteractionFramework/Public/Components/InteractComponent.h"

#include "Interfaces/ImHighlightable.h"
#include "Interfaces/ImInteractable.h"

UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractComponent:: TryInteract(const USceneComponent* Origin)
{
	
	if (!bCanInteract || !Origin)
	{
		return;
	}

	FVector Start = Origin->GetComponentLocation();
	FVector End = Start + (Origin->GetForwardVector() * InteractTraceDistance);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, QueryParams);

	AActor* HitActor = Hit.GetActor();
	
	if (!HitActor) return;

	TInlineComponentArray<UActorComponent*> HitActorComponents;
	HitActor->GetComponents(HitActorComponents);
	
	for (UActorComponent* Comp : HitActorComponents)
	{
		if (Comp && Comp->Implements<UImInteractable>())
		{

			//GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,TEXT("Found Interactable"));

			IImInteractable::Execute_Interact(Comp);
		}
	}
}

void UInteractComponent::TryHighlight(const USceneComponent* Origin)
{
    if (!IsValid(Origin)) return;

    const FVector TraceStart = Origin->GetComponentLocation();
    const FVector Forward = Origin->GetForwardVector();
    const FVector TraceEnd = TraceStart + (Forward * InteractTraceDistance);
	
	// ignore player
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwner());

    bool bHit = GetWorld()->LineTraceSingleByChannel(
       InteractHitResult,
       TraceStart,
       TraceEnd,
       ECC_Visibility,
       QueryParams
    );

    AActor* HitActor = InteractHitResult.GetActor();

    // case actor
    if (HitActor == CurrentHighlightedActor)
    {
       return; 
    }

    // 2. unhighlight old actor
    if (CurrentHighlightedComponent)
    {
        if (IsValid(CurrentHighlightedComponent) && CurrentHighlightedComponent->Implements<UImHighlightable>())
        {
            IImHighlightable::Execute_Unhighlight(CurrentHighlightedComponent);
        }
        
        CurrentHighlightedComponent = nullptr;
        CurrentHighlightedActor = nullptr;
    }

    // try highlight new object
    if (HitActor)
    {
    	
        TInlineComponentArray<UActorComponent*> HitActorComponents;
        HitActor->GetComponents(HitActorComponents);

        for (UActorComponent* Comp : HitActorComponents)
        {
            if (Comp && Comp->Implements<UImHighlightable>())
            {
                CurrentHighlightedComponent = Comp;
                CurrentHighlightedActor = HitActor; 
                
                IImHighlightable::Execute_Highlight(CurrentHighlightedComponent);
            	
                break; 
            }
        }
    }
}




