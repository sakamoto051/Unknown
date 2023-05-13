#include "PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "DoorPlatform.h"
#include "Core/Public/Misc/OutputDeviceNull.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Blueprint/UserWidget.h"
#include "GamePlayerState.h"
#include "PaintingPlatform.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/HUD.h"



APlayerCharacter::APlayerCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FootstepAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FootstepAudioComponent"));
	FootstepAudioComponent->bAutoActivate = false;
	FootstepAudioComponent->SetupAttachment(RootComponent);
	FootstepAudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}

void APlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerCharacter::SoundFootStep();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &APlayerCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &APlayerCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ToggleCrouched);
	PlayerInputComponent->BindAction(TEXT("ToggleMenu"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ToggleMenu);
}

void APlayerCharacter::Interact()
{
	// カメラの位置と向きを格納するための変数
	FVector Location;
	FRotator Rotation;
	// Characterクラスのポインタを取得
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (Character == nullptr) {
    	UE_LOG(LogTemp, Warning, TEXT("Character == nulptr"));
		return;
	}
	// カメラの位置と向きを取得
	Character->GetActorEyesViewPoint(Location, Rotation);

	FHitResult Hit;
	FVector ShotDirection;
	ShotDirection = -Rotation.Vector();
	FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel2, Params);
	if (bSuccess) {
		AActor *HitActor = Hit.GetActor();
		if (HitActor->GetClass()->FindFunctionByName(TEXT("Interact"))) {
			FOutputDeviceNull ar;
			HitActor->CallFunctionByNameWithArguments(TEXT("Interact"), ar, nullptr, true);
		}

		AGamePlayerState* MyPlayerState = Cast<AGamePlayerState>(GetPlayerState());
        if (MyPlayerState) {
			MyPlayerState->SetFlg(HitActor->GetName());
        }
	}
}

void APlayerCharacter::ToggleCrouched()
{
    if (IsCrouched) {
        UnCrouch();
		IsCrouched = false;
    } else {
        Crouch();
		IsCrouched = true;
    }
}

void APlayerCharacter::ClearInputBind()
{
	// APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	// PlayerController->bShowMouseCursor = true;

	InputComponent = FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
		InputComponent->ClearActionBindings();
		InputComponent->ClearAxisBindings();
    }
}

void APlayerCharacter::SetInputBind()
{
	// APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	// PlayerController->bShowMouseCursor = false;

	InputComponent = FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
		InputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
		InputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
		InputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
		InputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
		InputComponent->BindAxis(TEXT("LookUpRate"), this, &APlayerCharacter::LookUpRate);
		InputComponent->BindAxis(TEXT("LookRightRate"), this, &APlayerCharacter::LookRightRate);
		InputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Interact);
		InputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ToggleCrouched);
		InputComponent->BindAction(TEXT("ToggleMenu"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ToggleMenu);
    }
}

void APlayerCharacter::SetMenuInputBind()
{
	InputComponent = FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
		InputComponent->BindAction(TEXT("ToggleMenu"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ToggleMenu);
    }
}

void APlayerCharacter::ActivateCursor()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = true;
	
}
void APlayerCharacter::DeActivateCursor()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = false;
	
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue * 100);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::SoundFootStep()
{
	if (FootstepAudioComponent != nullptr && FootstepSoundCue != nullptr) {
		const float VelocityMagnitude = GetVelocity().Size();
		const bool bIsMoving = VelocityMagnitude > 0.0f;

		if (bIsMoving && !FootstepAudioComponent->IsPlaying()) {
			FootstepAudioComponent->SetSound(FootstepSoundCue);
			FootstepAudioComponent->Play();
		} else if (!bIsMoving && FootstepAudioComponent->IsPlaying()) {
			FootstepAudioComponent->Stop();
		}
	}
}

void APlayerCharacter::ToggleMenu()
{
	if (IsOpenMenu) {
		UE_LOG(LogTemp, Display, TEXT("close"));
		DeActivateCursor();
		RemoveMenuWidget();
		ClearInputBind();
		SetInputBind();
		IsOpenMenu = false;
	} else {
		UE_LOG(LogTemp, Display, TEXT("open"));
		ActivateCursor();
		SetMenuWidget();
		ClearInputBind();
		SetMenuInputBind();
		IsOpenMenu = true;
	}
}

void APlayerCharacter::SetTitleWidget()
{
    UUserWidget* TitleScreen = CreateWidget<UUserWidget>(GetWorld(), TitleWidget);
    if (TitleScreen != nullptr) {
        TitleScreen->AddToViewport();
    }
}

void APlayerCharacter::SetClearWidget()
{
    UUserWidget* ClearScreen = CreateWidget<UUserWidget>(GetWorld(), ClearWidget);
    if (ClearScreen != nullptr) {
        ClearScreen->AddToViewport();
    }
}

void APlayerCharacter::SetMenuWidget()
{
    UUserWidget* MenuScreen = CreateWidget<UUserWidget>(GetWorld(), MenuWidget);
    if (MenuScreen != nullptr) {
        MenuScreen->AddToViewport();
    }
}

void APlayerCharacter::RemoveMenuWidget()
{
    TArray<UUserWidget*> WidgetsToRemove;
    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), WidgetsToRemove, MenuWidget);
    for (UUserWidget* Widget : WidgetsToRemove) {
        Widget->RemoveFromParent();
        Widget->Destruct();
    }
}

