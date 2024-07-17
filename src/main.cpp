extern "C" {
#include "doomgeneric/doomgeneric.h"
}

int main() {
  doomgeneric_Create(0, NULL);

  for (int i = 0;; i++) {
    doomgeneric_Tick();
  }

  return 0;
}
