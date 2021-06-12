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
	for (int i = 0; i <= vakiot.VIER_LKM; i++)
	{
		// riveja joilla i nollaa tai ristia, on aluksi 0
		merkki_lkm[0][i] = 0;
		merkki_lkm[1][i] = 0;
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
	if (merkki_lkm[0][vakiot.VIER_LKM] > 0)
	{
		return { true, 0 };
	}
	if (merkki_lkm[1][vakiot.VIER_LKM] > 0)
	{
		return { true, 1 };
	}
	return { false, -1 };
}

bool Ristinolla::risti_voitti() {
	if (merkki_lkm[0][vakiot.VIER_LKM] > 0)
	{
		return true;
	}
	return false;
}

bool Ristinolla::nolla_voitti() {
	if (merkki_lkm[1][vakiot.VIER_LKM] > 0)
	{
		return true;
	}
	return false;
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
			// muistetaan myos toinen merkki
			int toinen = (vuorossa + 1) % 2;
			int m_lkm2 = rivit.rivit[indeksi].merkkien_lkm(toinen);
			merkki_lkm[toinen][m_lkm2]--;
		}
		// jos rivi aktiivinen
		if (rivit.aktiiviset_rivit[indeksi])
		{
			// yksi vahemman riveja, joissa m_lkm-1 merkkia, ja yksi enemman riveja, joissa m_lkm merkkia
			merkki_lkm[vuorossa][m_lkm]++;
			merkki_lkm[vuorossa][m_lkm - 1]--;
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
		}
		// jos poisto muuttaa rivin aktiiviseksi, eli siella on jaljella vain "vuorossa"-merkkeja
		else if (rivit.rivit[indeksi].on_pelattavissa()  && !(rivit.aktiiviset_rivit[indeksi]))
		{
			rivit.aktiiviset_rivit[indeksi] = true;
			merkki_lkm[toinen][0]++;
			int m_lkm2 = rivit.rivit[indeksi].merkkien_lkm(vuorossa);
			merkki_lkm[vuorossa][m_lkm2]++;
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
	}
}

int Ristinolla::arvo() {
	int arvo = 0;
	if (merkki_lkm[0][vakiot.VIER_LKM] > 0)
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
	return arvo;
}



// AI-juttuja/pelin tallennus

// helppo algoritmi seuraavan siirron paattamiseen
 int siirto_arvon_perusteella(Ristinolla ristinolla) {
	 int siirto = -1;
	 // luodaan uusi ristinolla, jolla leikkia
	 Ristinolla rn(ristinolla.vakiot, ristinolla.ristit, ristinolla.nollat);
	 // ristipelaaja maksimoi arvoa, nollapelaaja minimoi
	 if (rn.vuorossa == 0)
	 {
		 int maxmin = INT_MIN;
		 for (int i = 0; i < rn.vapaat.size(); i++)
		 {
			 int min = INT_MAX;
			 int pot_siirto = rn.vapaat[i];
			 rn.tee_siirto(pot_siirto);
			 // jos voitettiin, niin se siita
			 if (rn.merkki_lkm[0][rn.vakiot.VIER_LKM] > 0)
			 {
				 return pot_siirto;
			 }
			 // katsotaan kuinka hyva tilanne on vastustajan mahdollisten siirtojen jalkeen
			 for (int j = 0; j < rn.vapaat.size(); j++)
			 {
				 rn.tee_siirto(rn.vapaat[j]);
				 int tilannearvo = rn.arvo();
				 if (tilannearvo < maxmin)
				 {
					 min = tilannearvo;
					 rn.kumoa_siirto();
					 break;
				 }
				 else if (tilannearvo < min)
				 {
					 min = tilannearvo;
				 }
				 rn.kumoa_siirto();
			 }
			 if (maxmin < min)
			 {
				 maxmin = min;
				 siirto = pot_siirto;
			 }
			 rn.kumoa_siirto();
		 }
	 }
	 else
	 {
		 int minmax = INT_MAX;
		 for (int i = 0; i < rn.vapaat.size(); i++)
		 {
			 int max = INT_MIN;
			 int pot_siirto = rn.vapaat[i];
			 rn.tee_siirto(pot_siirto);
			 // jos voitettiin, niin se siita
			 if (rn.merkki_lkm[1][rn.vakiot.VIER_LKM] > 0)
			 {
				 return pot_siirto;
			 }
			 // katsotaan kuinka hyva tilanne on vastustajan mahdollisten siirtojen jalkeen
			 for (int j = 0; j < rn.vapaat.size(); j++)
			 {
				 rn.tee_siirto(rn.vapaat[j]);
				 int tilannearvo = rn.arvo();
				 if (minmax < tilannearvo)
				 {
					 max = tilannearvo;
					 rn.kumoa_siirto();
					 break;
				 }
				 else if (max < tilannearvo)
				 {
					 max = tilannearvo;
				 }
				 rn.kumoa_siirto();
			 }
			 if (max < minmax)
			 {
				 minmax = max;
				 siirto = pot_siirto;
			 }
			 rn.kumoa_siirto();
		 }
	 }
	 // jos ei siirtoa saatu paatettya, valitaan se "satunnaisesti"
	 if (siirto == -1)
	 {
		 siirto = ristinolla.vapaat[rand() % ristinolla.vapaat.size()];
	 }
	 return siirto;
 }

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
		ristinolla.kumoa_siirto();
		//ristinolla = Ristinolla(ristinolla.vakiot, ristivektori, nollavektori);
	}
	return aiemmat_pelit;
}
