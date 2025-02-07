// Copyright by FK

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;
struct FGameplayTag;
struct FOnAttributeChangeData;


/**
 * @brief Structure representing a UI widget row.
 *
 * This row holds the data needed to display a message widget,
 * including a gameplay tag for matching, the text message, the widget class, 
 * and an optional image.
 */
USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	/** Tag used to identify the message type */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	/** Text message to display */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MessageText = FText();

	/** Widget class to use for displaying the message */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;

	/** Optional image to display with the message */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* MessageImage = nullptr;
};

/** 
 * @brief Delegate called when an attribute (e.g., health or mana) changes.
 *
 * @param NewValue The new value of the attribute.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSingnature, float, NewValue);

/** 
 * @brief Delegate called to broadcast a message widget row.
 *
 * @param Row The widget row data.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);


/**
 * @brief Widget controller responsible for updating overlay widgets.
 *
 * UOverlayWidgetController is derived from UAuraWidgetController and is used to broadcast
 * initial attribute values and bind callbacks for attribute changes (health, mana, etc.)
 * as well as for processing message widget data based on effect asset tags.
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	/**
	 * @brief Broadcasts the initial attribute values to the UI.
	 *
	 * Retrieves the current health, max health, mana, and max mana values from the 
	 * attribute set and broadcasts them via their respective delegates.
	 */
	virtual void BroadcastInitialValues() override;

	/**
	 * @brief Binds callbacks to gameplay attribute change delegates.
	 *
	 * This method sets up lambda callbacks to listen for changes in attributes such as health,
	 * max health, mana, and max mana. It also binds a lambda to handle effect asset tag events,
	 * allowing the UI to update message widgets dynamically.
	 */
	virtual void BindCallbacksToDependencies() override;

	/** Delegate triggered when the health attribute changes. */
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSingnature OnHealthChanged;

	/** Delegate triggered when the maximum health attribute changes. */
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSingnature OnMaxHealthChanged;

	/** Delegate triggered when the mana attribute changes. */
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSingnature OnManaChanged;

	/** Delegate triggered when the maximum mana attribute changes. */
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSingnature OnMaxManaChanged;

	/** Delegate triggered when a message widget row should be displayed. */
	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

protected:
	/** 
	 * @brief Data table containing UI widget row data.
	 *
	 * This data table is used to look up widget row entries based on gameplay tags.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;


	/**
	 * @brief Template helper function to retrieve a data table row by tag.
	 *
	 * @tparam T The expected row structure type.
	 * @param DataTable The data table to search.
	 * @param Tag The gameplay tag used to identify the row.
	 * @return Pointer to the row if found; nullptr otherwise.
	 */
	template <typename T>
	static T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
