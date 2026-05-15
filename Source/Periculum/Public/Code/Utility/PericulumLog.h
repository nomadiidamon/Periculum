#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(Periculum_Game, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Periculum_Audio, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Periculum_UI, Log, All);

DECLARE_LOG_CATEGORY_EXTERN(Periculum_Player, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Periculum_Input, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Periculum_AI, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Periculum_Combat, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(Periculum_Inventory, Log, All);


/// Generic logging macro that includes the function name.
#define PERICULUM_LOG(Category, Verbosity, Format, ...) \
    UE_LOG(Category, Verbosity, TEXT("[%s] " Format), TEXT(__FUNCTION__), ##__VA_ARGS__)



/// Category-specific logging macros that include the function name for convenience.

#define LOG_GAME(Verbosity, Format, ...) \
    PERICULUM_LOG(Periculum_Game, Verbosity, Format, ##__VA_ARGS__)

#define LOG_AUDIO(Verbosity, Format, ...) \
    PERICULUM_LOG(Periculum_Audio, Verbosity, Format, ##__VA_ARGS__)

#define LOG_UI(Verbosity, Format, ...) \
    PERICULUM_LOG(Periculum_UI, Verbosity, Format, ##__VA_ARGS__)

#define LOG_PLAYER(Verbosity, Format, ...) \
    PERICULUM_LOG(Periculum_Player, Verbosity, Format, ##__VA_ARGS__)

#define LOG_INPUT(Verbosity, Format, ...) \
    PERICULUM_LOG(Periculum_Input, Verbosity, Format, ##__VA_ARGS__)

#define LOG_AI(Verbosity, Format, ...) \
    PERICULUM_LOG(Periculum_AI, Verbosity, Format, ##__VA_ARGS__)

#define LOG_COMBAT(Verbosity, Format, ...) \
    PERICULUM_LOG(Periculum_Combat, Verbosity, Format, ##__VA_ARGS__)

#define LOG_INVENTORY(Verbosity, Format, ...) \
    PERICULUM_LOG(Periculum_Inventory, Verbosity, Format, ##__VA_ARGS__)


/// Actor-specific logging macros that include the actor's name for convenience.
#define LOG_ACTOR(Category, Verbosity, Actor, Format, ...) \
    UE_LOG((Category), (Verbosity), \
    TEXT("[%s] %s: " Format), \
    TEXT(__FUNCTION__), \
    *GetNameSafe((Actor)), \
    ##__VA_ARGS__)

/// Component-specific logging macros that include the component's name for convenience.
#define LOG_COMPONENT(Category, Verbosity, Component, Format, ...) \
    UE_LOG((Category), (Verbosity), \
    TEXT("[%s] %s.%s: " Format), \
    TEXT(__FUNCTION__), \
    *GetNameSafe(((Component) ? (Component)->GetOwner() : nullptr)), \
    *GetNameSafe((Component)), \
    ##__VA_ARGS__)