#include <bit>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>

using namespace std;

#include <VExercise4.h>


void test_all_inputs(int cs, int sel, uint8_t(op)(uint8_t, uint8_t, uint8_t)) {
  
  VExercise4 model;

  model.cs = cs;
  model.sel = sel;
  model.alpha = 0;
  model.beta = 0;
  model.gamma = 0;

  do {
    do {
      do {
        model.eval();
        uint8_t result {op(model.alpha, model.beta, model.gamma)};
        REQUIRE(result == model.out);
      } while(++model.gamma);
    } while(++model.beta);
  } while(++model.alpha);
}

TEST_CASE("Exercise 4 Test cs=0") {
  test_all_inputs(0, 0, [](uint8_t a, uint8_t b, uint8_t c) -> uint8_t { return 0; });
  test_all_inputs(0, 1, [](uint8_t a, uint8_t b, uint8_t c) -> uint8_t { return 0; });
  test_all_inputs(0, 2, [](uint8_t a, uint8_t b, uint8_t c) -> uint8_t { return 0; });
  test_all_inputs(0, 3, [](uint8_t a, uint8_t b, uint8_t c) -> uint8_t { return 0; });
}

TEST_CASE("Exercise 4 Test cs=1, sel=0") {
  test_all_inputs(1, 0, [](uint8_t a, uint8_t b, uint8_t c) -> uint8_t { return a; });
}

TEST_CASE("Exercise 4 Test cs=1, sel=1") {
  test_all_inputs(1, 1, [](uint8_t a, uint8_t b, uint8_t c) -> uint8_t { return b; });
}

TEST_CASE("Exercise 4 Test cs=1, sel=2") {
  test_all_inputs(1, 2, [](uint8_t a, uint8_t b, uint8_t c) -> uint8_t { return c; });
}

TEST_CASE("Exercise 4 Test cs=1, sel=3") {
  test_all_inputs(1, 3, [](uint8_t a, uint8_t b, uint8_t c) -> uint8_t { return a & (b | c); });
}

