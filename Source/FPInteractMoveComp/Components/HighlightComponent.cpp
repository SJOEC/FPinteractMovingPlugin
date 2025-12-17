#include "HighlightComponent.h"

#include "Interfaces/ImHighlightable.h"

void UHighlightComponent::SetHighlightState(bool bIsHighlighted)
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	// Buscamos TODOS los componentes visuales (StaticMesh, SkeletalMesh, etc.)
	TArray<UMeshComponent*> Meshes;
	Owner->GetComponents<UMeshComponent>(Meshes);

	for (UMeshComponent* Mesh : Meshes)
	{
		if (Mesh)
		{
			Mesh->SetOverlayMaterial(bIsHighlighted ? HighlightMaterial : nullptr);
		}
	}
}


void UHighlightComponent::Highlight_Implementation()
{
	SetHighlightState(true);
}

void UHighlightComponent::Unhighlight_Implementation()
{
	SetHighlightState(false);
}
