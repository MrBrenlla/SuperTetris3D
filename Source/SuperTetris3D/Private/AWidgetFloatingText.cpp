// Fill out your copyright notice in the Description page of Project Settings.


#include "AWidgetFloatingText.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"

AWidgetFloatingText::AWidgetFloatingText()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create the WidgetComponent
    WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
    RootComponent = WidgetComp;

    // World-space widget
    WidgetComp->SetWidgetSpace(EWidgetSpace::World);
    WidgetComp->SetDrawSize(FVector2D(2000, 1000));
    WidgetComp->SetRelativeLocation(FVector(150, 0, 0));
    WidgetComp->SetPivot(FVector2D(0.5f, 0.5f));
    WidgetComp->SetRelativeRotation(FRotator(0, 0, 0));

    // Load widget blueprint
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetBP(TEXT("/Game/Blueprints/UI/W_FloatingText"));
    if (WidgetBP.Succeeded())
    {
        WidgetComp->SetWidgetClass(WidgetBP.Class);
        //UE_LOG(LogTemp, Warning, TEXT("FloatingText: Widget class loaded."));
    }
    else
    {
        //UE_LOG(LogTemp, Error, TEXT("FloatingText: Failed to load widget class."));
    }

    // Scale if needed
    WidgetComp->SetWorldScale3D(FVector(1, 1, 1));
}

void AWidgetFloatingText::SetText(FText text)
{
    if (UUserWidget* Widget = WidgetComp->GetUserWidgetObject())
    {
        if (UTextBlock* TextBlock = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("TextBlock"))))
        {
            TextBlock->SetText(text);
        }
    }
}

