#pragma once
//Im Gui
#include "imgui.h"
#include "Application/UI/imgui_impl_glfw.h"
#include "Application/UI/imgui_impl_opengl3.h"


// Spdlog
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// OpenGL
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// STL
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <numeric>
#include <array>
#include <sstream>
#include <unordered_map>
#include <fstream>

// The Renderer
#include "Fundation/Log/Log.h"
#include "Core/OO/Semantics.h"
#include "Fundation/Ref/Ref.h"
#include "Fundation/Ref/Unique.h"
#include "Fundation/Type/Point.h"
#include "Fundation/Type/Rect.h"
#include "Fundation/Type/Point.h"
#include "Fundation/Type/Line.h"

// GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/constants.hpp"
#include "glm/gtx/quaternion.hpp"

// std
#include <cassert>

// stbimage
#include "stbimage.h"