#pragma once

#include "CoreMinimal.h"
#include "WeaponType.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    None        UMETA(DisplayName = "None"),
    Pistol      UMETA(DisplayName = "Pistol"),
    Rifle       UMETA(DisplayName = "Rifle"),
    Shotgun     UMETA(DisplayName = "Shotgun"),
    Lighter  UMETA(DisplayName = "Lighter"),
    Axe   UMETA(DisplayName = "Axe"),
    Molotov UMETA(DisplayName="Molotov")
};

