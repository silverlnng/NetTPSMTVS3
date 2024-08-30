﻿// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "NetTPSMTVSCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter , Log , All);

UCLASS(config = Game)
class ANetTPSMTVSCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = Camera , meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = Camera , meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true"))
	UInputAction* GrabPistolAction;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

public:
	ANetTPSMTVSCharacter();


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void GrabPistol(const FInputActionValue& Value);

	void FirePistol(const FInputActionValue& Value);


	void MyTakePistol();
	void MyReleasePistol();



protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite)
	bool bHasPistol;

	// 태어날 때 모든 총 목록을 기억하고싶다.
	UPROPERTY()
	TArray<AActor*> PistolList;

	// 총을 잡았을 때 위치
	UPROPERTY(EditDefaultsOnly , Category = Pistol)
	class USceneComponent* HandComp;

	// 소유한 총을 기억하고싶다.
	UPROPERTY()
	class AActor* GrabPistolActor;

	UPROPERTY(EditDefaultsOnly , Category = Pistol)
	float GrabDistance = 300;

	void AttachPistol(AActor* pistolActor);

	void DetachPistol();


	// 만약 마우스 왼쪽 버튼을 누르면 총을쏘고싶다.
	// 부딪힌곳에 총알자국을 표현하고싶다.
	UPROPERTY(EditDefaultsOnly , Category = Pistol)
	class UParticleSystem* BulletImpactVFX;

	// MainWidget을 생성해서 기억하고싶다.
	 UPROPERTY(EditDefaultsOnly , Category = Pistol)
	 TSubclassOf<class UUserWidget> MainUIFactory;

	 UPROPERTY()
	 class UMainWidget* MainUI;

	 void InitMainUI();

	 UPROPERTY(EditDefaultsOnly , Category = Pistol)
	 int32 MaxBulletCount = 10;

	 int32 BulletCount = MaxBulletCount;
};

