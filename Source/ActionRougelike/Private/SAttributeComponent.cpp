// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// 设置该角色属性的默认值
USAttributeComponent::USAttributeComponent()
{
	CurrentHealth = MaxHealth;
}


bool USAttributeComponent::ChangeHealth(float Delta)
{
	CurrentHealth += Delta;
	
	return true;
}
