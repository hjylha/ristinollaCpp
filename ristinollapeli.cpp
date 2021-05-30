#include "ristinollapeli.h"

Vakiot::Vakiot() {
	LEVEYS = 3;
	KORKEUS = 3;
	VIER_LKM = 3;
}

Vakiot::Vakiot(int leveys, int korkeus, int vier_lkm) {
	LEVEYS = leveys;
	KORKEUS = korkeus;
	VIER_LKM = vier_lkm;
}

// tarpeeton oletusconstructor
Ristinollapeli::Ristinollapeli() {
	vakiot = Vakiot(3, 3, 3);
	/*KORKEUS = 3;
	LEVEYS = 3;
	VIER_LKM = 3;
	char MERKIT[2] = { 'R', '0' };
	std::string SUUNNAT[4] = { "A", "O", "AO", "AV" };*/
}

Ristinollapeli::Ristinollapeli(Vakiot vakio) {
	vakiot = vakio;
	ristinolla = Ristinolla(vakio, {}, {});
	/*KORKEUS = korkeus;
	LEVEYS = leveys;
	VIER_LKM = vier_lkm;
	char MERKIT[2] = { 'X', '0' };
	std::string SUUNNAT[4] = { "A", "O", "AO", "AV" };*/
}


//mahdollisesti tarvittavia funktioita
bool onko_ruudussa_risti(int ruutu, std::vector<int> ristit) {
	for (int i = 0; i < ristit.size(); i++)
	{
		if (ruutu == ristit[i]) {
			return true;
		}
	}
	return false;
}

bool onko_ruudussa_nolla(int ruutu, std::vector<int> nollat) {
	for (int i = 0; i < nollat.size(); i++)
	{
		if (ruutu == nollat[i]) {
			return true;
		}
	}
	return false;
}

bool onko_ruutu_vapaa(int ruutu, std::vector<int> ristit, std::vector<int> nollat) {
	if (onko_ruudussa_risti(ruutu, ristit))
	{
		return false;
	}
	if (onko_ruudussa_nolla(ruutu, nollat))
	{
		return false;
	}
	return true;
}

std::vector<int> vapaat_ruudut(Vakiot vakiot, std::vector<int> ristit, std::vector<int> nollat) {
	std::vector<int> vapaat;
	for (int i = 0; i < vakiot.KORKEUS * vakiot.LEVEYS; i++)
	{
		if (onko_ruutu_vapaa(i, ristit, nollat))
		{
			vapaat.push_back(i);
		}
	}
	return vapaat;
}

// lisataan ruutu jarjestettyyn vektoriin
std::vector<int> lisaa_ruutu(int ruutu, std::vector<int> vektori) {
	// jos vektori on tyhja, asia on helppo
	if (vektori.empty())
	{
		vektori.push_back(ruutu);
		return vektori;
	}
	// muuten joutuu kai tekemaan jotain
	int indeksi = 0;
	int lisa = vektori.size() / 2;
	while (lisa > 0)
	{
		indeksi = indeksi + lisa;
		if (ruutu < vektori[indeksi])
		{
			indeksi = indeksi - lisa;
		}
		lisa = lisa / 2;
	}
	// joko indeksin paikalle tai seuraavalle paikalle
	//std::next(vektori.begin(), index)
	if (ruutu < vektori[indeksi])
	{
		vektori.insert(vektori.begin() + indeksi, ruutu);
	}
	else
	{
		vektori.insert(vektori.begin() + indeksi + 1, ruutu);
	}
	return vektori;
}


Rivi::Rivi(Vakiot vakio, std::string rivin_suunta, int rivin_alkuruutu) {
	vakiot = vakio;
	
}

