#include "testit.h"


void esita_testitulokset(std::vector<TestiTulos> testitulokset) {
	for (auto& tulos : testitulokset) {
		std::cout << tulos.kuvaus << ": " << tulos.lapi << std::endl;
	}
}

TestiTulos valiteksti(std::string teksti)
{
	TestiTulos tulos;
	tulos.kuvaus = teksti;
	tulos.lapi = false;
	return tulos;
}


std::vector<TestiTulos> aja_testit() {
	std::vector<TestiTulos> testitulokset;

	testitulokset.push_back(valiteksti("setup.cpp -testit (tulos 0)"));
	testitulokset.push_back(setup::test_vakiot());
	testitulokset.push_back(setup::test_paikkarivilla());
	testitulokset.push_back(setup::test_sopiiko_rivi());
	testitulokset.push_back(setup::test_is_ruutu_rivilla());
	testitulokset.push_back(setup::test_rivi_constructor());
	testitulokset.push_back(setup::test_laske_ristien_lkm());
	testitulokset.push_back(setup::test_laske_nollien_lkm());
	testitulokset.push_back(setup::test_onko_pelattavissa());
	testitulokset.push_back(setup::test_tee_siirto());
	testitulokset.push_back(setup::test_kumoa_siirto());
	testitulokset.push_back(setup::test_tyhjenna());
	testitulokset.push_back(setup::test_vapaat_ruudut());
	testitulokset.push_back(setup::test_missa_riveissa_ruutu_on());

	testitulokset.push_back(valiteksti(""));
	testitulokset.push_back(valiteksti("ristinolla.cpp -testit (tulos 0)"));
	testitulokset.push_back(ristinolla::test_Ristinolla_constructor_tyhja());
	testitulokset.push_back(ristinolla::test_Ristinolla_constructor());
	testitulokset.push_back(ristinolla::test_vaihda_vuoroa());
	testitulokset.push_back(ristinolla::test_on_ratkaisematon());
	testitulokset.push_back(ristinolla::test_risti_voitti());
	testitulokset.push_back(ristinolla::test_nolla_voitti());
	testitulokset.push_back(ristinolla::test_voitti());
	testitulokset.push_back(ristinolla::test_onko_siirto_mahdollinen());
	testitulokset.push_back(ristinolla::test_tee_siirto());
	testitulokset.push_back(ristinolla::test_kumoa_siirto());
	testitulokset.push_back(ristinolla::test_aloita_alusta());
	testitulokset.push_back(ristinolla::test_priorisoi_ruudut());
	testitulokset.push_back(ristinolla::ennakoidaan_arvo());

	testitulokset.push_back(valiteksti(""));
	testitulokset.push_back(valiteksti("ai.cpp -testit (tulos 0)"));
	testitulokset.push_back(ai::test_aloitussiirto());
	testitulokset.push_back(ai::test_siirto_arvon_perusteella());



	return testitulokset;
}


int main() {
	std::vector<TestiTulos> testitulokset = aja_testit();

	esita_testitulokset(testitulokset);

	return 0;
}