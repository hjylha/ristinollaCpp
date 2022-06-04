#pragma once

#include <string>
#include <vector>


const char MERKIT[3] = {'X', '0', ' '};
const std::string SUUNNAT[4] = { "A", "O", "AO", "AV" };


struct Vakiot {
public:
	//const int LEVEYS;
	int LEVEYS;
	//const int KORKEUS;
	int KORKEUS;
	//const int VIER_LKM;
	int VIER_LKM;
	
	Vakiot();
	Vakiot(int leveys, int korkeus, int vier_lkm);
};


struct PaikkaRivilla {
public:
	int rivi_id;
	int paikka;

	PaikkaRivilla(int rivi_indeksi, int paikkaindeksi);
};

class Rivi {
public:
    bool sopii;
	std::vector<int> status;
	std::vector<int> ruudut;
	int ristien_lkm;
	int nollien_lkm;

	bool on_pelattavissa;

	Rivi(Vakiot vakiot, int ruutu_ja_suunta);

	int laske_ristien_lkm();
	int laske_nollien_lkm();
	bool onko_pelattavissa();

	void tee_siirto(int paikkaindeksi, int vuoro);
	void kumoa_siirto(int paikkaindeksi, int vuoro);
	void tyhjenna();

	std::vector<int> vapaat_ruudut();
};


std::vector<PaikkaRivilla> missa_riveissa_ruutu_on(Vakiot vakiot, int ruutu);
