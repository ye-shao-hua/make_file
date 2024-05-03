#pragma once

#include <compare>
#include <memory>
#include <ranges>

template <typename Type>
concept IsPointType =
    std::ranges::range<Type> && std::regular<Type> &&
    requires(Type point, const Type const_point, std::istream is) {
      typename Type::number_t;
      typename Type::iterator_t;
      typename Type::const_iterator_t;
      { Type::dim() } -> std::same_as<std::size_t>;
      { Type{} } -> std::same_as<Type>;
      { Type{*(new Type{})} } -> std::same_as<Type>;
      { Type{Type{}} } -> std::same_as<Type>;
      { Type{1, 1.2, 3, 4, 5, 6, 7, 8, 9} } -> std::same_as<Type>;
      { point = const_point } -> std::same_as<Type &>;
      { point = std::move(point) } -> std::same_as<Type &>;
      point.~Type();
      { const_point + const_point } -> std::same_as<Type>;
      { point += const_point } -> std::same_as<Type &>;
      { const_point.copy() } -> std::same_as<Type>;
      { const_point.copy_ptr() } -> std::same_as<Type *>;
      { const_point < const_point } -> std::same_as<bool>;
      { const_point == const_point } -> std::same_as<bool>;
      { const_point <=> const_point } -> std::same_as<std::partial_ordering>;
      {
        const_point.template norm<std::size_t{1}>(),
            const_point.template norm<std::size_t{2}>(),
            const_point.template norm<std::size_t{3}>(),
            const_point.template norm<std::size_t{4}>(),
            const_point.template norm<std::size_t{5}>(),
            const_point.template norm<std::size_t{6}>(),
            const_point.template norm<std::size_t{7}>(),
            const_point.template norm<std::size_t{8}>(),
            const_point.template norm<std::size_t{9}>(),
            const_point.template norm<std::size_t{10}>(),
            const_point.template norm<std::size_t{11}>()
      } -> std::same_as<typename Type::number_t>;
      { point.show() } -> std::same_as<void>;
      { is >> point } -> std::same_as<std::istream &>;
      { point.begin() } -> std::same_as<typename Type::iterator_t>;
      { point.end() } -> std::same_as<typename Type::iterator_t>;
      { const_point.begin() } -> std::same_as<typename Type::const_iterator_t>;
      { const_point.end() } -> std::same_as<typename Type::const_iterator_t>;
      {
        point.data()
      } -> std::same_as<std::array<typename Type::number_t, Type::dim()> &>;
    };

template <typename Type>
concept IsValuePointType = IsPointType<Type> && requires(
                                                    Type value_point,
                                                    const Type
                                                        const_value_point) {
  typename Type::value_t;
  typename Type::point_t;
  { Type{std::make_unique<typename Type::point_t{}>()} } -> std::same_as<Type>;
  {
    Type{std::make_unique<typename Type::point_t{}>(), typename Type::value_t{}}
  } -> std::same_as<Type>;
  { value_point.set_value(typename Type::value_t{}) } -> std::same_as<void>;
  { const_value_point.value() } -> std::same_as<typename Type::value_t>;
};
