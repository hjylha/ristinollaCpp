#pragma once

#include <string>
#include <vector>
#include <list>

class Vakiot {
public:
	int LEVEYS;
	int KORKEUS;
	int VIER_LKM;
	char MERKIT[2] = {'X', '0'};
	std::string SUUNNAT[4] = { "A", "O", "AO", "AV" };
	Vakiot();
	Vakiot(int leveys, int korkeus, int vier_lkm);
};

class Rivi {
public:
	Vakiot vakiot;
	std::string suunta;
	std::vector<int> ruudut;
	std::vector<char> status;
	//Rivi(int rivin_pituus);
	Rivi(Vakiot vakiot, std::string rivin_suunta, int rivin_alkuruutu);
	Rivi(Vakiot vakiot, std::string rivin_suunta, int rivin_alkuruutu, std::vector<int> ristit, std::vector<int> nollat);
	int ristien_lkm();
	int nollien_lkm();
	bool on_pelattavissa();
};

class Ristinolla {
public:
	Vakiot vakiot;
	std::vector<int> vapaat;
	std::vector<int> ristit;
	std::vector<int> nollat;
	std::vector<Rivi> mahdolliset_rivit;
	//std::vector<bool> aktiiviset_rivit;
	int max_ristit;
	int max_nollat;
	int vuorossa;
	Ristinolla();
	Ristinolla(Vakiot vakio, std::vector<int> ristiruudut, std::vector<int> nollaruudut);
	bool on_ratkaisematon();
	bool risti_voitti();
	bool nolla_voitti();
	bool onko_siirto_mahdollinen(int ruutu);
	void tee_siirto(int ruutu);
	void aloita_alusta();
};

class Ristinollapeli {
public:
	/*int KORKEUS;
	int LEVEYS;
	int VIER_LKM;
	char MERKIT[2];
	std::string SUUNNAT[4];*/
	Vakiot vakiot;
	Ristinolla ristinolla;
	Ristinollapeli();
	Ristinollapeli(Vakiot vakio);
};


// AI-juttuja/pelin tallennus
class PelattuPeli {
public:
	int lopputulos;
	//std::vector<int> ristit;
	//std::vector<int> nollat;
	std::vector<int> siirrot;
	PelattuPeli();
	PelattuPeli(int tulos, std::vector<int>ristivektori, std::vector<int> nollavektori);
};