#include "AFloatingScore.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"

AFloatingScore::AFloatingScore()
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
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetBP(TEXT("/Game/Blueprints/UI/W_FloatingNumber"));
    if (WidgetBP.Succeeded())
    {
        WidgetComp->SetWidgetClass(WidgetBP.Class);
        //UE_LOG(LogTemp, Warning, TEXT("FloatingScore: Widget class loaded."));
    }
    else
    {
        //UE_LOG(LogTemp, Error, TEXT("FloatingScore: Failed to load widget class."));
    }

    // Scale if needed
    WidgetComp->SetWorldScale3D(FVector(1, 1, 1));
}

void AFloatingScore::SetScore(int Score)
{
    if (UUserWidget* Widget = WidgetComp->GetUserWidgetObject())
    {
        if (UTextBlock* TextBlock = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("TextBlock"))))
        {
            TextBlock->SetText(FText::AsNumber(Score));
        }
    }

    // Auto destroy after 1 second
    SetLifeSpan(0.8f);
}

void AFloatingScore::SetMultiplier(int mult)
{

    WidgetComp->SetRelativeRotation(FRotator(-30, 0, 0));

    if (UUserWidget* Widget = WidgetComp->GetUserWidgetObject())
    {
        if (UTextBlock* TextBlock = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("TextBlock"))))
        {
            TextBlock->SetText(FText::Format(FText::FromString("x{0}"), mult));
        }
    }

    // Auto destroy after 1 second
    SetLifeSpan(0.8f);
}

void AFloatingScore::SetColor(FColor color)
{
    if (UUserWidget* Widget = WidgetComp->GetUserWidgetObject())
    {
        if (UTextBlock* TextBlock = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("TextBlock"))))
        {
            FSlateColor slateColor = FSlateColor(FLinearColor(color));
            TextBlock->SetColorAndOpacity(slateColor);
        }
    }
}