Rivi::Rivi(Vakiot vakio, std::string rivin_suunta, int rivin_alkuruutu, std::vector<int> ristit, std::vector<int> nollat) {
	vakiot = vakio;
	suunta = rivin_suunta;
	//ruudut[0] = rivin_alkuruutu;
	ruudut.push_back(rivin_alkuruutu);
	status.push_back(' ');
	for (int i = 1; i < vakiot.VIER_LKM; i++)
	{
		//status[i] = ' ';
		status.push_back(' ');
		ruudut.push_back(0);
	}
	if (rivin_suunta == vakiot.SUUNNAT[0])  // "A"
	{
		for (int i = 0; i < vakiot.VIER_LKM; i++)
		{
			ruudut[i] = rivin_alkuruutu + vakiot.LEVEYS * i;
			//ruudut.push_back(rivin_alkuruutu + vakiot.LEVEYS * i);
			if (onko_ruudussa_risti(rivin_alkuruutu + vakiot.LEVEYS * i, ristit))
			{
				status[i] = vakiot.MERKIT[0];
			}
			else if (onko_ruudussa_nolla(rivin_alkuruutu + vakiot.LEVEYS * i, nollat)) {
				status[i] = vakiot.MERKIT[1];
			}
		}
	}
	else if (rivin_suunta == vakiot.SUUNNAT[1])  // "O"
	{
		for (int i = 1; i < vakiot.VIER_LKM; i++)
		{
			ruudut[i] = rivin_alkuruutu + i;
			if (onko_ruudussa_risti(rivin_alkuruutu + i, ristit))
			{
				status[i] = vakiot.MERKIT[0];
			}
			else if (onko_ruudussa_nolla(rivin_alkuruutu + i, nollat)) {
				status[i] = vakiot.MERKIT[1];
			}
		}
	}
	else if (rivin_suunta == vakiot.SUUNNAT[2])  // "AO"
	{
		for (int i = 1; i < vakiot.VIER_LKM; i++)
		{
			ruudut[i] = rivin_alkuruutu + vakiot.LEVEYS * i + i;
			if (onko_ruudussa_risti(rivin_alkuruutu + vakiot.LEVEYS * i + i, ristit))
			{
				status[i] = vakiot.MERKIT[0];
			}
			else if (onko_ruudussa_nolla(rivin_alkuruutu + vakiot.LEVEYS * i + i, nollat)) {
				status[i] = vakiot.MERKIT[1];
			}
		}
	}
	else if (rivin_suunta == vakiot.SUUNNAT[3])  // "AV"
	{
		for (int i = 1; i < vakiot.VIER_LKM; i++)
		{
			ruudut[i] = rivin_alkuruutu + vakiot.LEVEYS * i - i;
			if (onko_ruudussa_risti(rivin_alkuruutu + vakiot.LEVEYS * i - i, ristit))
			{
				status[i] = vakiot.MERKIT[0];
			}
			else if (onko_ruudussa_nolla(rivin_alkuruutu + vakiot.LEVEYS * i - i, nollat)) {
				status[i] = vakiot.MERKIT[1];
			}
		}
	}
}

int Rivi::ristien_lkm() {
	int risti_lkm = 0;
	for (int i = 0; i < vakiot.VIER_LKM; i++) {
		if (status[i] == vakiot.MERKIT[0])
		{
			risti_lkm++;
		}
	}
	return risti_lkm;
}

int Rivi::nollien_lkm() {
	int nolla_lkm = 0;
	for (int i = 0; i < vakiot.VIER_LKM; i++) {
		if (status[i] == vakiot.MERKIT[1])
		{
			nolla_lkm++;
		}
	}
	return nolla_lkm;
}

// taytyy ottaa huomioon pelialueen ulkopuolelle menevat rivit
bool Rivi::sopii() {
	// jos alkuruutu on oikean reunan lahella ja rivi menee oikealle
	if (vakiot.LEVEYS - ruudut[0] % vakiot.LEVEYS < vakiot.VIER_LKM)
	{
		if (suunta == "O" || suunta == "AO")
		{
			return false;
		}
	}
	// jos alkuruutu on alareunan lahella ja rivi menee alas
	if (vakiot.KORKEUS - ruudut[0] / vakiot.KORKEUS < vakiot.VIER_LKM)
	{
		if (suunta == "A" || suunta == "AV" || suunta == "AO")
		{
			return false;
		}
	}
	// jos alkuruutu on vasemman reunan lahella ja rivi menee alavasemmalle
	if (ruudut[0] % vakiot.LEVEYS < vakiot.VIER_LKM - 1 && suunta == "AV")
	{
		return false;
	}
	return true;
}

