// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SAttributeComponent.h"
#include "SInteractComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/BlueprintTypeConversions.h"


// Sets default values
ASCharacter::ASCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建弹簧臂组件
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	//使用Pawn的旋转控制
	SpringArmComp->bUsePawnControlRotation = true;
	//将弹簧臂组件绑定到根组件
	SpringArmComp->SetupAttachment(RootComponent);
	
	// 创建相机组件
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CamaraComp");
	//将相机组件绑定到弹簧臂组件
	CameraComp->SetupAttachment(SpringArmComp);

	// 将角色朝向向加速度方向旋转，用RotationRate作为旋转改变速率
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	//创建增强输入系统组件
	//EnhancedInputComponent = CreateDefaultSubobject<UEnhancedInputComponent>("EISComp");

	//创建交互组件
	InteractComp = CreateDefaultSubobject<USInteractComponent>("InteractComp");

	//创建属性组件
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// 调用将运动功能绑定到用户输入
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// 调用父类的SetupPlayerInputComponent函数
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 检查输入组件是否有效
	check(PlayerInputComponent);

	// 获取玩家控制器
	if (APlayerController* PlayerController = CastChecked<APlayerController>(GetController()))
	{
		// 获取本地玩家的输入子系统
		if (UEnhancedInputLocalPlayerSubsystem* Subsytem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// 添加映射上下文
			Subsytem->AddMappingContext(IMC_Action,0);
			Subsytem->AddMappingContext(IMC_MoveBase,0);
		}
	}

	// 检查输入组件是否有效
	if (UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 检查输入动作是否有效
		if (IA_LookUp)
		{
			// 设置输入动作的值类型
			IA_LookUp->ValueType = EInputActionValueType::Axis1D;
			// 绑定 上下转向
			EIC->BindAction(IA_LookUp, ETriggerEvent::Triggered, this, &ASCharacter::LookUp);
		}
		if (IA_Turn)
		{
			IA_Turn->ValueType = EInputActionValueType::Axis1D;
			// 绑定 左右转向
			EIC->BindAction(IA_Turn,ETriggerEvent::Triggered,this,&ASCharacter::Turn);
		}
		if (IA_MoveForward)
		{
			IA_MoveForward->ValueType = EInputActionValueType::Axis1D;
			// 绑定 前后移动
			EIC->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &ASCharacter::MoveForward);
		}
		if (IA_MoveRight)
		{
			IA_MoveRight->ValueType = EInputActionValueType::Axis1D;
			// 绑定 左右移动
			EIC->BindAction(IA_MoveRight,ETriggerEvent::Triggered,this,&ASCharacter::MoveRight);
		}
		if (IA_Jump)
		{
			// 绑定 跳跃
			EIC->BindAction(IA_Jump,ETriggerEvent::Started,this,&ASCharacter::Jump);
		}
		if (IA_PrimaryAttack)
		{
			// 绑定 主要攻击
			EIC->BindAction(IA_PrimaryAttack,ETriggerEvent::Triggered,this,&ASCharacter::PrimaryAttack);
		}
		if (IA_DefaultInteract)
		{
			// 绑定 默认交互
			EIC->BindAction(IA_DefaultInteract,ETriggerEvent::Triggered,this,&ASCharacter::DefaultInteract);
		}
	}

	/* 旧版输入绑定系统
	// 将角色移动绑定到轴输入
	//PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	
	// 将角色旋转绑定到轴输入
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this, &APawn::AddControllerPitchInput);

	// 将角色的攻击绑定到动作输入
	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&ASCharacter::PrimaryAttack);
	
	// 将角色的跳跃绑定到动作输入
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//将角色的互动绑定到动作输入
	PlayerInputComponent->BindAction("DefaultInteract", IE_Pressed, this, &ASCharacter::DefaultInteract);
	*/
	
}


// 运动函数
// 上下转向实现
void ASCharacter::LookUp(const FInputActionValue& InputActionValue)
{
	APawn::AddControllerPitchInput(InputActionValue.GetMagnitude());
}

// 左右转向实现
void ASCharacter::Turn(const FInputActionValue& InputActionValue)
{
	APawn::AddControllerYawInput(InputActionValue.GetMagnitude());
}

// 前后移动实现
void ASCharacter::MoveForward(const FInputActionValue& InputActionValue)
{
	// 获取控制器当前的朝向（获取旋转，将除Yaw之外的角度设置为0）
	FRotator RotatorRotation = GetControlRotation();
	RotatorRotation.Pitch = 0.0f;
	RotatorRotation.Roll = 0.0f;
	
	// 将朝向设置为角色运动方向
	AddMovementInput(RotatorRotation.Vector(),InputActionValue.GetMagnitude());
}

