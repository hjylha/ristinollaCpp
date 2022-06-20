#pragma once




#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "./../ristinolla.h"
#include "./../ai.h"

extern Vakiot testivakio;


struct TestiTulos {
	std::string kuvaus;
	bool lapi;
};


void esita_testitulokset(std::vector<TestiTulos> testitulokset);

// test_setup
namespace setup
{
TestiTulos test_vakiot();

TestiTulos test_paikkarivilla();

TestiTulos test_sopiiko_rivi();
TestiTulos test_is_ruutu_rivilla();

TestiTulos test_rivi_constructor();

TestiTulos test_laske_ristien_lkm();
TestiTulos test_laske_nollien_lkm();
TestiTulos test_onko_pelattavissa();

TestiTulos test_tee_siirto();
TestiTulos test_kumoa_siirto();
TestiTulos test_tyhjenna();
TestiTulos test_vapaat_ruudut();

TestiTulos test_missa_riveissa_ruutu_on();
}




// test_ristinolla
namespace ristinolla
{
TestiTulos test_Ristinolla_constructor_tyhja();
TestiTulos test_Ristinolla_constructor();

TestiTulos test_vaihda_vuoroa();
TestiTulos test_on_ratkaisematon();
TestiTulos test_risti_voitti();
TestiTulos test_nolla_voitti();
TestiTulos test_voitti();
TestiTulos test_onko_siirto_mahdollinen();
TestiTulos test_tee_siirto();
TestiTulos test_kumoa_siirto();
TestiTulos test_aloita_alusta();
TestiTulos test_arvo();
TestiTulos test_onko_ruudun_etaisyys_pelista_pienempi();
TestiTulos test_priorisoi_ruudut();

// bonus"testi"
TestiTulos ennakoidaan_arvo();
}

// test ai
namespace ai
{
TestiTulos test_aloitussiirto();
TestiTulos test_siirto_arvon_perusteella();
}

// TestiTulos test_
// TestiTulos test_