#pragma once

#include <string_view>

class Season {
public:
  static const Season &Spring;
  static const Season &Summer;
  static const Season &Autumn;
  static const Season &Winter;

  static const Season _values[];

private:
  unsigned _ordinal;

  Season() : Season(0) {}

  constexpr explicit Season(int ordinal) : _ordinal(ordinal) {}

  constexpr operator int() const { return _ordinal; }

public:
  static constexpr int size() { return 4; }

  std::string_view name() const {
    switch (_ordinal) {
    case 0:
      return "Spring";
    case 1:
      return "Summer";
    case 2:
      return "Autumn";
    case 3:
      return "Winter";
    default:
      return "invalid";
    }
  }

  unsigned index() const { return _ordinal; }

  const Season &next() const { 
    return values()[(index() + 1) % size()];
  }

  static const Season &get(int i) { return values()[i]; }

  static const Season *const values() {
    return _values;
  }
};

const Season Season::_values[] = {Season(0), Season(1), Season(2), Season(3)};
const Season &Season::Spring = Season::_values[0];
const Season &Season::Summer = Season::_values[1];
const Season &Season::Autumn = Season::_values[2];
const Season &Season::Winter = Season::_values[3];