bool Rivi::on_pelattavissa() {
	bool on_risti = false;
	bool on_nolla = false;
	for (int i = 0; i < vakiot.VIER_LKM; i++)
	{
		if (status[i] == vakiot.MERKIT[0]) {
			on_risti = true;
		}
		else if (status[i] == vakiot.MERKIT[1])
		{
			on_nolla = true;
		}
		if (on_risti && on_nolla)
		{
			return false;
		}
	}
	return true;
}

bool ei_pelattavissa(Rivi rivi) {
	if (rivi.on_pelattavissa()) return false;
	return true;
}


// turha oletusconstructor, ettei editori valita
Rivit::Rivit() {

}

Rivit::Rivit(Vakiot vakio, std::vector<int> ristit, std::vector<int> nollat) {
	vakiot = vakio;
	for (int i = 0; i < vakio.KORKEUS * vakio.LEVEYS * 4; i++)
	{
		rivit.push_back(Rivi(vakio, vakio.SUUNNAT[i % 4], i / 4, ristit, nollat));
		aktiiviset_rivit.push_back(false);
		if (rivit[i].sopii() && rivit[i].on_pelattavissa())
		{
			//aktiiviset_rivit.push_back(i);
			aktiiviset_rivit[i] = true;
		}
	}
}

// apufunktio, jota ei kai enaa tarvita
//std::vector<Rivi> pelattavat_rivit(Vakiot vakiot, std::vector<int> ristit, std::vector<int> nollat) {
//	std::vector<Rivi> rivit;
//	// 4 suuntaa
//	for (int i = 0; i < 4; i++)
//	{
//		//SUUNNAT[0] = "A"
//		if (i == 0)
//		{
//			for (int j = 0; j < vakiot.KORKEUS * vakiot.LEVEYS; j++)
//			{
//				if (j / vakiot.LEVEYS <= vakiot.KORKEUS - vakiot.VIER_LKM) {
//					Rivi rivi(vakiot, vakiot.SUUNNAT[i], j, ristit, nollat);
//					if (rivi.ristien_lkm() == 0 || rivi.nollien_lkm() == 0)
//					{
//						rivit.push_back(rivi);
//					}
//				}
//			}
//		}
//
//		//SUUNNAT[1] = "O"
//		else if (i == 1)
//		{
//			for (int j = 0; j < vakiot.KORKEUS * vakiot.LEVEYS; j++)
//			{
//				if (j % vakiot.LEVEYS <= vakiot.LEVEYS - vakiot.VIER_LKM) {
//					Rivi rivi(vakiot, vakiot.SUUNNAT[i], j, ristit, nollat);
//					if (rivi.ristien_lkm() == 0 || rivi.nollien_lkm() == 0)
//					{
//						rivit.push_back(rivi);
//					}
//				}
//			}
//		}
//
//		//SUUNNAT[2] = "AO"
//		else if (i == 2)
//		{
//			for (int j = 0; j < vakiot.KORKEUS * vakiot.LEVEYS; j++)
//			{
//				if (j % vakiot.LEVEYS <= vakiot.LEVEYS - vakiot.VIER_LKM && j / vakiot.LEVEYS <= vakiot.KORKEUS - vakiot.VIER_LKM) {
//					Rivi rivi(vakiot, vakiot.SUUNNAT[i], j, ristit, nollat);
//					if (rivi.ristien_lkm() == 0 || rivi.nollien_lkm() == 0)
//					{
//						rivit.push_back(rivi);
//					}
//				}
//			}
//		}
//
//		//SUUNNAT[3] = "AV"
//		else if (i == 3) {
//			for (int j = 0; j < vakiot.KORKEUS * vakiot.LEVEYS; j++)
//			{
//				if (j % vakiot.LEVEYS >= vakiot.VIER_LKM - 1 && j / vakiot.LEVEYS <= vakiot.KORKEUS - vakiot.VIER_LKM) {
//					Rivi rivi(vakiot, vakiot.SUUNNAT[i], j, ristit, nollat);
//					if (rivi.ristien_lkm() == 0 || rivi.nollien_lkm() == 0)
//					{
//						rivit.push_back(rivi);
//					}
//				}
//			}
//		}
//	}
//	return rivit;
//}

