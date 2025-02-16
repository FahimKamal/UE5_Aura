// Copyright by FK

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AuraAttributeSet.generated.h"

/**
 * Macro to define attribute accessors for easier attribute management.
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Struct to store properties related to gameplay effects, including source and target details.
 */
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	/** Default constructor */
	FEffectProperties() {}

	/** The effect context handle containing information about the gameplay effect application */
	FGameplayEffectContextHandle EffectContextHandle;

	/** Source Properties (Entity applying the effect) */
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;  /**< Ability System Component of the source */

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;  /**< Avatar actor of the source */

	UPROPERTY()
	AController* SourceController = nullptr;  /**< Controller of the source */

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;  /**< Character associated with the source */

	/** Target Properties (Entity receiving the effect) */
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;  /**< Ability System Component of the target */

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;  /**< Avatar actor of the target */

	UPROPERTY()
	AController* TargetController = nullptr;  /**< Controller of the target */

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;  /**< Character associated with the target */
};

/**
 * UAuraAttributeSet
 * 
 * A class that manages character attributes such as health and mana using Unreal's Gameplay Ability System (GAS).
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	/** Default constructor */
	UAuraAttributeSet();

	/** Replicates the attributes over the network */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Called before an attribute is changed, used to enforce attribute limits */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	/** Called after a gameplay effect is executed, allowing final attribute modifications */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/**Primary Attributes */
	/** Strength attribute, replicated with OnRep_Strength */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category= "Primary Attritutes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

	/** Intelligence attribute, replicated with OnRep_Intelligence */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category= "Primary Attritutes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	/** Resilience attribute, replicated with OnRep_Resilience */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category= "Primary Attritutes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	/** Vigor attribute, replicated with OnRep_Vigor */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category= "Primary Attritutes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

	
	/** Vital Attributes */
	/** Health attribute, replicated with OnRep_Health */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	/** Maximum health attribute, replicated with OnRep_MaxHealth */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	/** Mana attribute, replicated with OnRep_Mana */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	/** Maximum mana attribute, replicated with OnRep_MaxMana */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	/** Replication notification function for Health */
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	/** Replication notification function for MaxHealth */
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	/** Replication notification function for Mana */
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	/** Replication notification function for MaxMana */
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	/** Replication notification function for Strength */
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	/** Replication notification function for Intelligence */
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	/** Replication notification function for Resilience */
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	/** Replication notification function for Vigor */
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

private:
	/** Extracts source and target properties from gameplay effect data */
	static void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& PropsOut);
};






