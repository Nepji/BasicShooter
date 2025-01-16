// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BSBaseCharacter.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BSMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, Log, Warning)

ABSBaseCharacter::ABSBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UBSMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SocketOffset = FVector(0.0f,100.0f,80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	
	HealthComponent = CreateDefaultSubobject<UBSHealthComponent>("HealthComponent");

	HealthTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextRenderComponent->SetupAttachment(GetRootComponent());
	HealthTextRenderComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<UBSWeaponComponent>("WeaponComponent");
}
bool ABSBaseCharacter::IsRunning()
{
	return isRunningState;
}

const float ABSBaseCharacter::GetDirection()
{
	if(GetVelocity().IsZero())
	{
		return 0.0f;
	}
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const float AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(),VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(),VelocityNormal);
	const float Degrees = FMath::RadiansToDegrees(AngleBetween);

	
	return CrossProduct.IsZero()?Degrees:Degrees * FMath::Sign(CrossProduct.Z);
}

void ABSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData.MappingContext, 0);
		}
	}



	OnHealthChange(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this,&ABSBaseCharacter::OnDeath);
	HealthComponent->OnHealthChange.AddUObject(this,&ABSBaseCharacter::OnHealthChange);


	
}

void ABSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(HealthComponent);
	check(HealthTextRenderComponent);
	check(WeaponComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputData.MoveAction, ETriggerEvent::Triggered, this, &ABSBaseCharacter::EnhancedInputMove);
		EnhancedInputComponent->BindAction(InputData.LookAround,ETriggerEvent::Triggered,this,&ABSBaseCharacter::EnhancedInputLook);
		EnhancedInputComponent->BindAction(InputData.JumpAction,ETriggerEvent::Triggered,this,&ABSBaseCharacter::Jump);
		EnhancedInputComponent->BindAction(InputData.RunAction,ETriggerEvent::Started,this,&ABSBaseCharacter::OnStartRun);
		EnhancedInputComponent->BindAction(InputData.RunAction,ETriggerEvent::Completed,this,&ABSBaseCharacter::OnEndRun);
		EnhancedInputComponent->BindAction(InputData.FireAction,ETriggerEvent::Started,WeaponComponent,&UBSWeaponComponent::StartFire);
		EnhancedInputComponent->BindAction(InputData.FireAction,ETriggerEvent::Completed,WeaponComponent,&UBSWeaponComponent::StopFire);
	}
}
void ABSBaseCharacter::EnhancedInputMove(const FInputActionValue& Value)
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

	UE_LOG(LogBaseCharacter, Log, TEXT("Movement %0.f, %0.f"), MovementVector.X, MovementVector.Y)
}
void ABSBaseCharacter::EnhancedInputLook(const FInputActionValue& Value)
{
	const FVector2d LookAxisVector = Value.Get<FVector2d>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}
void ABSBaseCharacter::OnStartRun(const FInputActionValue& Value)
{
	isRunningState = true;
}

void ABSBaseCharacter::OnEndRun(const FInputActionValue& Value)
{
	isRunningState = false;
}

void ABSBaseCharacter::OnDeath()
{
	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(ToDeathTimer);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}

	
}
void ABSBaseCharacter::OnHealthChange(float Health)
{
	HealthTextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}



