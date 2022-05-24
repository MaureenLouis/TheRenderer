#pragma once
#include "Core/OO/Semantics.h"

#define GENERATE_SINGLETON(className)                                       \
public:                                                                     \
    static className& get()                                                 \
    {                                                                       \
        static className singleton;                                         \
        return singleton;                                                   \
    }                                                                       \
    NO_COPY(className)                                                      \
    NO_MOVE(className)                                                      \
public:

