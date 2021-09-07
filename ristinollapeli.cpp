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

int is_ruutu_rivilla(int i, int alkuruutu, std::string suunta, Vakiot vakio) {
	if (suunta == "A")
	{
		return alkuruutu + i * vakio.LEVEYS;
	}
	else if (suunta == "O")
	{
		return alkuruutu + i;
	}
	else if (suunta == "AO")
	{
		return alkuruutu + i + i * vakio.LEVEYS;
	}
	else if (suunta == "AV")
	{
		return alkuruutu - i + i * vakio.LEVEYS;
	}
	// pitaisiko ilmoittaa virheesta tassa kohdassa?
}


// lisataan ruutu jarjestettyyn vektoriin
std::vector<int> lisaa_ruutu(int ruutu, std::vector<int> vektori) {
	// jos vektori on tyhja, asia on helppo
	if (vektori.empty())
	{
		vektori.push_back(ruutu);
		return vektori;
	}
	// tarkastetaan aaripaat
	if (ruutu < vektori[0])
	{
		vektori.insert(vektori.begin(), ruutu);
		return vektori;
	}
	if (ruutu > vektori[vektori.size() - 1])
	{
		vektori.push_back(ruutu);
		return vektori;
	}
	// muuten joutuu kai tekemaan jotain
	int indeksi = 0;
	int lisa = (vektori.size() - 1) / 2;
	while (lisa > 0)
	{
		indeksi += lisa;
		if (ruutu < vektori[indeksi])
		{
			indeksi = indeksi - lisa;
		}
		else if (vektori[indeksi + lisa] < ruutu)
		{
			indeksi += lisa;
			break;
		}
		lisa = lisa / 2;
	}
	// joko indeksin paikalle tai seuraavalle paikalle
	//std::next(vektori.begin(), index)
	if (ruutu < vektori[indeksi])
	{
		vektori.insert(vektori.begin() + indeksi, ruutu);
		return vektori;
	}
	if (indeksi <= vektori.size() - 2)
	{
		vektori.insert(vektori.begin() + indeksi + 1, ruutu);
	}
	return vektori;
}

// etsi indeksi i siten etta vektori[i] == luku. jos ei loydy: indeksi = -1
// vektori on jarjestetty
int etsi_indeksi(int luku, std::vector<int> vektori) {
	// tyhjasta vektorista ei loydy mitaan
	if (vektori.empty())
	{
		return -1;
	}
	// katsotaan onko vektorin ulkopuolella
	if (luku < vektori[0] || luku > vektori[vektori.size() - 1])
	{
		return -1;
	}
	// muuten joutuu
	int indeksi = 0;
	int lisa = (vektori.size() - 1) / 2;
	while (lisa > 0)
	{
		//indeksi = indeksi + lisa;
		indeksi += lisa;
		if (luku == vektori[indeksi])
		{
			return indeksi;
		}
		if (luku < vektori[indeksi])
		{
			indeksi = indeksi - lisa;
		}
		else if(vektori[indeksi + lisa] <= luku)
		{
			if (vektori[indeksi + lisa] == luku)
			{
				return indeksi + lisa;
			}
			indeksi += lisa;
			break;
		}
		lisa = lisa / 2;
		
	}
	if (luku == vektori[indeksi])
	{
		return indeksi;
	}
	if (indeksi <= vektori.size() - 2)
	{
		if (luku == vektori[indeksi + 1])
		{
			return indeksi + 1;
		}
	}
	
	// jos ei loydy, palautetaan -1
	return -1;
}

// pari.second perusteella jarjestyksessa
std::vector<std::pair<int, int>> lisaa_pari_toisen_luvun_mukaan(std::pair<int, int> pari, std::vector<std::pair<int, int>> vektori) {
	// helpot tapaukset
	if (vektori.empty()) {
		vektori.push_back(pari);
		return vektori;
	}
	if (pari.second <= vektori[0].second)
	{
		vektori.insert(vektori.begin(), pari);
		return vektori;
	}
	int loppu_indeksi = vektori.size() - 1;
	if (pari.second >= vektori[loppu_indeksi].second)
	{
		vektori.push_back(pari);
		return vektori;
	}
	// muuten joudutaan katsomaan jarjestysta
	int alku_indeksi = 0;
	int lisa = loppu_indeksi / 2;
	while (lisa > 0)
	{
		alku_indeksi += lisa;
		if (pari.second == vektori[alku_indeksi].second)
		{
			vektori.insert(vektori.begin() + alku_indeksi, pari);
			return vektori;
		}
		if (pari.second < vektori[alku_indeksi].second)
		{
			loppu_indeksi = alku_indeksi;
			alku_indeksi -= lisa;
		}
		lisa = loppu_indeksi - alku_indeksi;
		lisa /= 2;
	}
	vektori.insert(vektori.begin() + alku_indeksi, pari);
	return vektori;
}

// taman voi kai joskus vasatakin????
int etsi_indeksi_toisen_luvun_mukaan(std::pair<int, int> pari, std::vector<std::pair<int, int>> vektori) {
	// jos ei loydy, palautetaan -1
	if (vektori.empty() || pari.second < vektori[0].second)
	{
		return -1;
	}
	int loppuindeksi = vektori.size() - 1;
	if (pari.second > vektori[loppuindeksi].second)
	{
		return -1;
	}
	// muuten tutkitaan
	int alkuindeksi = 0;
	int lisa = loppuindeksi / 2;
	while (lisa > 0)
	{
		alkuindeksi += lisa;
		// yhtasuuruudet pitaa muistaa ottaa huomioon!!
	}

	// jos ei loydy, saadaan -1
	return -1;
}




Rivi::Rivi() {}

