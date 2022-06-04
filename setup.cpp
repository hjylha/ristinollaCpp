#include "setup.h"


Vakiot::Vakiot() 
: LEVEYS(3), KORKEUS(3),VIER_LKM(3) 
{}

Vakiot::Vakiot(int leveys, int korkeus, int vier_lkm) 
: LEVEYS(leveys), KORKEUS(korkeus), VIER_LKM(vier_lkm)
{}


bool sopiiko_rivi(int ruutu_ja_suunta, Vakiot vakio)
{
	if (ruutu_ja_suunta < 0)
	{
		return false;
	}
	int alkuruutu = ruutu_ja_suunta / 4;
	int suunta = ruutu_ja_suunta % 4;
	// jos alkuruutu on oikean reunan lahella ja rivi menee oikealle
	if ((vakio.LEVEYS - alkuruutu % vakio.LEVEYS < vakio.VIER_LKM) && (suunta == 1 || suunta == 2))
	{
		return false;
	}
	// jos alkuruutu on alareunan lahella ja rivi menee alas
	if ((vakio.KORKEUS - alkuruutu / vakio.LEVEYS < vakio.VIER_LKM) && (suunta == 0 || suunta == 2 || suunta == 3))
	{
		return false;
	}
	// jos alkuruutu on vasemman reunan lahella ja rivi menee alavasemmalle
	if (alkuruutu % vakio.LEVEYS < vakio.VIER_LKM - 1 && suunta == 3)
	{
		return false;
	}
	return true;
}

int is_ruutu_rivilla(int i, int ruutu_ja_suunta, Vakiot vakio) {
	int alkuruutu = ruutu_ja_suunta / 4;
	int suunta = ruutu_ja_suunta % 4;
	switch (suunta)
	{
	case 0:
		return alkuruutu + i * vakio.LEVEYS;
	case 1:
		return alkuruutu + i;
	case 2:
		return alkuruutu + i + i * vakio.LEVEYS;
	case 3:
		return alkuruutu - i + i * vakio.LEVEYS;
	default:
		return -1;
	}
}


PaikkaRivilla::PaikkaRivilla(int rivi_indeksi, int paikkaindeksi) {
	rivi_id = rivi_indeksi;
	paikka = paikkaindeksi;
}


Rivi::Rivi(Vakiot vakiot, int ruutu_ja_suunta) {
	//int alkuruutu = ruutu_ja_suunta / 4;
	//int suunta = ruutu_ja_suunta % 4;
	sopii = sopiiko_rivi(ruutu_ja_suunta, vakiot);
	if (sopii)
	{
		for (int i = 0; i < vakiot.VIER_LKM; i++)
		{
			// oletuksena tyhja ruutu
			status.push_back(2);
			ruudut.push_back(is_ruutu_rivilla(i, ruutu_ja_suunta, vakiot));
		}
	}
	on_pelattavissa = sopii;
	ristien_lkm = 0;
	nollien_lkm = 0;
}

int Rivi::laske_ristien_lkm() {
	int risti_lkm = 0;
	for (int i = 0; i < status.size(); i++)
	{
		if (status[i] == 0)
		{
			risti_lkm++;
		}
	}
	return risti_lkm;
}

int Rivi::laske_nollien_lkm() {
	int nolla_lkm = 0;
	for (int i = 0; i < status.size(); i++)
	{
		if (status[i] == 1)
		{
			nolla_lkm++;
		}
	}
	return nolla_lkm;
}

bool Rivi::onko_pelattavissa() {
	if (!sopii)
	{
		return false;
	}
	if (ristien_lkm > 0 && nollien_lkm > 0)
	{
		return false;
	}
	return true;
}

void Rivi::tee_siirto(int paikkaindeksi, int vuoro) {
	status[paikkaindeksi] = vuoro;
	if (vuoro == 0)
	{
		ristien_lkm++;
	}
	else if (vuoro == 1)
	{
		nollien_lkm++;
	}
	if (on_pelattavissa && ristien_lkm > 0  && nollien_lkm > 0)
	{
		on_pelattavissa = false;
	}
}

void Rivi::kumoa_siirto(int paikkaindeksi, int vuoro) {
	status[paikkaindeksi] = 2;
	if (vuoro == 1)
	{
		ristien_lkm--;
	}
	else if (vuoro == 0)
	{
		nollien_lkm--;
	}
	if (!on_pelattavissa && (ristien_lkm == 0 || nollien_lkm == 0))
	{
		on_pelattavissa = true;
	}
}

void Rivi::tyhjenna() {
	if (sopii)
	{
		for (int i = 0; i < status.size(); i++)
		{
			status[i] = 2;
		}
		on_pelattavissa = true;
	}
	ristien_lkm = 0;
	nollien_lkm = 0;
}

std::vector<int> Rivi::vapaat_ruudut() {
	std::vector<int> vapaat;
	for (int i = 0; i < status.size(); i++)
	{
		if (status[i] == 2)
		{
			vapaat.push_back(ruudut[i]);
		}
	}
	return vapaat;
}


std::vector<PaikkaRivilla> missa_riveissa_ruutu_on(Vakiot vakiot, int ruutu) {
	std::vector<PaikkaRivilla> rivit_ja_paikat;

	// alas menevilla riveilla
	for (int j = 0; j < vakiot.VIER_LKM; j++)
	{
		//ruutu - vakiot.LEVEYS * j
		int rivi_indeksi = 4 * (ruutu - vakiot.LEVEYS * j);
		if (rivi_indeksi < vakiot.LEVEYS * vakiot.KORKEUS * 4 && sopiiko_rivi(rivi_indeksi, vakiot))
		{
			PaikkaRivilla rj(rivi_indeksi, j);
			rivit_ja_paikat.push_back(rj);
		}
	}

	// oikealle menevilla riveilla
	for (int j = 0; j < vakiot.VIER_LKM; j++)
	{
		int rivi_indeksi = 4 * (ruutu - j) + 1;
		if (rivi_indeksi < vakiot.LEVEYS * vakiot.KORKEUS * 4 && sopiiko_rivi(rivi_indeksi, vakiot))
		{
			PaikkaRivilla rj(rivi_indeksi, j);
			rivit_ja_paikat.push_back(rj);
		}
	}

	// alas oikealle menevilla riveilla
	for (int j = 0; j < vakiot.VIER_LKM; j++)
	{
		int rivi_indeksi = 4 * (ruutu - vakiot.LEVEYS * j - j) + 2;
		if (rivi_indeksi < vakiot.LEVEYS * vakiot.KORKEUS * 4 && sopiiko_rivi(rivi_indeksi, vakiot))
		{
			PaikkaRivilla rj(rivi_indeksi, j);
			rivit_ja_paikat.push_back(rj);
		}
	}

	// alas vasemmalle menevilla riveilla
	for (int j = 0; j < vakiot.VIER_LKM; j++)
	{
		int rivi_indeksi = 4 * (ruutu - vakiot.LEVEYS * j + j) + 3;
		if (rivi_indeksi < vakiot.LEVEYS * vakiot.KORKEUS * 4 && sopiiko_rivi(rivi_indeksi, vakiot))
		{
			PaikkaRivilla rj(rivi_indeksi, j);
			rivit_ja_paikat.push_back(rj);
		}
	}

	return rivit_ja_paikat;
}