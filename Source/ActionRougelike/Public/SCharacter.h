// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ACTIONROUGELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	// 弹簧臂组件
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	// 摄像机组件
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 角色前后移动
	void MoveForward(float	Value);
	// 角色左右移动
	void MoveRight(float Value);
	// 角色主要攻击
	void PrimaryAttack();

	// 生成的弹体类
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};