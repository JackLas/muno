// Copyright (c) 2025 Yevhenii Kryvyi
// SPDX-License-Identifier: MIT

#ifndef SRC_RESOURCES_INCLUDE_RESOURCES_HPP
#define SRC_RESOURCES_INCLUDE_RESOURCES_HPP

#include "SFML/System/InputStream.hpp"

namespace muno
{

class Resources final
{
public:
    Resources() = default;

    sf::InputStream& font() const;
};

} // namespace muno

#endif // SRC_RESOURCES_INCLUDE_RESOURCES_HPP