std::vector<std::vector<int>> Rivit::missa_riveissa_ruutu_on(int ruutu) {
	std::vector<std::vector<int>> rivi_ja_paikka;
	// alas menevilla riveilla
	for (int j = 0; j < vakiot.VIER_LKM; j++)
	{
		//ruutu - vakiot.LEVEYS * j
		int rivi_indeksi = 4 * (ruutu - vakiot.LEVEYS * j);
		if (rivi_indeksi >= 0 && rivi_indeksi < vakiot.LEVEYS * vakiot.KORKEUS * 4 && rivit[rivi_indeksi].sopii())
		{
			std::vector<int> rj;
			rj.push_back(rivi_indeksi);
			rj.push_back(j);
			rivi_ja_paikka.push_back(rj);
		}
	}

	// oikealle menevilla riveilla
	for (int j = 0; j < vakiot.VIER_LKM; j++)
	{
		int rivi_indeksi = 4 * (ruutu - j) + 1;
		if (rivi_indeksi >= 0 && rivi_indeksi < vakiot.LEVEYS * vakiot.KORKEUS * 4 && rivit[rivi_indeksi].sopii())
		{
			std::vector<int> rj;
			rj.push_back(rivi_indeksi);
			rj.push_back(j);
			rivi_ja_paikka.push_back(rj);
		}
	}

	// alas oikealle menevilla riveilla
	for (int j = 0; j < vakiot.VIER_LKM; j++)
	{
		int rivi_indeksi = 4 * (ruutu - vakiot.LEVEYS * j - j) + 2;
		if (rivi_indeksi >= 0 && rivi_indeksi < vakiot.LEVEYS * vakiot.KORKEUS * 4 && rivit[rivi_indeksi].sopii())
		{
			std::vector<int> rj;
			rj.push_back(rivi_indeksi);
			rj.push_back(j);
			rivi_ja_paikka.push_back(rj);
		}
	}

	// alas vasemmalle menevilla riveilla
	for (int j = 0; j < vakiot.VIER_LKM; j++)
	{
		int rivi_indeksi = 4 * (ruutu - vakiot.LEVEYS * j + j) + 3;
		if (rivi_indeksi >= 0 && rivi_indeksi < vakiot.LEVEYS * vakiot.KORKEUS * 4 && rivit[rivi_indeksi].sopii())
		{
			std::vector<int> rj;
			rj.push_back(rivi_indeksi);
			rj.push_back(j);
			rivi_ja_paikka.push_back(rj);
		}
	}
	return rivi_ja_paikka;
}



Ristinolla::Ristinolla() {}

Ristinolla::Ristinolla(Vakiot vakio, std::vector<int> ristiruudut, std::vector<int> nollaruudut) {
	vakiot = vakio;
	ristit = ristiruudut;
	nollat = nollaruudut;
	vuorossa = (ristiruudut.size() + nollaruudut.size()) % 2;
	vapaat = vapaat_ruudut(vakio, ristiruudut, nollaruudut);
	rivit = Rivit(vakio, ristit, nollat);
	//mahdolliset_rivit = pelattavat_rivit(vakio, ristiruudut, nollaruudut);
	max_ristit = 0;
	max_nollat = 0;
	//for (auto i = mahdolliset_rivit.begin(); i != mahdolliset_rivit.end(); i++)
	//for (int i = 0; i < rivit.aktiiviset_rivit.size(); i++)
	for (auto i = rivit.aktiiviset_rivit.begin(); i != rivit.aktiiviset_rivit.end(); i++)
	{
		//int risti_lkm = i->ristien_lkm();
		//int nolla_lkm = i->nollien_lkm();
		//int risti_lkm = rivit.rivit[rivit.aktiiviset_rivit[i]].ristien_lkm();
		//int nolla_lkm = rivit.rivit[rivit.aktiiviset_rivit[i]].nollien_lkm();
		int risti_lkm = rivit.rivit[*i].ristien_lkm();
		int nolla_lkm = rivit.rivit[*i].nollien_lkm();
		if (risti_lkm > max_ristit)
		{
			max_ristit = risti_lkm;
		}
		if (nolla_lkm > max_nollat)
		{
			max_nollat = nolla_lkm;
		}
	}
}

