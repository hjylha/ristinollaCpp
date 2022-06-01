#include "ristinolla.h"


Loppu::Loppu(bool onko_voitettu, int kuka_on_voittanut) {
	voitto = onko_voitettu;
	kenelle = kuka_on_voittanut;
}

Ristinolla0::Ristinolla0() {

}

Ristinolla0::Ristinolla0(Vakiot vakiot, std::vector<int> aiemmat_siirrot)
	: vakio(vakiot)
{
	for (int i = 0; i < vakio.LEVEYS * vakio.KORKEUS; i++)
	{
		ruudut.push_back(2);
	}
	//siirrot = aiemmat_siirrot;
	vuorossa = aiemmat_siirrot.size() % 2;
	for (int i = 0; i < vakio.LEVEYS * vakio.KORKEUS * 4; i++)
	{
		rivit.push_back(Rivi(vakio, i));
	}
	for (int i = 0; i < aiemmat_siirrot.size(); i++)
	{
		ruudut[aiemmat_siirrot[i]] = i % 2;
		std::vector<PaikkaRivilla> rivit_ja_paikat = missa_riveissa_ruutu_on(vakio, aiemmat_siirrot[i]);
		for (int j = 0; j < rivit_ja_paikat.size(); j++)
		{
			rivit[rivit_ja_paikat[j].rivi_id].tee_siirto(rivit_ja_paikat[j].paikka, i % 2);
		}
	}
}

void Ristinolla0::vaihda_vuoroa() {
	vuorossa = ++vuorossa % 2;
}

bool Ristinolla0::on_ratkaisematon() {
	for (int i = 0; i < rivit.size(); i++)
	{
		if (rivit[i].on_pelattavissa())
		{
			return false;
		}
	}
	return true;
}

bool Ristinolla0::risti_voitti() {
	for (int i = 0; i < rivit.size(); i++)
	{
		if (rivit[i].ristien_lkm == vakio.VIER_LKM)
		{
			return true;
		}
	}
	return false;
}

bool Ristinolla0::nolla_voitti() {
	for (int i = 0; i < rivit.size(); i++)
	{
		if (rivit[i].nollien_lkm == vakio.VIER_LKM)
		{
			return true;
		}
	}
	return false;
}

Loppu Ristinolla0::voitti() {
	if (on_ratkaisematon())
	{
		return { false, 2 };
	}
	// edellinen vuoro: nolla
	if (vuorossa == 0)
	{
		return { nolla_voitti(), 1 };
	}
	// edellinen vuoro: risti
	return { risti_voitti(), 0 };
}

bool Ristinolla0::onko_siirto_mahdollinen(int ruutu) {
	if (ruudut[ruutu] == 2)
	{
		return true;
	}
	return false;
}

void Ristinolla0::tee_siirto(int ruutu) {
	ruudut[ruutu] = vuorossa;
	siirrot.push_back(ruutu);
	std::vector<PaikkaRivilla> rivit_ja_paikat = missa_riveissa_ruutu_on(vakio, ruutu);
	for (int i = 0; i < rivit_ja_paikat.size(); i++)
	{
		rivit[rivit_ja_paikat[i].rivi_id].tee_siirto(rivit_ja_paikat[i].paikka, vuorossa);
	}

	vaihda_vuoroa();
}

void Ristinolla0::kumoa_siirto() {
	// jos ei kumottavaa, ei tehda mitaan
	if (siirrot.empty())
	{
		return;
	}

	int edellinen_ruutu = siirrot[siirrot.size() - 1];
	siirrot.pop_back();
	ruudut[edellinen_ruutu] = 2;

	std::vector<PaikkaRivilla> rivit_ja_paikat = missa_riveissa_ruutu_on(vakio, edellinen_ruutu);
	for (int i = 0; i < rivit_ja_paikat.size(); i++)
	{
		rivit[rivit_ja_paikat[i].rivi_id].kumoa_siirto(rivit_ja_paikat[i].paikka, vuorossa);
	}

	vaihda_vuoroa();
}

void Ristinolla0::aloita_alusta() {
	siirrot.clear();
	vuorossa = 0;
	for (int i = 0; i < ruudut.size(); i++)
	{
		ruudut[i] = 2;
	}
	for (int i = 0; i < vakio.LEVEYS * vakio.KORKEUS * 4; i++)
	{
		rivit[i].tyhjenna();
	}
}

int Ristinolla0::arvo() {
	// jos peli on ohi, arvo on helppo
	if (on_ratkaisematon())
	{
		return 0;
	}
	// risti maksimoi
	if (risti_voitti())
	{
		return INT_MAX;
	}
	// nolla minimoi
	if (nolla_voitti())
	{
		return INT_MIN;
	}

	// muuten lasketaan
	int laskettu_arvo = 0;
	for (int i = 0; i < vakio.LEVEYS * vakio.KORKEUS * 4; i++)
	{
		if (rivit[i].on_pelattavissa())
		{
			laskettu_arvo += pow(10, rivit[i].ristien_lkm) - pow(10, rivit[i].nollien_lkm);
		}
	}

	return laskettu_arvo;
}

std::pair<bool, int> Ristinolla0::onko_ruudun_etaisyys_pelista_pienempi(int ruutu, int ref_etaisyys) {
	int etaisyys_pelista = std::max(vakio.KORKEUS, vakio.LEVEYS);
	for (int i = 0; i < siirrot.size(); i++)
	{
		int x_etaisyys = std::abs(ruutu % vakio.LEVEYS - siirrot[i] % vakio.LEVEYS);
		int y_etaisyys = std::abs(ruutu / vakio.LEVEYS - siirrot[i] / vakio.LEVEYS);
		int etaisyys = std::max(x_etaisyys, y_etaisyys);
		if (etaisyys < ref_etaisyys) {
			return { true, etaisyys };
		}
		etaisyys_pelista = std::min(etaisyys_pelista, etaisyys);
	}
	return { false, etaisyys_pelista };
}

std::vector<int> Ristinolla0::priorisoi_ruudut() {
	std::vector<int> priorisoidut;
	std::vector<int> ylijaama;
	
	for (int i = 0; i < ruudut.size(); i++)
	{
		if (ruudut[i] == 2)
		{
			std::pair<bool, int> eta = onko_ruudun_etaisyys_pelista_pienempi(i, vakio.VIER_LKM / 2 + 1);
			if (eta.first)
			{
				priorisoidut.push_back(i);
			}
			else
			{
				ylijaama.push_back(i);
			}

		}
	}

	// jos siina oli kaikki, ei tarvi tehda muuta
	if (ylijaama.empty()) {
		return priorisoidut;
	}
	// lisataan loput (tarvitaanko kaikki??)
	for (int i = 0; i < ylijaama.size(); i++)
	{
		priorisoidut.push_back(ylijaama[i]);
	}

	return priorisoidut;

}