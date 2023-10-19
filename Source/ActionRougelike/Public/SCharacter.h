// 在项目设置的描述页面中填写您的版权声明。

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USAttributeComponent;
class USInteractComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ACTIONROUGELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// 设置该角色属性的默认值
	ASCharacter();
	
protected:

	// 弹簧臂组件
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	// 摄像机组件
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	// 互动组件
	UPROPERTY(VisibleAnywhere)
	USInteractComponent* InteractComp;

	//属性组件
	UPROPERTY(VisibleAnywhere)
	USAttributeComponent* AttributeComp;

	// 生成的弹体类
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	// 主要攻击动画
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* PrimaryAttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;
	
	// 游戏开始或生成时调用
	virtual void BeginPlay() override;

	// 角色前后移动
	void MoveForward(float	Value);
	// 角色左右移动
	void MoveRight(float Value);
	// 角色主要攻击
	void PrimaryAttack();
	// 角色互动
	void DefaultInteract();
	// 角色主要攻击2
	void PrimaryAttack_Timeover();

public:	
	// 在每一帧调用
	virtual void Tick(float DeltaTime) override;
	
	// 调用将功能绑定到输入
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};