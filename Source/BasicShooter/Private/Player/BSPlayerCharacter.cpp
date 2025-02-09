// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BSPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/BSMovementComponent.h"
#include "Components/BSWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABSPlayerCharacter::ABSPlayerCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
	CameraCollisionComponent->SetupAttachment(CameraComponent);
	CameraCollisionComponent->SetSphereRadius(10.0f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ABSPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}
void ABSPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckCameraOverlap();
}
void ABSPlayerCharacter::BeginPlay()
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData.MappingContext, 0);
		}
	}

	check(CameraComponent);
	check(CameraCollisionComponent);
	check(SpringArmComponent);

	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABSPlayerCharacter::OnCameraCollisionBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this,&ABSPlayerCharacter::OnCameraCollisionEndOverlap);
	
	Super::BeginPlay();
}
void ABSPlayerCharacter::OnDeath()
{
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	Super::OnDeath();
}

void ABSPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputData.MoveAction, ETriggerEvent::Triggered, this, &ABSPlayerCharacter::EnhancedInputMove);
		EnhancedInputComponent->BindAction(InputData.LookAround, ETriggerEvent::Triggered, this, &ABSPlayerCharacter::EnhancedInputLook);
		EnhancedInputComponent->BindAction(InputData.JumpAction, ETriggerEvent::Triggered, this, &ABSPlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(InputData.RunAction, ETriggerEvent::Started, this, &ABSPlayerCharacter::OnStartRun);
		EnhancedInputComponent->BindAction(InputData.RunAction, ETriggerEvent::Completed, this, &ABSPlayerCharacter::OnEndRun);
		EnhancedInputComponent->BindAction(InputData.FireAction, ETriggerEvent::Started, WeaponComponent, &UBSWeaponComponent::StartFire);
		EnhancedInputComponent->BindAction(InputData.FireAction, ETriggerEvent::Completed, WeaponComponent, &UBSWeaponComponent::StopFire);
		EnhancedInputComponent->BindAction(InputData.NextWeaponAction, ETriggerEvent::Triggered, WeaponComponent, &UBSWeaponComponent::NextWeapon);
		EnhancedInputComponent->BindAction(InputData.ReloadAction, ETriggerEvent::Triggered, WeaponComponent, &UBSWeaponComponent::Reload);
	}
}

void ABSPlayerCharacter::EnhancedInputMove(const FInputActionValue& Value)
{
	const FVector2d MovementVector = Value.Get<FVector2d>();

	if (GetController())
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}
void ABSPlayerCharacter::EnhancedInputLook(const FInputActionValue& Value)
{
	const FVector2d LookAxisVector = Value.Get<FVector2d>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void ABSPlayerCharacter::OnStartRun(const FInputActionValue& Value)
{
	WeaponComponent->StopFire();
	isRunningState = true;
}

void ABSPlayerCharacter::OnEndRun(const FInputActionValue& Value)
{
	isRunningState = false;
}
void ABSPlayerCharacter::CheckCameraOverlap() const
{
	const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
	GetMesh()->SetOwnerNoSee(HideMesh);

	TArray<USceneComponent*> MeshChildren;
	GetMesh()->GetChildrenComponents(true,MeshChildren);

	for(auto Child : MeshChildren)
	{
		const auto MeshChildrenGeometry = Cast<UPrimitiveComponent>(Child);
		if(!MeshChildrenGeometry)
		{
			continue;
		}
		MeshChildrenGeometry->SetOwnerNoSee(HideMesh);
	}
}

