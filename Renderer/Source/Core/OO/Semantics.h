#pragma once

#define NO_COPY(className)                                                  \
public:                                                                     \
    className(const className& other) = delete;                             \
    const className& operator=(const className& other) = delete;

#define NO_MOVE(className)                                                  \
public:                                                                     \
    className(const className&& other) = delete;                            \
    const className& operator=(const className&& other) = delete;

#define SELF(className) using Self = className

#define SUPER(className) using Super = className

#define GENERATE_BODY(selfClass, parentClass)    \
    SELF(selfClass);                             \
    SUPER(parentClass)                           \


#define FORWARD_DECL(className) class className

#define UNUSED(x) (void)(x)