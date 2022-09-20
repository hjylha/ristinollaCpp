
#include "ristinolla.h"
#include "ristinollaKonsolissa.h"
#include <iostream>

int main() {
    // Ristinolla rn = Ristinolla(Vakiot(24, 16, 5), {});
    // rn.tee_siirto(0);
    // rn.tee_siirto(1);
    // rn.tee_siirto(45);
    // rn.tee_siirto(69);

    // std::cout << "Leveys:" << rn.vakio.LEVEYS << "\n";
    // std::cout << "Korkeus" << rn.vakio.KORKEUS << "\n";

    // piirraRistinolla(rn, 32);

    pelaaRistinollaa(24, 16, 5, 1);
    return 0;
}