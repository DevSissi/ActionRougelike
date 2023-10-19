// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROUGELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 设置该角色属性的默认值
	USAttributeComponent();
	
protected:
	// 最大血量
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Attributes")
	float MaxHealth;

	// 当前血量
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Attributes")
	float CurrentHealth;

public:
	// 改变血量
	UFUNCTION(BlueprintCallable,Category = "Attributes")
	bool ChangeHealth(float Delta);
		
};
