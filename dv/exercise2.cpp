#include <cstdint>
#include <bit>
#include <catch2/catch_test_macros.hpp>

#include <VExercise2.h>

using namespace std;

void step(VExercise2& model) {
  model.clk = 1;
  model.eval();
  model.clk = 0;
  model.eval();
}

TEST_CASE("Exercise 2 Test Reset") {
  VExercise2 model;
  model.reset = 1;
  model.init = 0;
  step(model);
  uint16_t result = ~0;
  REQUIRE(model.out == result);

  step(model);
  step(model);
  step(model);
  step(model);
  REQUIRE(model.out == result);

  model.init = 10;
  result = ~10;
  step(model);
  REQUIRE(model.out == result);
  
}