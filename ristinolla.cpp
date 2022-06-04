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

	for (int i = 0; i < vakio.VIER_LKM + 1; i++)
	{
		rivit_joissa_k_merkkia.push_back(std::unordered_set<int>());
	}

	ohi_on = false;
	voittaja = -1;

	// tarkastetaan mahdolliset aiemmat siirrot
	if (!aiemmat_siirrot.empty())
	{
		for (int i = 0; i < aiemmat_siirrot.size(); i++)
		{
			ruudut[aiemmat_siirrot[i]] = i % 2;
			std::vector<PaikkaRivilla> rivit_ja_paikat = missa_riveissa_ruutu_on(vakio, aiemmat_siirrot[i]);
			for (int j = 0; j < rivit_ja_paikat.size(); j++)
			{
				rivit[rivit_ja_paikat[j].rivi_id].tee_siirto(rivit_ja_paikat[j].paikka, i % 2);
			}
		}
		for (int i = 0; i < rivit.size(); i++)
		{
			if (rivit[i].on_pelattavissa)
			{
				int symbolien_maara = std::max(rivit[i].ristien_lkm, rivit[i].nollien_lkm);
				if (symbolien_maara > 0)
				{
					rivit_joissa_k_merkkia[symbolien_maara].insert(i);
				}
			}
		}
	}
	
}

void Ristinolla0::vaihda_vuoroa() {
	vuorossa = ++vuorossa % 2;
}

bool Ristinolla0::on_ratkaisematon() {
	for (int i = 0; i < rivit.size(); i++)
	{
		if (rivit[i].onko_pelattavissa())
		{
			return false;
		}
	}
	ohi_on = true;
	return true;
}

bool Ristinolla0::risti_voitti() {
	for (int i = 0; i < rivit.size(); i++)
	{
		if (rivit[i].ristien_lkm == vakio.VIER_LKM)
		{
			ohi_on = true;
			voittaja = 0;
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
			ohi_on = true;
			voittaja = 1;
			return true;
		}
	}
	return false;
}

Loppu Ristinolla0::voitti() {
	if (rivit_joissa_k_merkkia[vakio.VIER_LKM].empty())
	{
		return Loppu(false, 2);
	}
	else
	{
		if (rivit[*rivit_joissa_k_merkkia[vakio.VIER_LKM].begin()].ristien_lkm == vakio.VIER_LKM)
		{
			ohi_on = true;
			voittaja = 0;
			return Loppu(true, 0);
		}
		ohi_on = true;
		voittaja = 1;
		return Loppu(true, 1);
	}
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
		bool on_aktiivinen = rivit[rivit_ja_paikat[i].rivi_id].on_pelattavissa;
		rivit[rivit_ja_paikat[i].rivi_id].tee_siirto(rivit_ja_paikat[i].paikka, vuorossa);
		if (on_aktiivinen)
		{
			int merkkien_maara = std::max(rivit[rivit_ja_paikat[i].rivi_id].ristien_lkm, rivit[rivit_ja_paikat[i].rivi_id].nollien_lkm);
			if (merkkien_maara > 1)
			{
				rivit_joissa_k_merkkia[merkkien_maara - 1].erase(rivit_ja_paikat[i].rivi_id);
			}
			if (rivit[rivit_ja_paikat[i].rivi_id].on_pelattavissa)
			{
				rivit_joissa_k_merkkia[merkkien_maara].insert(rivit_ja_paikat[i].rivi_id);
			}
		}
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
		bool on_aktiivinen = rivit[rivit_ja_paikat[i].rivi_id].on_pelattavissa;
		rivit[rivit_ja_paikat[i].rivi_id].kumoa_siirto(rivit_ja_paikat[i].paikka, vuorossa);
		if (rivit[rivit_ja_paikat[i].rivi_id].on_pelattavissa)
		{
			int merkkien_maara = std::max(rivit[rivit_ja_paikat[i].rivi_id].ristien_lkm, rivit[rivit_ja_paikat[i].rivi_id].nollien_lkm);
			if (merkkien_maara > 0)
			{
				rivit_joissa_k_merkkia[merkkien_maara].insert(rivit_ja_paikat[i].rivi_id);
			}
			if (on_aktiivinen)
			{
				rivit_joissa_k_merkkia[merkkien_maara + 1].erase(rivit_ja_paikat[i].rivi_id);
			}
		}
		
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

	ohi_on = false;
	voittaja = -1;
	for (int i = 1; i < vakio.VIER_LKM + 1; i++)
	{
		rivit_joissa_k_merkkia[i].clear();
	}
}

int Ristinolla0::arvo() {
	// jos peli on ohi, arvo on helppo
	Loppu tulos = voitti();
	if (tulos.voitto && tulos.kenelle == 0)
	{
		return INT_MAX;
	}
	if (tulos.voitto && tulos.kenelle == 1)
	{
		return INT_MIN;
	}
	if (on_ratkaisematon())
	{
		return 0;
	}

	// muuten lasketaan
	int laskettu_arvo = 0;
	for (int merkkien_maara = vakio.VIER_LKM - 1; merkkien_maara > 0; merkkien_maara--)
	{
		for (auto& rivi_id : rivit_joissa_k_merkkia[merkkien_maara])
		{
			laskettu_arvo += pow(10, rivit[rivi_id].ristien_lkm) - (10, rivit[rivi_id].nollien_lkm);
		}
	}

	/*for (int i = 0; i < vakio.LEVEYS * vakio.KORKEUS * 4; i++)
	{
		if (rivit[i].onko_pelattavissa())
		{
			laskettu_arvo += pow(10, rivit[i].ristien_lkm) - pow(10, rivit[i].nollien_lkm);
		}
	}*/

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