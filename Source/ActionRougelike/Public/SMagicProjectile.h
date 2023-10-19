// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROUGELIKE_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:

	// 球体组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	// 弹丸运动组件
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	// 粒子系统组件
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;


	// 伤害数值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage;	
};