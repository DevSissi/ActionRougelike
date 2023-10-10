// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SGameplayInterface.generated.h"

// This class does not need to be modified.
//这个类不需要修改。
UINTERFACE(MinimalAPI)
class USGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONROUGELIKE_API ISGameplayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	// 在该类中添加接口函数。这是将被继承以实现该接口的类。
public:
	//接口函数：互动 --传入Pawn而非Character扩大可与之交互的对象范围
	//使用纯虚函数是因为对象互动的方式不同，所以需要不同的实现
	UFUNCTION(BlueprintNativeEvent)
	virtual void Interact(APawn*  InstigatorPawn) = 0;
};
