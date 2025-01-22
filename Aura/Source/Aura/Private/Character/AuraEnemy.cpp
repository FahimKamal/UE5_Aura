// Copyright by FK


#include "Character/AuraEnemy.h"

void AAuraEnemy::HighlightActor()
{
	bHighlighted = true;
	SetHighLightValues(bHighlighted,*GetMesh());
	// GetMesh()->SetRenderCustomDepth(true);
	// GetMesh()->SetCustomDepthStencilValue(250);

	SetHighLightValues(bHighlighted, *Weapon);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(250);
}

void AAuraEnemy::UnHighlightActor()
{
	bHighlighted = false;
	// GetMesh()->SetRenderCustomDepth(false);
	SetHighLightValues(bHighlighted,*GetMesh());
	SetHighLightValues(bHighlighted, *Weapon);
}


void AAuraEnemy::SetHighLightValues(bool bValue, USkeletalMeshComponent& MeshComponent)
{
	MeshComponent.SetRenderCustomDepth(bValue);
	if (bValue)
	{
		MeshComponent.SetCustomDepthStencilValue(250);
	}
}


