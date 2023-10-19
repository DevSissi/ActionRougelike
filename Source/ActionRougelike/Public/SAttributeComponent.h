// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

// 为组件创建一个 当生命值改变时 的触发事件
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnChangeHealth, AActor*, InstigatorActor, USAttributeComponent*, AffectComp, float, CurrentHealth, float, MaxHealth, float, Delta);

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
	bool isChangeHealth(float Delta);

	// BlueprintAssignable 仅可与多播代表一起使用。公开用于在蓝图中分配的属性。
	UPROPERTY(BlueprintAssignable)
	FOnChangeHealth OnChangeHealth;
		
};
