// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveActor.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONROUGELIKE_API ASExplosiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosiveActor();

protected:
	
	// 静态网格体组件
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComp;
	
	// 径向力组件
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	URadialForceComponent* RadialForceComp;

	//爆炸伤害
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float Damage;
	

	// 实例初始化函数，在游戏初始化和Pawn生成后调用
	virtual void PostInitializeComponents() override;
	
	// 被击反应函数，当该 Actor 被另一个组件击中时调用
	UFUNCTION(BlueprintCallable)
	void OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};