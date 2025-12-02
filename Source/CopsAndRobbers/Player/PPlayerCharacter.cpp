#include "Player/PPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"

APPlayerCharacter::APPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	GetCapsuleComponent()->SetupAttachment(GetRootComponent());
	GetMesh()->SetupAttachment(GetCapsuleComponent());
	GetArrowComponent()->SetupAttachment(GetCapsuleComponent());

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	// Components Transform ---------------
	// FRotator : pitch / yaw / roll
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));

	// Camera Move ------------------------
	bUseControllerRotationPitch = false;	// 카메라와 캐릭터의 회전은 분리
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;	// 캐릭터가 이동하는 방향으로 mesh 회전
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);	// yaw 회전 가속도
	
	SpringArmComponent->bUsePawnControlRotation = true;	// Pawn의 Controller의 제어를 따름
	CameraComponent->bUsePawnControlRotation = false;		// SpringArm이 회전하므로 Camera 회전은 비활성화
	// Walk Speed -------------------------
	StandingWalkSpeed = 300.0f;
	SprintSpeedScale = 2.0f;
	GetCharacterMovement()->MaxWalkSpeed = StandingWalkSpeed;
	// ------------------------------------
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned; // AI 자동 빙의
}

void APPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = StandingWalkSpeed;
}

void APPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

