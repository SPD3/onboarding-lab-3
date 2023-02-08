
#include <bit>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>

using namespace std;

#include <VExercise3.h>

struct Ex3Simulation {
  int a;
  uint16_t b;
  uint16_t c;

  uint16_t out;

  Ex3Simulation(int a, uint16_t b, uint16_t c) : a(a), b(b), c(c) {
    out = (get_Mystery2_b_in() << 8) | get_Mystery2_a_in();
  }

private:
  int currentState = 4;

  uint8_t mystery1Simul(int a, uint8_t b, uint8_t c) {
    if (a == 0) {
      return ((b & 0b111) << 3) | (c & 0b111);
    }else if(a == 1) { 
      return ((c & 0b111) << 3) | (b & 0b111) | 0b1000000;
    }else if(a == 2) {
      return b;
    }
    return c;
  }

  uint8_t get_Mystery2_a_in() {
    int top_a_in = a & 0b11;
    
    uint8_t top_b_in = b & 0b11111111;
    uint8_t top_c_in = c & 0b11111111;
    return mystery1Simul(top_a_in, top_b_in, top_c_in);
  }

  uint8_t get_Mystery2_b_in() {
    int bot_a_in = (a & 0b1100) >> 2;
    uint8_t bot_b_in = b >> 8;
    uint8_t bot_c_in = c >> 8;

    return mystery1Simul(bot_a_in, bot_b_in, bot_c_in);
  }

public:
  void step() {
    uint8_t a_in = get_Mystery2_a_in();
    uint8_t b_in = get_Mystery2_b_in();

    currentState = (currentState + 1) % 5;
    if (currentState == 0) {
      out = (a_in << 8) | (out & 0b11111111);
    }else if(currentState == 1) {
      out = (out & 0b1111111100000000) | b_in;
    }else if(currentState == 2) {
      out = ((out & 0b1111111100000000) >> 8) | ((out & 0b11111111) << 8);
    }else if(currentState == 3) {
      out = ((out & 0b1111) << 12) | ((out & 0b11110000) << 4) | ((out & 0b111100000000) >> 4) | (out >> 12);
    }else {
      out = popcount(out) & 1;
    }
    
  }
};

void step(VExercise3& model) {
  model.clk = 1;
  model.eval();
  model.clk = 0;
  model.eval();
}

void testModel(VExercise3& model) {
  Ex3Simulation ex3Simulation(model.a, model.b, model.c);

  model.reset = 1;
  step(model);
  model.reset = 0;
  REQUIRE(model.out == ex3Simulation.out);

  for(size_t i = 0; i < 10; ++i) {
    step(model);
    ex3Simulation.step();
    REQUIRE(model.out == ex3Simulation.out);
  }
}

TEST_CASE("Exercise 3 Mystery1") {
  VExercise3 model;
  model.a = 0;
  model.b = 0;
  model.c = 0;

  for(size_t i = 0; i < 16; ++i) {
    model.a = i;
    for (size_t j = 0; j < 10; ++j) {
      model.b = rand() % ((uint16_t) ~0 + 1);
      for (size_t k = 0; k < 10; ++k) { 
        model.c = rand() % ((uint16_t) ~0 + 1);
        testModel(model);
        
      }
    }
  } 
}

TEST_CASE("Exercise 3 Test reseting") {
  VExercise3 model;
  model.reset = 1;
  model.a = 0;
  model.b = 0;
  model.c = 0;

  step(model);
  uint16_t result = 0;
  REQUIRE(model.out == result);

  step(model);
  step(model);
  step(model);
  step(model);
  REQUIRE(model.out == result);

}