bool Ristinolla::on_ratkaisematon() {
	//if (rivit.aktiiviset_rivit.empty()) {
		//return true;
	//}
	for (int i = 0; i < rivit.aktiiviset_rivit.size(); i++)
	{
		if (rivit.aktiiviset_rivit[i])
		{
			return false;
		}
	}
	return true;
	//return false;
}

bool Ristinolla::risti_voitti() {
	if (max_ristit == vakiot.VIER_LKM)
	{
		return true;
	}
	return false;
}

bool Ristinolla::nolla_voitti() {
	if (max_nollat == vakiot.VIER_LKM)
	{
		return true;
	}
	return false;
}

bool Ristinolla::onko_siirto_mahdollinen(int ruutu) {
	if (onko_ruutu_vapaa(ruutu, ristit, nollat)) {
		return true;
	}
	return false;
}

//bool Ristinolla::poistetaan(int rivi_id) {
//	if (poistettavat.empty())
//	{
//		return false;
//	}
//	for (int i = 0; i < poistettavat.size(); i++)
//	{
//		if (rivi_id == poistettavat[i])
//		{
//			return true;
//		}
//	}
//	return false;
//}

void Ristinolla::tee_siirto(int ruutu) {
	if (vuorossa == 0)
	{
		//ristit.push_back(ruutu);
		ristit = lisaa_ruutu(ruutu, ristit);
	}
	else
	{
		//nollat.push_back(ruutu);
		nollat = lisaa_ruutu(ruutu, nollat);
	}
	siirrot.push_back(ruutu);
	// vapaiden update
	vapaat.erase(std::remove(vapaat.begin(), vapaat.end(), ruutu), vapaat.end());
	//for (auto i = vapaat.begin(); i != vapaat.end(); i++)
	//{
	//	if (*i == ruutu)
	//	{
	//		if (i == vapaat.begin())
	//		{
	//			vapaat.erase(i);
	//			//i = vapaat.begin();
	//		}
	//		else
	//		{
	//			vapaat.erase(i--);
	//		}
	//		break;
	//	}
	//}

	// rivien update
	//std::vector<int> poistettavat;
	//poistettavat.clear();
	std::vector<std::vector<int>> muokattavat = rivit.missa_riveissa_ruutu_on(ruutu);
	//for (auto i = muokattavat.begin(); i != muokattavat.end(); i++)
	for  (int i = 0; i < muokattavat.size(); i++)
	{
		rivit.rivit[muokattavat[i][0]].status[muokattavat[i][1]] = vakiot.MERKIT[vuorossa];
		//rivit.rivit[*i[0]].status[*i[1]] = vakiot.MERKIT[vuorossa];
		//int risti_lkm = rivit.rivit[*i[0]].ristien_lkm();
		//int nolla_lkm = rivit.rivit[*i[0]].nollien_lkm();
		if (rivit.rivit[muokattavat[i][0]].ristien_lkm() > max_ristit)
		{
			max_ristit = rivit.rivit[muokattavat[i][0]].ristien_lkm();
		}
		else if (rivit.rivit[muokattavat[i][0]].nollien_lkm() > max_nollat)
		{
			max_nollat = rivit.rivit[muokattavat[i][0]].nollien_lkm();
		}
		if (!(rivit.rivit[muokattavat[i][0]].on_pelattavissa()) && rivit.aktiiviset_rivit[muokattavat[i][0]])
		{
			//poistettavat.push_back(muokattavat[i][0]);
			rivit.aktiiviset_rivit[muokattavat[i][0]] = false;
		}
		//if (rivit.rivit[*i[0]].ristien_lkm() > max_ristit)
		//{
			//max_ristit = rivit.rivit[*i[0]].ristien_lkm();
		//}
		//else if (rivit.rivit[*i[0]].nollien_lkm() > max_nollat)
		//{
			//max_nollat = rivit.rivit[*i[0]].nollien_lkm();
		//}
		//if (!(rivit.rivit[*i[0]].on_pelattavissa()))
		//{
			//poistettavat.push_back(*i[0]);
		//}
	}
	 
	// vanha tapa muokata riveja
	//for (auto i = mahdolliset_rivit.begin(); i != mahdolliset_rivit.end(); i++)
	//{
	//	int alkuruutu = i->ruudut[0];
	//	std::string suunta = i->suunta;
	//	if (alkuruutu % vakiot.LEVEYS == ruutu % vakiot.LEVEYS && suunta == "A")
	//	{
	//		int koord = ruutu / vakiot.LEVEYS - alkuruutu / vakiot.LEVEYS;
	//		if (0 <= koord && koord < vakiot.VIER_LKM)
	//		{
	//			i->status[koord] = vakiot.MERKIT[vuorossa];
	//			int risti_lkm = i->ristien_lkm();
	//			int nolla_lkm = i->nollien_lkm();
	//			if (risti_lkm > max_ristit)
	//			{
	//				max_ristit = risti_lkm;
	//			}
	//			else if (nolla_lkm > max_nollat)
	//			{
	//				max_nollat = nolla_lkm;
	//			}
	//			//poistetaanko rivi?
	//			//if (!(i->on_pelattavissa()))
	//			//{
	//			//	mahdolliset_rivit.erase(i--);
	//			//	/*if (on_viimeinen)
	//			//	{
	//			//		break;
	//			//	}*/
	//			//}
	//		}
	//	}
	//	else if (alkuruutu / vakiot.LEVEYS == ruutu / vakiot.LEVEYS && suunta == "O")
	//	{
	//		int koord = ruutu % vakiot.LEVEYS - alkuruutu % vakiot.LEVEYS;
	//		if (0 <= koord && koord < vakiot.VIER_LKM)
	//		{
	//			i->status[koord] = vakiot.MERKIT[vuorossa];
	//			int risti_lkm = i->ristien_lkm();
	//			int nolla_lkm = i->nollien_lkm();
	//			if (risti_lkm > max_ristit)
	//			{
	//				max_ristit = risti_lkm;
	//			}
	//			else if (nolla_lkm > max_nollat)
	//			{
	//				max_nollat = nolla_lkm;
	//			}
	//			//poistetaanko rivi?
	//			//if (!(i->on_pelattavissa()))
	//			//{
	//			//	mahdolliset_rivit.erase(i--);
	//			//	/*if (on_viimeinen)
	//			//	{
	//			//		break;
	//			//	}*/
	//			//}
	//		}
	//	}
	//	else if (alkuruutu / vakiot.LEVEYS - alkuruutu % vakiot.LEVEYS == ruutu / vakiot.LEVEYS - ruutu % vakiot.LEVEYS && suunta == "AO")
	//	{
	//		int koord = ruutu % vakiot.LEVEYS - alkuruutu % vakiot.LEVEYS;
	//		if (0 <= koord && koord < vakiot.VIER_LKM)
	//		{
	//			i->status[koord] = vakiot.MERKIT[vuorossa];
	//			int risti_lkm = i->ristien_lkm();
	//			int nolla_lkm = i->nollien_lkm();
	//			if (risti_lkm > max_ristit)
	//			{
	//				max_ristit = risti_lkm;
	//			}
	//			else if (nolla_lkm > max_nollat)
	//			{
	//				max_nollat = nolla_lkm;
	//			}
	//			//poistetaanko rivi?
	//			//if (!(i->on_pelattavissa()))
	//			//{
	//			//	mahdolliset_rivit.erase(i--);
	//			//	/*if (on_viimeinen)
	//			//	{
	//			//		break;
	//			//	}*/
	//			//}
	//		}
	//	}
	//	else if (alkuruutu / vakiot.LEVEYS + alkuruutu % vakiot.LEVEYS == ruutu / vakiot.LEVEYS + ruutu % vakiot.LEVEYS && suunta == "AV")
	//	{
	//		int koord = alkuruutu % vakiot.LEVEYS - ruutu % vakiot.LEVEYS;
	//		if (0 <= koord && koord < vakiot.VIER_LKM)
	//		{
	//			i->status[koord] = vakiot.MERKIT[vuorossa];
	//			int risti_lkm = i->ristien_lkm();
	//			int nolla_lkm = i->nollien_lkm();
	//			if (risti_lkm > max_ristit)
	//			{
	//				max_ristit = risti_lkm;
	//			}
	//			else if (nolla_lkm > max_nollat)
	//			{
	//				max_nollat = nolla_lkm;
	//			}
	//			//poistetaanko rivi?
	//			/*if (!(i->on_pelattavissa()))
	//			{
	//				mahdolliset_rivit.erase(i--);
	//				if (on_viimeinen)
	//				{
	//					break;
	//				}
	//			}*/
	//		}
	//	}
	//}
	// poistetaan turhat rivit
	//rivit.aktiiviset_rivit.erase(std::remove_if(rivit.aktiiviset_rivit.begin(), rivit.aktiiviset_rivit.end(), &Ristinolla::poistetaan), rivit.aktiiviset_rivit.end());

	//mahdolliset_rivit.erase(std::remove_if(mahdolliset_rivit.begin(), mahdolliset_rivit.end(), ei_pelattavissa), mahdolliset_rivit.end());
	//ja lopuksi vaihdetaan vuoroa
	vuorossa = ++vuorossa % 2;
}

//int Ristinolla::edellinen_siirto() {
//
//}

void Ristinolla::kumoa_siirto() {
	//int ruutu = edellinen_siirto();
	// jos ei kumottavaa, ei tehda mitaan
	if (siirrot.empty())
	{
		return;
	}

	int ruutu = siirrot[siirrot.size() - 1];

	// vapautetaan ruutu ja poistetaan siirtovektorista
	vapaat = lisaa_ruutu(ruutu, vapaat);
	siirrot.pop_back();

	// poistetaan risti tai nolla
	if (vuorossa == 1)
	{
		ristit.erase(std::remove(ristit.begin(), ristit.end(), ruutu), ristit.end());
	}
	else
	{
		nollat.erase(std::remove(nollat.begin(), nollat.end(), ruutu), nollat.end());
	}

	// rivit pitanee kayda lapi

	//lopuksi vaihdetaan vuoro
	vuorossa = ++vuorossa % 2;
}

void Ristinolla::aloita_alusta() {
	ristit.clear();
	nollat.clear();
	vuorossa = 0;
	max_ristit = 0;
	max_nollat = 0;
	vapaat = vapaat_ruudut(vakiot, ristit, nollat);
	//mahdolliset_rivit = pelattavat_rivit(vakiot, ristit, nollat);
	rivit = Rivit(vakiot, ristit, nollat);
}



// AI-juttuja/pelin tallennus

// onko tarvetta jarjestyksen vaihdolle?
std::vector<int> tee_siirtolista(std::vector<int> ristit, std::vector<int> nollat) {
	std::vector<int> siirrot;
	for (int i = 0; i < ristit.size() - 1; i++)
	{
		siirrot.push_back(ristit[i]);
		siirrot.push_back(nollat[i]);
	}
	siirrot.push_back(ristit[ristit.size() - 1]);
	if (ristit.size() == nollat.size())
	{
		siirrot.push_back(nollat[nollat.size() - 1]);
	}
	return siirrot;
}

std::vector<std::vector<int>> ristit_ja_nollat(std::vector<int> siirrot) {
	std::vector<int> ristit, nollat;
	for (int i = 0; i < siirrot.size(); i++)
	{
		if (i % 2 == 0) {
			ristit.push_back(siirrot[i]);
		}
		else {
			nollat.push_back(siirrot[i]);
		}
	}
	std::vector<std::vector<int>> ristit_ja_nollat;
	ristit_ja_nollat.push_back(ristit);
	ristit_ja_nollat.push_back(nollat);
	return ristit_ja_nollat;
}

PelattuPeli::PelattuPeli() {

}

PelattuPeli::PelattuPeli(int tulos, std::vector<int> ristivektori, std::vector<int> nollavektori) {
	lopputulos = tulos;
	siirrot = tee_siirtolista(ristivektori, nollavektori);
	//ristit = ristivektori;
	//nollat = nollavektori;
}