// 左右移动实现
void ASCharacter::MoveRight(const FInputActionValue& InputActionValue)
{
	// 获取控制器当前的朝向（获取旋转，将除Yaw之外的角度设置为0）
	FRotator RotatorRotation = GetControlRotation();
	RotatorRotation.Pitch = 0.0f;
	RotatorRotation.Roll = 0.0f;
	
	 // x = 前方		红色
	 // y = 右方		绿色
	 // z = 上方		蓝色
	
	// 将Y轴朝向转换为方向向量
	FVector RightVector = FRotationMatrix(RotatorRotation).GetScaledAxis(EAxis::Y);
	
	// 将角色运动方向设置为方向向量（Y轴朝向）
	AddMovementInput(RightVector, InputActionValue.GetMagnitude());
}

// 主要攻击实现1：播放攻击动画，在攻击动画完成时再生成攻击弹体
void ASCharacter::PrimaryAttack()
{
	// 播放主要攻击动画
	PlayAnimMontage(PrimaryAttackAnim);
	// 设置计时器，延时攻击弹体生成以匹配攻击动画
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,this,&ASCharacter::PrimaryAttack_Timeover,0.25f);

	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

// 主要攻击实现2：生成攻击弹体
void ASCharacter::PrimaryAttack_Timeover()
{
	// 调用角色生成弹体的函数实现攻击
	SpawnProjectile(ProjectileClass);
}

// 生成弹体函数
void ASCharacter::SpawnProjectile(TSubclassOf<AActor> SpawnProjectileClass)
{
	if (ensureAlways(SpawnProjectileClass))
	{
		// 获取角色的发射粒子对应的骨骼位置
		FVector ProjectileSpawnLoc = GetMesh()->GetSocketLocation("Muzzle_01");
		
		// 射线检测获取视角（摄像机）前方对象
		// 创建一个 碰撞查询参数，用于特定的参数设置
		FCollisionQueryParams QueryParams;
		// 检测时忽略自身
		QueryParams.AddIgnoredActor(this);
		
		// 创建一个碰撞对象查询参数，用于检测可检测的对象
		FCollisionObjectQueryParams ObjQueryParams;
		ObjQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjQueryParams.AddObjectTypesToQuery(ECC_Pawn);
		ObjQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
		
		// 射线检测距离
		float QueryDistance = 1e+4;
		// 射线检测半径
		FCollisionShape Shape;
		Shape.SetSphere(1);
		// 射线检测起点
		FVector LineTracingStartLoc = CameraComp->GetComponentLocation();
		// 射线检测终点
		FVector LineTracingEndLoc = LineTracingStartLoc + CameraComp->GetForwardVector() * QueryDistance;
		
		FHitResult HitResult;
		
		// 射线检测
		if(GetWorld()->SweepSingleByObjectType(HitResult,LineTracingStartLoc,LineTracingEndLoc,FQuat::Identity,ObjQueryParams,Shape,QueryParams))
		{
			LineTracingEndLoc = HitResult.ImpactPoint;
		}

		// 绘制调试 sphere
		// bool bIsHit = GetWorld()->SweepSingleByObjectType(HitResult,LineTracingStartLoc,LineTracingEndLoc,FQuat::Identity,ObjQueryParams,Shape,QueryParams);
		// FColor DebugColor = bIsHit ? FColor::Green : FColor::Red;
		// DrawDebugSphere(GetWorld(),LineTracingEndLoc,1,16,DebugColor,false,2.f);
		

		// 计算视觉中心与弹体发射之间的向量差
		FVector ProjectileLoc = LineTracingEndLoc - ProjectileSpawnLoc;
		FRotator  ProjectileRot = ProjectileLoc.Rotation();
		
		// 将弹体生成位置设置为武器位置,方向为摄像机朝向
		FTransform SpawnTrans = FTransform(ProjectileRot, ProjectileSpawnLoc);
	
		// 设定生成参数，即使碰撞也始终生成
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		// 将粒子的触发者（触发器）设置为玩家角色（发射者）
		SpawnParams.Instigator = this;

		// 在武器位置生成弹体
		GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTrans,SpawnParams);
	}
}

// 默认交互实现
void ASCharacter::DefaultInteract()
{
	// 调用默认交互函数
	InteractComp->DefaultInteract();
}
