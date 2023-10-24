// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// 设置该角色属性的默认值
USAttributeComponent::USAttributeComponent()
{
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}


bool USAttributeComponent::isChangeHealth(float Delta)
{
	CurrentHealth += Delta;

	OnChangeHealth.Broadcast(nullptr, this, CurrentHealth, MaxHealth, Delta);
	
	return true;
}

// bool USAttributeComponent::isChangeHealth(UMeshComponent* MeshComp, float Delta)
// {
// 	CurrentHealth += Delta;
//
// 	OnChangeHealth.Broadcast(nullptr, this, CurrentHealth, MaxHealth, Delta);
//
// 	if (Delta > 0.f)
// 	{
// 		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds());
// 	}
// 	
// 	return true;
// }
