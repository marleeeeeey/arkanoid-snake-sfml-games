#pragma once

// *************** STL ***************
#include <algorithm>
#include <cassert>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <numbers>
#include <optional>
#include <optional>
#include <random>
#include <set>
#include <sstream>
#include <utility>
#include <map>
#include <unordered_set>

// ************* 3rd party ************
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <imgui.h>
#include <magic_enum.hpp>
#include <nlohmann/json.hpp>
#include <fmt/format.h>
// ReSharper disable once CppInconsistentNaming
using json = nlohmann::json;

// ************* My Utils *************
#include <utils/GlmToSfmlOperators.h>
#include <utils/Config.h>
#include <utils/Direction.h>
#include <utils/JsonFormatter.h>
#include <utils/JsonLoader.h>
#include <utils/GeometryUtils.h>
#include <utils/Logger.h>
#include <utils/MathUtils.h>
#include <utils/StringUtils.h>
#include <utils/SystemUtils.h>
