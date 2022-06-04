# pragma once

#include "setup.h"
#include <cmath>
#include <climits>
#include <set>
#include <unordered_set>


struct Loppu {
public:
	bool voitto;
	int kenelle;

	Loppu(bool onko_voitettu, int kuka_on_voittanut);
};

class Ristinolla0 {
public:
	Vakiot vakio;
	std::vector<int> ruudut;
	std::vector<Rivi> rivit;
	std::vector<int> siirrot;
	int vuorossa;

	bool ohi_on;
	int voittaja;

	std::vector<std::unordered_set<int>> rivit_joissa_k_merkkia;

	Ristinolla0();
	Ristinolla0(Vakiot vakiot, std::vector<int> aiemmat_siirrot);

	void vaihda_vuoroa();

	bool on_ratkaisematon();
	bool risti_voitti();
	bool nolla_voitti();
	Loppu voitti();
	bool onko_siirto_mahdollinen(int ruutu);
	void tee_siirto(int ruutu);
	void kumoa_siirto();
	void aloita_alusta();

	int arvo();
	std::pair<bool, int> onko_ruudun_etaisyys_pelista_pienempi(int ruutu, int ref_etaisyys);
	std::vector<int> priorisoi_ruudut();
};

