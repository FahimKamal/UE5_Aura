// Copyright by FK

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

class USkeletalMeshComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

private:
	static void SetHighLightValues(bool bValue, USkeletalMeshComponent& MeshComponent);
};
