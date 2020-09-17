/**********************************************************************
 *  This file is part of intervalxt.
 *
 *        Copyright (C) 2019 Vincent Delecroix
 *        Copyright (C) 2019-2020 Julian Rüth
 *
 *  intervalxt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  intervalxt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with intervalxt. If not, see <https://www.gnu.org/licenses/>.
 *********************************************************************/

#ifndef LIBINTERVALXT_SAMPLE_ELEMENT_COEFFICIENTS_HPP
#define LIBINTERVALXT_SAMPLE_ELEMENT_COEFFICIENTS_HPP

#include <exact-real/element.hpp>

#include "coefficients.hpp"

namespace intervalxt::sample {

namespace {

template <typename Ring>
struct Coefficients<exactreal::Element<Ring>> {
  using T = exactreal::Element<Ring>;

  std::vector<std::vector<mpq_class>> operator()(const std::vector<T>& elements) {
    if (elements.size() == 0)
      return {};

    auto parent = elements[0].module();
    for (auto& x : elements)
      parent = span(parent, x.module());

    std::vector<std::vector<mpq_class>> ret;
    for (auto x : elements)
      ret.push_back(x.promote(parent).template coefficients<mpq_class>());

    return ret;
  }
};

}  // namespace

}  // namespace intervalxt::sample

#endif