// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC.h"

#include"Components/SphereComponent.h"
#include"Components/BoxComponent.h"
#include"Characters/SlashCharacter.h"
#include"Components/WidgetComponent.h "
#include"Blueprint/UserWidget.h"
//#include"Components/ShopSystemComponent.h"
#include"Components/WidgetComponent.h "

ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
	Sphere->SetSphereRadius(400.f);

	//NPC名字
	NameWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Name"));
	NameWidget->SetupAttachment(GetRootComponent());
	NameWidget->SetWidgetSpace(EWidgetSpace::Screen);
	NameWidget->SetVisibility(false);

	//创建商店组件
	//ShopSystem = CreateDefaultSubobject<UShopSystemComponent>(TEXT("Shop"));
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
	Tags.Add(FName("ShopNPC"));
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnSphereEndOverlap);
}

void ANPC::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("get shop")));

	ASlashCharacter* Character = Cast<ASlashCharacter>(OtherActor);
	if (Character)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Character: %s"), *Character->GetName()));
		Character->SetOverlappingShop(this);

		if (NameWidget)
		{
			NameWidget->SetVisibility(true);
		}
	}
}

void ANPC::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("leave shop")));
	ASlashCharacter* Character = Cast<ASlashCharacter>(OtherActor);
	if (Character)
	{
		GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Green, FString::Printf(TEXT("Character: %s"), *Character->GetName()));
		Character->SetOverlappingShop(nullptr);

		if (NameWidget)
		{
			NameWidget->SetVisibility(false);
		}
	}
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::OpenStoreUI()
{
	/*if (ShopSystem)
	{
		ShopSystem->OpenShop();
	}*/
}

