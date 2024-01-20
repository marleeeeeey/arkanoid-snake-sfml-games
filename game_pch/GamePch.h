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

// ************* 3rd party ************
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <magic_enum.hpp>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// ************* My Utils *************
#include <utils/GlmToSfmlOperators.h>
#include <utils/Config.h>
#include <utils/JsonFormatter.h>
#include <utils/GeometryUtils.h>
#include <utils/Logger.h>
#include <utils/MathUtils.h>
#include <utils/StringUtils.h>
#include <utils/SystemUtils.h>