std::vector<PelattuPeli> simuloi_peleja(Vakiot vakio, int lukum) {
	std::vector<PelattuPeli> pelit;
	if (lukum < 1)
	{
		return pelit;
	}
	for (int i = 0; i < lukum; i++)
	{
		Ristinolla ristinolla(vakio, {}, {});
		bool peli_menossa = true;
		while (peli_menossa)
		{
			// valitaan satunnainen vapaa ruutu
			// parempi strategia olisi syyta keksia
			int seuraava_ruutu = ristinolla.vapaat[rand() % ristinolla.vapaat.size()];
			ristinolla.tee_siirto(seuraava_ruutu);
			if (ristinolla.risti_voitti())
			{
				PelattuPeli peli(1, ristinolla.ristit, ristinolla.nollat);
				pelit.push_back(peli);
				peli_menossa = false;
			}
			else if (ristinolla.nolla_voitti())
			{
				PelattuPeli peli(-1, ristinolla.ristit, ristinolla.nollat);
				pelit.push_back(peli);
				peli_menossa = false;
			}
			else if (ristinolla.on_ratkaisematon())
			{
				PelattuPeli peli(0, ristinolla.ristit, ristinolla.nollat);
				pelit.push_back(peli);
				peli_menossa = false;
			}
		}
		
	}

	return pelit;
}


// ja sitten bruteforce-funktio
std::vector<PelattuPeli> pelaa_kaikki_pelit(Ristinolla ristinolla, std::vector<PelattuPeli> aiemmat_pelit) {
	//std::vector<PelattuPeli> pelit;
	//Ristinolla ristinolla(ristinolla0.vakiot, ristinolla0.ristit, ristinolla0.nollat);

	// jos ei lisapelattavaa ole, tilanne on helppo
	if (ristinolla.risti_voitti())
	{
		PelattuPeli peli(1, ristinolla.ristit, ristinolla.nollat);
		aiemmat_pelit.push_back(peli);
		return aiemmat_pelit;
	}
	else if (ristinolla.nolla_voitti())
	{
		PelattuPeli peli(-1, ristinolla.ristit, ristinolla.nollat);
		aiemmat_pelit.push_back(peli);
		return aiemmat_pelit;
	}
	else if (ristinolla.on_ratkaisematon())
	{
		PelattuPeli peli(0, ristinolla.ristit, ristinolla.nollat);
		aiemmat_pelit.push_back(peli);
		return aiemmat_pelit;
	}
	
	// muuten joutuu kaymaan lapi siirtoja
	for (auto i = ristinolla.vapaat.begin(); i != ristinolla.vapaat.end(); i++)
	{
		std::vector<int> ristivektori = ristinolla.ristit;
		std::vector<int> nollavektori = ristinolla.nollat;
		ristinolla.tee_siirto(*i);
		aiemmat_pelit = pelaa_kaikki_pelit(ristinolla, aiemmat_pelit);
		//ristinolla.kumoa_siirto(*i);
		ristinolla = Ristinolla(ristinolla.vakiot, ristivektori, nollavektori);
	}
	return aiemmat_pelit;
}
