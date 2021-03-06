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

#ifndef LIBINTERVALXT_SAMPLE_LENGTHS_HPP
#define LIBINTERVALXT_SAMPLE_LENGTHS_HPP

#include <gmpxx.h>

#include <tuple>
#include <unordered_set>
#include <vector>

#include "../label.hpp"
#include "../lengths.hpp"
#include "coefficients.hpp"
#include "floor_division.hpp"

namespace intervalxt::sample {

namespace {

template <typename T, typename FloorDivision = FloorDivision<T>, typename Coefficients = Coefficients<T>>
class Lengths : public Serializable<Lengths<T>> {
 public:
  Lengths();
  explicit Lengths(const std::vector<T>&);

  template <typename... L>
  static auto make(L&&... values);

  std::vector<Label> labels() const;

  operator T() const;
  explicit operator bool() const;

  void push(Label);
  void pop();
  void clear();
  int cmp(Label) const;
  int cmp(Label, Label) const;
  void subtract(Label);
  Label subtractRepeated(Label);
  std::vector<std::vector<mpq_class>> coefficients(const std::vector<Label>&) const;
  std::string render(Label) const;
  T get(Label) const;
  ::intervalxt::Lengths only(const std::unordered_set<Label>&) const;
  ::intervalxt::Lengths forget() const;
  bool similar(Label, Label, const ::intervalxt::Lengths&, Label, Label) const;

  bool operator==(const Lengths&) const;

 private:
  T& at(Label);
  const T& at(Label) const;

  friend Serialization<Lengths<T>>;

  std::vector<Label> stack;
  std::vector<T> lengths;
};

template <typename T>
Lengths(const std::vector<T>&) -> Lengths<T>;

}  // namespace

}  // namespace intervalxt::sample

#include "detail/lengths.ipp"

#endif
