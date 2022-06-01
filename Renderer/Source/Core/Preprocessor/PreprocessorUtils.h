#pragma once

#define STRINGIFY_HELPER(x) #x
#define STRINGIFY(x)   STRINGIFY_HELPER(x)

#define CONCAT_IMPL(x, y)  x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)
