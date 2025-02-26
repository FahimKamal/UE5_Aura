// Copyright by FK

#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "ShaderPrintParameters.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon-> SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon-> SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();	
}

FVector AAuraCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
	
}

void AAuraCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.0f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.0f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.0f);
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;

	UAuraAbilitySystemComponent* AuraASU = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);

	AuraASU->AddCharacterAbilities(StartupAbilities);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


