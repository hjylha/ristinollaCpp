#include "testit.h"


TestiTulos ai::test_aloitussiirto()
{
    bool testi = aloitussiirto(testivakio) == 12;

    

    Vakiot vakio(35, 25, 5);
    testi = testi && aloitussiirto(vakio) == 35 * 25 / 2;

    vakio = Vakiot(3, 3, 3);
    testi = testi && aloitussiirto(vakio) == 4;

    vakio = Vakiot(4, 4, 4);
    testi = testi && aloitussiirto(vakio) == 10;

    TestiTulos tulos;
	tulos.kuvaus = "aloitussiirto-funktio";
	tulos.lapi = testi;

    return tulos;
}


TestiTulos ai::test_siirto_arvon_perusteella()
{
    Ristinolla ristinolla(testivakio, {});
    bool testi = siirto_arvon_perusteella(ristinolla) == 12;

    TestiTulos tulos;
	tulos.kuvaus = "siirto_arvon_perusteella-funktio (TODO)";
	tulos.lapi = testi;

    return tulos;
}