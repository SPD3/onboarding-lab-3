#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <VExercise1.h>

using namespace std;

void test_all_inputs(uint8_t code, uint8_t(op)(uint8_t, uint8_t)) {
  VExercise1 model;
  model.op = code;
  model.a = 0;
  model.b = 0;

  do {
    do {
      model.eval();
      uint8_t result {op(model.a, model.b)};
      if (result != model.out) {
      //if (code == 1) {
        cout << "a: " << unsigned(model.a) << endl;
        cout << "b: " << unsigned(model.b) << endl;
        cout << "result: " << unsigned(result) << endl;
        cout << "out: " << unsigned(model.out) << endl;
        cout << "---------------------------------" << endl;
      }
      REQUIRE(result == model.out);
    } while(++model.b);
    model.b = 0;
  } while(++model.a);
}

TEST_CASE("Opcode 0, Xor") {
  test_all_inputs(0, [](uint8_t a, uint8_t b) -> uint8_t { return a ^ b; });
}

TEST_CASE("Opcode 1, Left shift") {
  test_all_inputs(1, [](uint8_t a, uint8_t b) -> uint8_t { 
    if(b >= 8) {
      return 0; // this accounts for integer promotion as explained here: https://stackoverflow.com/questions/30473958/what-is-going-on-with-bitwise-operators-and-integer-promotion
    }
    return a << b; 
  });
}

TEST_CASE("Opcode 2, %") {
  test_all_inputs(2, [](uint8_t a, uint8_t b) -> uint8_t { 
    if (b == 0) {
      return 0;
    }
    return a % b; 
  });
}

TEST_CASE("Opcode 3, ~(a & b)") {
  test_all_inputs(3, [](uint8_t a, uint8_t b) -> uint8_t { return ~(a & b); });
}