Rivi::Rivi(Vakiot vakio, std::string rivin_suunta, int rivin_alkuruutu, std::vector<int> ristit, std::vector<int> nollat) {
	vakiot = vakio;
	suunta = rivin_suunta;
	//ruudut[0] = rivin_alkuruutu;
	ruudut.push_back(rivin_alkuruutu);
	// oletuksena rivissa pelkkaa tyhjaa
	status.push_back(' ');
	for (int i = 1; i < vakiot.VIER_LKM; i++)
	{
		//status[i] = ' ';
		status.push_back(' ');
		ruudut.push_back(0);
	}

	for (int i = 0; i < vakiot.VIER_LKM; i++)
	{
		// mika on rivin ruutu i?
		if (rivin_suunta == vakiot.SUUNNAT[0])  // "A"
		{
			ruudut[i] = rivin_alkuruutu + vakiot.LEVEYS * i;
		}
		else if (rivin_suunta == vakiot.SUUNNAT[1])  // "O"
		{
			ruudut[i] = rivin_alkuruutu + i;
		}
		else if (rivin_suunta == vakiot.SUUNNAT[2])  // "AO"
		{
			ruudut[i] = rivin_alkuruutu + vakiot.LEVEYS * i + i;
		}
		else if (rivin_suunta == vakiot.SUUNNAT[3])  // "AV"
		{
			ruudut[i] = rivin_alkuruutu + vakiot.LEVEYS * i - i;
		}
		// tuleeko ruutuun risti tai nolla?
		if (onko_ruudussa_risti(ruudut[i], ristit))
			{
				status[i] = vakiot.MERKIT[0];
			}
		else if (onko_ruudussa_nolla(ruudut[i], nollat)) {
				status[i] = vakiot.MERKIT[1];
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

int Rivi::merkkien_lkm(int merkki_indeksi) {
	if (merkki_indeksi == 0)
	{
		return ristien_lkm();
	}
	if (merkki_indeksi == 1)
	{
		return nollien_lkm();
	}
	// jos jotain meni pieleen, sotketaan asioita edelleen ja palautetaan -1
	return -1;
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

std::vector<int> Rivi::vapaat() {
	std::vector<int> vapaat;
	for (size_t i = 0; i < vakiot.VIER_LKM; i++)
	{
		if (status[i] == ' ')
		{
			vapaat.push_back(ruudut[i]);
		}
	}
	return vapaat;
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

Ristinolla_OG::Ristinolla_OG() {}

Ristinolla_OG::Ristinolla_OG(Vakiot vakio, std::vector<int> ristiruudut, std::vector<int> nollaruudut) {
	vakiot = vakio;
	ristit = ristiruudut;
	nollat = nollaruudut;
	vuorossa = (ristiruudut.size() + nollaruudut.size()) % 2;
	vapaat = vapaat_ruudut(vakio, ristiruudut, nollaruudut);
}

bool Ristinolla_OG::on_ratkaisematon() {
	if (vapaat.empty())
	{
		return true;
	}
	return false;
}

bool Ristinolla_OG::risti_voitti() {
	if (ristit.size() < vakiot.VIER_LKM)
	{
		return false;
	}
	// jostakin ristista lahtien pitaisi olla VIER_LKM ristia vierekkain
	for (int i = 0; i < ristit.size() - vakiot.VIER_LKM + 1; i++)
	{
		// A
		// ei voi olla alareunan lahella
		if (vakiot.KORKEUS - ristit[i] / vakiot.LEVEYS >= vakiot.VIER_LKM)
		{
			for (int j = 1; j < vakiot.VIER_LKM; j++)
			{
				if (etsi_indeksi(ristit[i] + j * vakiot.LEVEYS, ristit) == -1)
				{
					break;
				}
				else if (j == vakiot.VIER_LKM - 1)
				{
					return true;
				}
			}
		}

		// O
		// ei voi olla oikean reuna lahella
		if (vakiot.LEVEYS - ristit[i] % vakiot.KORKEUS >= vakiot.VIER_LKM)
		{
			for (int j = 1; j < vakiot.VIER_LKM; j++)
			{
				if (etsi_indeksi(ristit[i] + j, ristit) == -1)
				{
					break;
				}
				else if (j == vakiot.VIER_LKM - 1)
				{
					return true;
				}
			}
		}

		// AO
		// ei alhaalla eika oikealla
		if (vakiot.KORKEUS - ristit[i] / vakiot.LEVEYS >= vakiot.VIER_LKM && vakiot.LEVEYS - ristit[i] % vakiot.KORKEUS >= vakiot.VIER_LKM)
		{
			for (int j = 1; j < vakiot.VIER_LKM; j++)
			{
				if (etsi_indeksi(ristit[i] + j * vakiot.LEVEYS + j, ristit) == -1)
				{
					break;
				}
				else if (j == vakiot.VIER_LKM - 1)
				{
					return true;
				}
			}
		}

		// AV
		// ei vasemmalla eika alhaalla
		if (ristit[i] % vakiot.LEVEYS >= vakiot.VIER_LKM - 1 && vakiot.KORKEUS - ristit[i] / vakiot.LEVEYS >= vakiot.VIER_LKM)
		{
			for (int j = 1; j < vakiot.VIER_LKM; j++)
			{
				if (etsi_indeksi(ristit[i] + j * vakiot.LEVEYS - j, ristit) == -1)
				{
					break;
				}
				else if (j == vakiot.VIER_LKM - 1)
				{
					return true;
				}
			}
		}

	}
	return false;
}
bool Ristinolla_OG::nolla_voitti() {
	if (nollat.size() < vakiot.VIER_LKM)
	{
		return false;
	}
	for (int i = 0; i < nollat.size() - vakiot.VIER_LKM + 1; i++)
	{
		// A
		// ei voi olla alareunan lahella
		if (vakiot.KORKEUS - nollat[i] / vakiot.LEVEYS >= vakiot.VIER_LKM)
		{
			for (int j = 1; j < vakiot.VIER_LKM; j++)
			{
				if (etsi_indeksi(nollat[i] + j * vakiot.LEVEYS, nollat) == -1)
				{
					break;
				}
				else if (j == vakiot.VIER_LKM - 1)
				{
					return true;
				}
			}
		}

		// O
		// ei voi olla oikean reuna lahella
		if (vakiot.LEVEYS - nollat[i] % vakiot.KORKEUS >= vakiot.VIER_LKM)
		{
			for (int j = 1; j < vakiot.VIER_LKM; j++)
			{
				if (etsi_indeksi(nollat[i] + j, nollat) == -1)
				{
					break;
				}
				else if (j == vakiot.VIER_LKM - 1)
				{
					return true;
				}
			}
		}

		// AO
		// ei alhaalla eika oikealla
		if (vakiot.KORKEUS - nollat[i] / vakiot.LEVEYS >= vakiot.VIER_LKM && vakiot.LEVEYS - nollat[i] % vakiot.KORKEUS >= vakiot.VIER_LKM)
		{
			for (int j = 1; j < vakiot.VIER_LKM; j++)
			{
				if (etsi_indeksi(nollat[i] + j * vakiot.LEVEYS + j, nollat) == -1)
				{
					break;
				}
				else if (j == vakiot.VIER_LKM - 1)
				{
					return true;
				}
			}
		}

		// AV
		// ei vasemmalla eika alhaalla
		if (nollat[i] % vakiot.LEVEYS >= vakiot.VIER_LKM - 1 && vakiot.KORKEUS - nollat[i] / vakiot.LEVEYS >= vakiot.VIER_LKM)
		{
			for (int j = 1; j < vakiot.VIER_LKM; j++)
			{
				if (etsi_indeksi(nollat[i] + j * vakiot.LEVEYS - j, nollat) == -1)
				{
					break;
				}
				else if (j == vakiot.VIER_LKM - 1)
				{
					return true;
				}
			}
		}

	}
	return false;
}

std::pair<bool, int> Ristinolla_OG::voitti() {
	if (on_ratkaisematon())
	{
		return { false, -1 };
	}
	// edellinen vuoro: nolla
	if (vuorossa == 0)
	{
		return { nolla_voitti(), 1 };
	}
	// edellinen vuoro: risti
	return { risti_voitti(), 0 };
	//else
	//{
		//return { risti_voitti(), 0 };
	//}
}

bool Ristinolla_OG::onko_siirto_mahdollinen(int ruutu) {
	// katsotaan onko ruutu vektorissa vapaat
	if (etsi_indeksi(ruutu, vapaat) > -1)
	{
		return true;
	}
	return false;
}

void Ristinolla_OG::tee_siirto(int ruutu) {
	if (vuorossa == 0)
	{
		ristit = lisaa_ruutu(ruutu, ristit);
	}
	else
	{
		nollat = lisaa_ruutu(ruutu, nollat);
	}
	siirrot.push_back(ruutu);
	// vapaiden update
	vapaat.erase(std::remove(vapaat.begin(), vapaat.end(), ruutu), vapaat.end());
	vuorossa = ++vuorossa % 2;
}

void Ristinolla_OG::kumoa_siirto() {
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
	vuorossa = ++vuorossa % 2;
}

void Ristinolla_OG::aloita_alusta() {
	ristit.clear();
	nollat.clear();
	siirrot.clear();
	vuorossa = 0;
	vapaat = vapaat_ruudut(vakiot, ristit, nollat);
}

// tilanteen esitys
std::vector<char> Ristinolla_OG::status() {
	std::vector<char> st;
	for (int i = 0; i < vakiot.LEVEYS * vakiot.KORKEUS; i++)
	{
		if (onko_ruudussa_risti(i, ristit))
		{
			st.push_back('X');
		}
		else if (onko_ruudussa_nolla(i, nollat))
		{
			st.push_back('0');
		}
		else
		{
			st.push_back(' ');
		}
	}
	return st;
}

// {true, pos}, jos rivilla risteja, mutta ei nollia; {true, neg}, jos nollia, mutta ei risteja
std::pair<bool, int> Ristinolla_OG::merkki_lkm_rivilla(int alkuruutu, std::string suunta) {
	// jos rivi ei ole ruudukolla, saadaan false
	if (alkuruutu % vakiot.LEVEYS > vakiot.LEVEYS - vakiot.VIER_LKM && (suunta == "O" || suunta == "AO"))
	{
		return { false, 0 };
	}
	if (alkuruutu / vakiot.LEVEYS > vakiot.KORKEUS - vakiot.VIER_LKM && (suunta == "A" || suunta == "AV" || suunta == "AO"))
	{
		return { false, 0 };
	}
	if (alkuruutu % vakiot.LEVEYS < vakiot.VIER_LKM - 1 && suunta == "AV")
	{
		return { false, 0 };
	}
	// muuten joudutaan laskemaan
	unsigned short risti_lkm = 0;
	unsigned short nolla_lkm = 0;
	for (int i = 0; i < vakiot.VIER_LKM; i++)
	{
		int nyk_ruutu = is_ruutu_rivilla(i, alkuruutu, suunta, vakiot);
		// jos ruudussa on risti, ristien lukumaara kasvaa
		if (etsi_indeksi(nyk_ruutu, ristit) > -1)
		{
			risti_lkm++;
		}
		// jos ruudussa on nolla, nollien lkm kasvaa
		else if (etsi_indeksi(nyk_ruutu, nollat) > -1)
		{
			nolla_lkm++;
		}
		// jos rivilla on risteja ja nollia, ei lasketa
		if (risti_lkm > 0 && nolla_lkm > 0)
		{
			return { false, 0 };
		}
	}
	if (risti_lkm > 0)
	{
		return { true, risti_lkm };
	}
	if (nolla_lkm > 0)
	{
		return { true, -1 * nolla_lkm };
	}
	return { false, 0 };
}

int Ristinolla_OG::arvo() {
	// jos peli on ohi, arvo on helppo
	if (on_ratkaisematon())
	{
		return 0;
	}
	std::pair<bool, int> voittaja = voitti();
	if (voittaja.first)
	{
		return voittaja.second == 0 ? INT_MAX : INT_MIN;
	}

	// muuten joudutaan laskemaan
	int arvo = 0;
	// kaikki rivien alkuruudut
	for (int i = 0; i < vakiot.KORKEUS * vakiot.LEVEYS; i++)
	{
		// kaikki suunnat
		for (int j = 0; j < 4; j++)
		{
			std::pair<bool, int> merkki_lkm = merkki_lkm_rivilla(i, vakiot.SUUNNAT[j]);
			if (merkki_lkm.first)
			{
				if (merkki_lkm.second < 0)
				{
					arvo -= pow(10, -1 * merkki_lkm.second);
				}
				else {
					arvo += pow(10, merkki_lkm.second);
				}
				
			}
		}
	}
	return arvo;
}

std::pair<bool, int> Ristinolla_OG::onko_ruudun_etaisyys_pelista_pienempi(int ruutu, int ref_etaisyys) {
	int etaisyys_pelista = std::max(vakiot.KORKEUS, vakiot.LEVEYS);
	for (int i = 0; i < ristit.size(); i++)
	{
		int x_etaisyys = std::abs(ruutu % vakiot.LEVEYS - ristit[i] % vakiot.LEVEYS);
		int y_etaisyys = std::abs(ruutu / vakiot.LEVEYS - ristit[i] / vakiot.LEVEYS);
		int etaisyys = std::max(x_etaisyys, y_etaisyys);
		if (etaisyys < ref_etaisyys) {
			return { true, etaisyys };
		}
		etaisyys_pelista = std::min(etaisyys_pelista, etaisyys);
	}
	for (int i = 0; i < nollat.size(); i++)
	{
		int x_etaisyys = std::abs(ruutu % vakiot.LEVEYS - nollat[i] % vakiot.LEVEYS);
		int y_etaisyys = std::abs(ruutu / vakiot.LEVEYS - nollat[i] / vakiot.LEVEYS);
		int etaisyys = std::max(x_etaisyys, y_etaisyys);
		if (etaisyys < ref_etaisyys) {
			return { true, etaisyys };
		}
		etaisyys_pelista = std::min(etaisyys_pelista, etaisyys);
	}
	return { false, etaisyys_pelista };
}

std::vector<int> Ristinolla_OG::priorisoi_ruudut() {
	std::vector<int> priorisoidut;
	std::vector<std::pair<int, int>> ylijaama;
	for (int i = 0; i < vapaat.size(); i++)
	{
		std::pair<bool, int> eta = onko_ruudun_etaisyys_pelista_pienempi(vapaat[i], vakiot.VIER_LKM / 2 + 1);
		if (eta.first)
		{
			priorisoidut.push_back(vapaat[i]);
		}
		else
		{
			ylijaama = lisaa_pari_toisen_luvun_mukaan({vapaat[i], eta.second}, ylijaama);
		}
	}
	// jos siina oli kaikki, ei tarvi tehda muuta
	if (ylijaama.empty()) {
		return priorisoidut;
	}
	// lisataan loput (tarvitaanko kaikki??)
	int max_etaisyys = vakiot.VIER_LKM + 1;
	int indeksi = 0;
	int etaisyys = ylijaama[indeksi].second;
	while (etaisyys < max_etaisyys)
	{
		priorisoidut.push_back(ylijaama[indeksi].first);
		indeksi++;
		if (indeksi == ylijaama.size())
		{
			return priorisoidut;
		}
		etaisyys = ylijaama[indeksi].second;
	}

	return priorisoidut;
}


Ristinolla::Ristinolla() {}

Ristinolla::Ristinolla(Vakiot vakio, std::vector<int> ristiruudut, std::vector<int> nollaruudut) {
	vakiot = vakio;
	ristit = ristiruudut;
	nollat = nollaruudut;
	vuorossa = (ristiruudut.size() + nollaruudut.size()) % 2;
	vapaat = vapaat_ruudut(vakio, ristiruudut, nollaruudut);
	rivit = Rivit(vakio, ristit, nollat);
	std::map<int, int> ristir_lkm, nollar_lkm;
	merkki_lkm.push_back(ristir_lkm);
	merkki_lkm.push_back(nollar_lkm);
	std::map<int, std::set<int>> rivien_rlkm, rivien_nlkm;
	rivien_mlkm.push_back(rivien_rlkm);
	rivien_mlkm.push_back(rivien_nlkm);
	for (int i = 0; i <= vakiot.VIER_LKM; i++)
	{
		// riveja joilla i nollaa tai ristia, on aluksi 0
		merkki_lkm[0][i] = 0;
		merkki_lkm[1][i] = 0;
		rivien_mlkm[0][i] = std::set<int>({});
		rivien_mlkm[1][i] = std::set<int>({});
	}
	for (size_t i = 0; i < rivit.aktiiviset_rivit.size(); i++)
	{
		if (rivit.aktiiviset_rivit[i])
		{
			int risti_lkm = rivit.rivit[i].ristien_lkm();
			int nolla_lkm = rivit.rivit[i].nollien_lkm();
			// yksi lisaa riveja joilla on risti_lkm risteja, samoin riveja joilla nolla_lkm nollia
			merkki_lkm[0][risti_lkm]++;
			merkki_lkm[1][nolla_lkm]++;
			rivien_mlkm[0][risti_lkm].insert(i);
			rivien_mlkm[0][nolla_lkm].insert(i);
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

std::pair<bool, int> Ristinolla::voitti() {
	if (rivien_mlkm[0][vakiot.VIER_LKM].empty() && rivien_mlkm[0][vakiot.VIER_LKM].empty())
	{
		return { false, -1 };
	}
	if (!(rivien_mlkm[0][vakiot.VIER_LKM].empty()))
	{
		return { true, 0 };
	}
	if (!(rivien_mlkm[1][vakiot.VIER_LKM].empty()))
	{
		return { true, 1 };
	}
	/*if (merkki_lkm[0][vakiot.VIER_LKM] > 0)
	{
		return { true, 0 };
	}
	if (merkki_lkm[1][vakiot.VIER_LKM] > 0)
	{
		return { true, 1 };
	}
	return { false, -1 };*/
}

bool Ristinolla::risti_voitti() {
	if (rivien_mlkm[0][vakiot.VIER_LKM].empty())
	{
		return false;
	}
	return true;
	/*if (merkki_lkm[0][vakiot.VIER_LKM] > 0)
	{
		return true;
	}
	return false;*/
}

bool Ristinolla::nolla_voitti() {
	if (rivien_mlkm[1][vakiot.VIER_LKM].empty())
	{
		return false;
	}
	return true;
	/*if (merkki_lkm[1][vakiot.VIER_LKM] > 0)
	{
		return true;
	}
	return false;*/
}

bool Ristinolla::onko_siirto_mahdollinen(int ruutu) {
	if (etsi_indeksi(ruutu, vapaat) > -1) {
		return true;
	}
	return false;
}

void Ristinolla::tee_siirto(int ruutu) {
	// lisataan ruutu vektoreihin
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
	
	// rivien update
	std::vector<std::vector<int>> muokattavat = rivit.missa_riveissa_ruutu_on(ruutu);
	for (int i = 0; i < muokattavat.size(); i++)
	{
		int indeksi = muokattavat[i][0];
		rivit.rivit[indeksi].status[muokattavat[i][1]] = vakiot.MERKIT[vuorossa];
		int m_lkm = rivit.rivit[indeksi].merkkien_lkm(vuorossa);
		// onko rivi enaa aktiivinen
		if (!(rivit.rivit[indeksi].on_pelattavissa()) && rivit.aktiiviset_rivit[indeksi])
		{
			rivit.aktiiviset_rivit[indeksi] = false;
			// poistetaan rivi myos merkki_lkm summauksesta
			merkki_lkm[vuorossa][m_lkm - 1]--;
			rivien_mlkm[vuorossa][m_lkm - 1].erase(indeksi);
			// muistetaan myos toinen merkki
			int toinen = (vuorossa + 1) % 2;
			int m_lkm2 = rivit.rivit[indeksi].merkkien_lkm(toinen);
			merkki_lkm[toinen][m_lkm2]--;
			rivien_mlkm[vuorossa][m_lkm2].erase(indeksi);
		}
		// jos rivi aktiivinen
		if (rivit.aktiiviset_rivit[indeksi])
		{
			// yksi vahemman riveja, joissa m_lkm-1 merkkia, ja yksi enemman riveja, joissa m_lkm merkkia
			merkki_lkm[vuorossa][m_lkm]++;
			merkki_lkm[vuorossa][m_lkm - 1]--;
			rivien_mlkm[vuorossa][m_lkm].insert(indeksi);
			rivien_mlkm[vuorossa][m_lkm - 1].erase(indeksi);
		}
	}
	//ja lopuksi vaihdetaan vuoroa
	vuorossa = ++vuorossa % 2;
}

//int Ristinolla::edellinen_siirto() {
//
//}

void Ristinolla::kumoa_siirto() {
	// jos ei kumottavaa, ei tehda mitaan
	if (siirrot.empty())
	{
		return;
	}

	int ruutu = siirrot[siirrot.size() - 1];
	// vapautetaan ruutu ja poistetaan siirtovektorista
	vapaat = lisaa_ruutu(ruutu, vapaat);
	siirrot.pop_back();
	// poistetaan risti tai nolla (muistetaan, etta vuorossa on "vaarin")
	if (vuorossa == 1)
	{
		ristit.erase(std::remove(ristit.begin(), ristit.end(), ruutu), ristit.end());
	}
	else
	{
		nollat.erase(std::remove(nollat.begin(), nollat.end(), ruutu), nollat.end());
	}

	// rivit pitanee kayda lapi
	std::vector<std::vector<int>> muokattavat = rivit.missa_riveissa_ruutu_on(ruutu);
	for (int i = 0; i < muokattavat.size(); i++)
	{
		int indeksi = muokattavat[i][0];
		// poistettava ei ole vuorossa
		int toinen = (vuorossa + 1) % 2;
		// poistetaan merkki
		rivit.rivit[indeksi].status[muokattavat[i][1]] = ' ';
		// jos rivilla oli vain yhdenlaisia merkkeja
		if (rivit.aktiiviset_rivit[indeksi])
		{
			int m_lkm = rivit.rivit[indeksi].merkkien_lkm(toinen);
			merkki_lkm[toinen][m_lkm + 1]--;
			merkki_lkm[toinen][m_lkm]++;
			rivien_mlkm[toinen][m_lkm + 1].erase(indeksi);
			rivien_mlkm[toinen][m_lkm].insert(indeksi);
			
		}
		// jos poisto muuttaa rivin aktiiviseksi, eli siella on jaljella vain "vuorossa"-merkkeja
		else if (rivit.rivit[indeksi].on_pelattavissa()  && !(rivit.aktiiviset_rivit[indeksi]))
		{
			rivit.aktiiviset_rivit[indeksi] = true;
			merkki_lkm[toinen][0]++;
			rivien_mlkm[toinen][0].insert(indeksi);
			int m_lkm2 = rivit.rivit[indeksi].merkkien_lkm(vuorossa);
			merkki_lkm[vuorossa][m_lkm2]++;
			rivien_mlkm[vuorossa][m_lkm2].insert(indeksi);
		}
	}
	//lopuksi vaihdetaan vuoro
	vuorossa = ++vuorossa % 2;
}

void Ristinolla::aloita_alusta() {
	ristit.clear();
	nollat.clear();
	vuorossa = 0;
	vapaat = vapaat_ruudut(vakiot, ristit, nollat);
	rivit = Rivit(vakiot, ristit, nollat);
	for (int i = 0; i <= vakiot.VIER_LKM; i++)
	{
		merkki_lkm[0][i] = 0;
		merkki_lkm[1][i] = 0;
		rivien_mlkm[0][i].clear();
		rivien_mlkm[1][i].clear();
	}
}

int Ristinolla::arvo() {
	int arvo = 0;
	if (!(rivien_mlkm[0][vakiot.VIER_LKM].empty()))
	{
		return INT_MAX;
	}
	if (!(rivien_mlkm[1][vakiot.VIER_LKM].empty()))
	{
		return INT_MIN;
	}
	for (size_t i = 1; i < vakiot.VIER_LKM; i++)
	{
		int risti_rivi_lkm = rivien_mlkm[0][i].size();
		int nolla_rivi_lkm = rivien_mlkm[1][i].size();
		arvo += (risti_rivi_lkm - nolla_rivi_lkm) * pow(10, i - 1);
	}
	return arvo;

	/*if (merkki_lkm[0][vakiot.VIER_LKM] > 0)
	{
		return INT_MAX;
	}
	if (merkki_lkm[1][vakiot.VIER_LKM] > 0)
	{
		return INT_MIN;
	}
	for (int i = 1; i < vakiot.VIER_LKM; i++)
	{
		arvo += (merkki_lkm[0][i] - merkki_lkm[1][i]) * pow(10, i - 1);
	}
	return arvo;*/
}


// AI-juttuja/pelin tallennus tiedostossa ai.cpp
