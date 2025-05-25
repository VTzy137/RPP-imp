#pragma once

#include "types.hpp"

class Mutation {
  public:
    static vtzy_types::path* mutation(vtzy_types::path* p, float toiu);
    static float est;

  private:
    Mutation() = delete;
};