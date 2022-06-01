
#include "ai.h"
#include "ristinollapeli.h"


/*std::vector<int> priorisoi_vapaat(Ristinolla ristinolla) {
	std::vector<int> jarjestys;
	int v1 = ristinolla.vuorossa;
	int v2 = (v1 + 1) % 2;
	for (int i = ristinolla.vakiot.VIER_LKM - 1; i >= 0; i--)
	{
		if (!(ristinolla.rivien_mlkm[v1][i].empty()))
		{
			for (auto j = ristinolla.rivien_mlkm[v1][i].begin(); j != ristinolla.rivien_mlkm[v1][i].end(); j++)
			{
				std::vector<int> vapaita = ristinolla.rivit.rivit[*j].vapaat();
				for (size_t k = 0; k < vapaita.size(); k++)
				{
					auto itr = find(jarjestys.begin(), jarjestys.end(), vapaita[k]);
					if (itr == jarjestys.end())
					{
						jarjestys.push_back(vapaita[k]);
					}
				}
			}
		}
		
		if (!(ristinolla.rivien_mlkm[v2][i].empty()))
		{
			for (auto j = ristinolla.rivien_mlkm[v2][i].begin(); j != ristinolla.rivien_mlkm[v2][i].end(); j++)
			{
				std::vector<int> vapaita = ristinolla.rivit.rivit[*j].vapaat();
				for (size_t k = 0; k < vapaita.size(); k++)
				{
					auto itr = find(jarjestys.begin(), jarjestys.end(), vapaita[k]);
					if (itr == jarjestys.end())
					{
						jarjestys.push_back(vapaita[k]);
					}
				}
			}
		}
		
	}
	return jarjestys;
}

int kay_siirrot_lapi(Ristinolla ristinolla, int siirto_lkm, int nyk_arvo) {
	int vert_arvo = ristinolla.vuorossa == 1 ? INT_MAX : INT_MIN;
	for (size_t i = 0; i < ristinolla.vapaat.size(); i++)
	{
		ristinolla.tee_siirto(ristinolla.vapaat[i]);
		int tilannearvo = siirto_arvon_perusteella_r0(ristinolla, siirto_lkm - 1, nyk_arvo)[1];

		if (ristinolla.vuorossa == 0 && tilannearvo < nyk_arvo)
		{
			return tilannearvo;
		}
		if (ristinolla.vuorossa == 1 && nyk_arvo < tilannearvo)
		{
			return tilannearvo;
		}
		if (ristinolla.vuorossa == 1 && vert_arvo < tilannearvo)
		{
			vert_arvo = tilannearvo;
		}
		if (ristinolla.vuorossa == 0 && tilannearvo < vert_arvo)
		{
			vert_arvo = tilannearvo;
		}


		ristinolla.kumoa_siirto();
	}
	return vert_arvo;
}*/

// kai sita voi aloitussiirron hardcodata (jonnekin keskelle)
int aloitussiirto(Vakiot vakio) {
	return (vakio.KORKEUS / 2) * vakio.LEVEYS + vakio.LEVEYS / 2;
}

int siirto_arvon_perusteella(Ristinolla0 ristinolla) {
	int siirto = -1;

	Ristinolla0 rn(ristinolla.vakio, ristinolla.siirrot);
	int vuoro = rn.vuorossa;
	//int toinen = (rn.vuorossa + 1) % 2;
	int alkuarvo = !vuoro ? INT_MIN : INT_MAX;
	int arvo = alkuarvo;
	std::vector<int> siirrot = rn.priorisoi_ruudut();
	for (int i = 0; i < siirrot.size(); i++)
	{
		int pot_siirto = siirrot[i];
		int siirron_arvo = !vuoro ? INT_MAX : INT_MIN;
		rn.tee_siirto(pot_siirto);
		// jos tuli voitto, niin ok siirto
		if (rn.voitti().voitto)
		{
			return pot_siirto;
		}
		// muuten katsotaan vastauksia
		std::vector<int> siirrot2 = rn.priorisoi_ruudut();
		for (int j = 0; j < siirrot2.size(); j++)
		{
			rn.tee_siirto(siirrot2[j]);

			// tuliko tappio?
			if (rn.voitti().voitto)
			{
				siirron_arvo = alkuarvo;
				rn.kumoa_siirto();
				break;
				// kai tappio pitaa yrittaa estaa
				// sen voi tehda myos voittamalla
				//return siirrot2[j];

			}
			int arvo_nyt = rn.arvo();
			// jos vastustajan siirron jalkeen tilanne on huono, ei tutkita vastustajan muita vastausmahdollisuuksia
			if ((!vuoro && arvo_nyt < arvo) || vuoro && arvo < arvo_nyt)
			{
				rn.kumoa_siirto();
				siirron_arvo = arvo_nyt;
				break;
			}
			// vertaillaan muihin vastasiirtoihin
			if ((!vuoro && arvo_nyt < siirron_arvo) || (vuoro && siirron_arvo < arvo_nyt))
			{
				siirron_arvo = arvo_nyt;
			}
			rn.kumoa_siirto();
		}
		// risti (vuoro=0) maksimoi, nolla (vuoro=1) minimoi
		if ((!vuoro && siirron_arvo > arvo) || (vuoro && siirron_arvo < arvo))
		{
			arvo = siirron_arvo;
			siirto = pot_siirto;
		}
		rn.kumoa_siirto();
	}
	// jos ei sopivaa siirtoa loydy, niin valitaan joku tyhja ruutu
	if (siirto == -1)
	{
		for (int i = 0; i < ristinolla.ruudut.size(); i++)
		{
			if (ristinolla.ruudut[i] == 2)
			{
				return i;
			}
		}
	}

	return siirto;
}

// helppo algoritmi seuraavan siirron paattamiseen
//int siirto_arvon_perusteella(Ristinolla_OG ristinolla) {
//	int siirto = -1;
//	// luodaan uusi ristinolla, jolla leikkia
//	Ristinolla_OG rn(ristinolla.vakiot, ristinolla.ristit, ristinolla.nollat);
//	int vuoro = rn.vuorossa;
//	//int toinen = (rn.vuorossa + 1) % 2;
//	int alkuarvo = !vuoro ? INT_MIN : INT_MAX;
//	int arvo = alkuarvo;
//	std::vector<int> siirrot = rn.priorisoi_ruudut();
//	for (int i = 0; i < siirrot.size(); i++)
//	{
//		int pot_siirto = siirrot[i];
//		int siirron_arvo = !vuoro ? INT_MAX : INT_MIN;
//		rn.tee_siirto(pot_siirto);
//		// jos tuli voitto, niin ok siirto
//		if (rn.voitti().first)
//		{
//			return pot_siirto;
//		}
//		// muuten katsotaan vastauksia
//		std::vector<int> siirrot2 = rn.priorisoi_ruudut();
//		for (int j = 0; j < siirrot2.size(); j++)
//		{
//			rn.tee_siirto(siirrot2[j]);
//			
//			// tuliko tappio?
//			if (rn.voitti().first)
//			{
//				siirron_arvo = alkuarvo;
//				rn.kumoa_siirto();
//				break;
//				// kai tappio pitaa yrittaa estaa
//				// sen voi tehda myos voittamalla
//				//return siirrot2[j];
//				
//			}
//			int arvo_nyt = rn.arvo();
//			// jos vastustajan siirron jalkeen tilanne on huono, ei tutkita vastustajan muita vastausmahdollisuuksia
//			if ((!vuoro && arvo_nyt < arvo) || vuoro && arvo < arvo_nyt)
//			{
//				rn.kumoa_siirto();
//				siirron_arvo = arvo_nyt;
//				break;
//			}
//			// vertaillaan muihin vastasiirtoihin
//			if ((!vuoro && arvo_nyt < siirron_arvo) || (vuoro && siirron_arvo < arvo_nyt))
//			{
//				siirron_arvo = arvo_nyt;
//			}
//			rn.kumoa_siirto();
//		}
//		// risti (vuoro=0) maksimoi, nolla (vuoro=1) minimoi
//		if ((!vuoro && siirron_arvo > arvo) || (vuoro && siirron_arvo < arvo))
//		{
//			arvo = siirron_arvo;
//			siirto = pot_siirto;
//		}
//		rn.kumoa_siirto();
//	}
//	// jos ei sopivaa siirtoa loydy, niin valitaan satunnaisesti
//	if (siirto == -1)
//	{
//		return ristinolla.vapaat[rand() % ristinolla.vapaat.size()];
//	}
//	return siirto;
//}

// helppo algoritmi seuraavan siirron paattamiseen
//int siirto_arvon_perusteella(Ristinolla ristinolla) {
//	int siirto = -1;
//	// luodaan uusi ristinolla, jolla leikkia
//	Ristinolla rn(ristinolla.vakiot, ristinolla.ristit, ristinolla.nollat);
//	int toinen = (rn.vuorossa + 1) % 2;
//
//	// jos voidaan voittaa, niin voitetaan sitten
//	if (!(rn.rivien_mlkm[rn.vuorossa][rn.vakiot.VIER_LKM - 1].empty()))
//	{
//		int rivi_index = *(rn.rivien_mlkm[rn.vuorossa][rn.vakiot.VIER_LKM - 1].begin());
//		return rn.rivit.rivit[rivi_index].vapaat()[0];
//	}
//	// jos tappio haamottaa, taytyy toimia
//	if (!(rn.rivien_mlkm[toinen][rn.vakiot.VIER_LKM - 1].empty()))
//	{
//		int rivi_index = *(rn.rivien_mlkm[toinen][rn.vakiot.VIER_LKM - 1].begin());
//		return rn.rivit.rivit[rivi_index].vapaat()[0];
//	}
//	// ristipelaaja maksimoi arvoa, nollapelaaja minimoi
//	int kok_arvo = rn.vuorossa == 0 ? INT_MIN : INT_MAX;
//	for (int i = 0; i < rn.vapaat.size(); i++)
//	{
//		int vert_arvo = rn.vuorossa == 0 ? INT_MAX: INT_MIN;
//		int pot_siirto = rn.vapaat[i];
//		rn.tee_siirto(pot_siirto);
//		// katsotaan vastustajan mahdolliset siirrot
//		for (int j = 0; j < rn.vapaat.size(); j++)
//		{
//			rn.tee_siirto(rn.vapaat[j]);
//			int tilannearvo = rn.arvo();
//			if ((rn.vuorossa == 0 && tilannearvo < kok_arvo) || (rn.vuorossa == 1 && kok_arvo < tilannearvo))
//			{
//				vert_arvo = tilannearvo;
//				rn.kumoa_siirto();
//				break;
//			}
//			if ((rn.vuorossa == 0 && tilannearvo < vert_arvo) || (rn.vuorossa == 1 && vert_arvo < tilannearvo))
//			{
//				vert_arvo = tilannearvo;
//			}
//			rn.kumoa_siirto();
//		}
//		
//		rn.kumoa_siirto();
//		if ((rn.vuorossa == 0 && kok_arvo < vert_arvo) || (rn.vuorossa == 1 && vert_arvo < kok_arvo))
//		{
//			kok_arvo = vert_arvo;
//			siirto = pot_siirto;
//		}
//	}
//
//	//if (rn.vuorossa == 0)
//	//{
//	//	int maxmin = INT_MIN;
//	//	for (int i = 0; i < rn.vapaat.size(); i++)
//	//	{
//	//		int min = INT_MAX;
//	//		int pot_siirto = rn.vapaat[i];
//	//		rn.tee_siirto(pot_siirto);
//	//		// jos voitettiin, niin se siita
//	//		if (rn.merkki_lkm[0][rn.vakiot.VIER_LKM] > 0)
//	//		{
//	//			return pot_siirto;
//	//		}
//	//		// katsotaan kuinka hyva tilanne on vastustajan mahdollisten siirtojen jalkeen
//	//		for (int j = 0; j < rn.vapaat.size(); j++)
//	//		{
//	//			rn.tee_siirto(rn.vapaat[j]);
//	//			int tilannearvo = rn.arvo();
//	//			if (tilannearvo < maxmin)
//	//			{
//	//				min = tilannearvo;
//	//				rn.kumoa_siirto();
//	//				break;
//	//			}
//	//			else if (tilannearvo < min)
//	//			{
//	//				min = tilannearvo;
//	//			}
//	//			rn.kumoa_siirto();
//	//		}
//	//		if (maxmin < min)
//	//		{
//	//			maxmin = min;
//	//			siirto = pot_siirto;
//	//		}
//	//		rn.kumoa_siirto();
//	//	}
//	//}
//	//else
//	//{
//	//	int minmax = INT_MAX;
//	//	for (int i = 0; i < rn.vapaat.size(); i++)
//	//	{
//	//		int max = INT_MIN;
//	//		int pot_siirto = rn.vapaat[i];
//	//		rn.tee_siirto(pot_siirto);
//	//		// jos voitettiin, niin se siita
//	//		if (rn.merkki_lkm[1][rn.vakiot.VIER_LKM] > 0)
//	//		{
//	//			return pot_siirto;
//	//		}
//	//		// katsotaan kuinka hyva tilanne on vastustajan mahdollisten siirtojen jalkeen
//	//		for (int j = 0; j < rn.vapaat.size(); j++)
//	//		{
//	//			rn.tee_siirto(rn.vapaat[j]);
//	//			int tilannearvo = rn.arvo();
//	//			if (minmax < tilannearvo)
//	//			{
//	//				max = tilannearvo;
//	//				rn.kumoa_siirto();
//	//				break;
//	//			}
//	//			else if (max < tilannearvo)
//	//			{
//	//				max = tilannearvo;
//	//			}
//	//			rn.kumoa_siirto();
//	//		}
//	//		if (max < minmax)
//	//		{
//	//			minmax = max;
//	//			siirto = pot_siirto;
//	//		}
//	//		rn.kumoa_siirto();
//	//	}
//	//}
//	// 
//	// jos ei siirtoa saatu paatettya, valitaan se "satunnaisesti"
//	if (siirto == -1)
//	{
//		siirto = ristinolla.vapaat[rand() % ristinolla.vapaat.size()];
//	}
//	return siirto;
//}

//std::vector<int> siirto_arvon_perusteella_r(Ristinolla_OG ristinolla, int siirto_lkm) {
//	Ristinolla_OG rn(ristinolla.vakiot, ristinolla.ristit, ristinolla.nollat);
//	int alkuarvo = rn.vuorossa == 0 ? INT_MIN : INT_MAX;
//
//	std::vector<int> siirto_ja_arvo = siirto_arvon_perusteella_r0(rn, siirto_lkm, alkuarvo);
//	// jos ei loydy siirtoa, valitaan se satunnaisesti
//	if (siirto_ja_arvo[0] == -1)
//	{
//		siirto_ja_arvo[0] = ristinolla.vapaat[rand() % ristinolla.vapaat.size()];
//	}
//	return siirto_ja_arvo;
//}
//
//std::vector<int> siirto_arvon_perusteella_r0(Ristinolla_OG ristinolla, int siirto_lkm, int nyk_arvo) {
//	std::vector<int> siirto_ja_arvo = { -1, nyk_arvo };
//	if (siirto_lkm <= 0)
//	{
//		siirto_ja_arvo[1] = ristinolla.arvo();
//		return siirto_ja_arvo;
//	}
//
//	int toinen = (ristinolla.vuorossa + 1) % 2;
//	std::vector<int> jarj_vapaat = ristinolla.priorisoi_ruudut();
//	for (size_t i = 0; i < jarj_vapaat.size(); i++)
//	{
//		int vert_arvo = ristinolla.vuorossa == 0 ? INT_MAX : INT_MIN;
//		int pot_siirto = jarj_vapaat[i];
//		ristinolla.tee_siirto(pot_siirto);
//		if (ristinolla.voitti().first)
//		{
//			siirto_ja_arvo[0] = pot_siirto;
//			siirto_ja_arvo[1] = ristinolla.vuorossa == 0 ? INT_MAX : INT_MIN;
//			return siirto_ja_arvo;
//		}
//
//		std::vector<int> vapaita2 = ristinolla.priorisoi_ruudut();
//		for (size_t j = 0; j < vapaita2.size(); j++)
//		{
//			ristinolla.tee_siirto(vapaita2[j]);
//			int testi = siirto_lkm - 1;
//			std::vector<int> testivektori = siirto_arvon_perusteella_r0(ristinolla, testi, nyk_arvo);
//			//int tilannearvo = siirto_arvon_perusteella_r0(rn, testi, nyk_arvo)[1];
//			int tilannearvo = testivektori[1];
//			if ((ristinolla.vuorossa == 0 && tilannearvo < nyk_arvo) || (ristinolla.vuorossa == 1 && nyk_arvo < tilannearvo))
//			{
//				vert_arvo = tilannearvo;
//				ristinolla.kumoa_siirto();
//				break;
//			}
//			if ((ristinolla.vuorossa == 0 && tilannearvo < vert_arvo) || (ristinolla.vuorossa == 1 && vert_arvo < tilannearvo))
//			{
//				vert_arvo = tilannearvo;
//			}
//			ristinolla.kumoa_siirto();
//		}
//
//		ristinolla.kumoa_siirto();
//		if ((ristinolla.vuorossa == 0 && siirto_ja_arvo[1] < vert_arvo) || (ristinolla.vuorossa == 1 && vert_arvo < siirto_ja_arvo[1]))
//		{
//			siirto_ja_arvo[0] = pot_siirto;
//			siirto_ja_arvo[1] = vert_arvo;
//		}
//	}
//	return siirto_ja_arvo;
//}
//
//std::vector<int> siirto_arvon_perusteella_r(Ristinolla ristinolla, int siirto_lkm) {
//	Ristinolla rn(ristinolla.vakiot, ristinolla.ristit, ristinolla.nollat);
//	int alkuarvo = rn.vuorossa == 0 ? INT_MIN : INT_MAX;
//
//	std::vector<int> siirto_ja_arvo = siirto_arvon_perusteella_r0(rn, siirto_lkm, alkuarvo);
//
//	if (siirto_ja_arvo[0] == -1)
//	{
//		siirto_ja_arvo[0] = ristinolla.vapaat[rand() % ristinolla.vapaat.size()];
//	}
//	return siirto_ja_arvo;
//}
//
//std::vector<int> siirto_arvon_perusteella_r0(Ristinolla rn, int siirto_lkm, int nyk_arvo) {
//	std::vector<int> siirto_ja_arvo = { -1, nyk_arvo };
//	if (siirto_lkm <= 0)
//	{
//		siirto_ja_arvo[1] = rn.arvo();
//		return siirto_ja_arvo;
//	}
//
//	int toinen = (rn.vuorossa + 1) % 2;
//	std::vector<int> jarj_vapaat = priorisoi_vapaat(rn);
//	for (size_t i = 0; i < jarj_vapaat.size(); i++)
//	{
//		int vert_arvo = rn.vuorossa == 0 ? INT_MAX : INT_MIN;
//		int pot_siirto = jarj_vapaat[i];
//		rn.tee_siirto(pot_siirto);
//		if (rn.voitti().first)
//		{
//			siirto_ja_arvo[0] = pot_siirto;
//			siirto_ja_arvo[1] = rn.vuorossa == 0 ? INT_MAX : INT_MIN;
//			return siirto_ja_arvo;
//		}
//
//		std::vector<int> vapaita2 = priorisoi_vapaat(rn);
//		for (size_t j = 0; j < vapaita2.size(); j++)
//		{
//			rn.tee_siirto(vapaita2[j]);
//			int testi = siirto_lkm - 1;
//			std::vector<int> testivektori = siirto_arvon_perusteella_r0(rn, testi, nyk_arvo);
//			//int tilannearvo = siirto_arvon_perusteella_r0(rn, testi, nyk_arvo)[1];
//			int tilannearvo = testivektori[1];
//			if ((rn.vuorossa == 0 && tilannearvo < nyk_arvo) || (rn.vuorossa == 1 && nyk_arvo < tilannearvo))
//			{
//				vert_arvo = tilannearvo;
//				rn.kumoa_siirto();
//				break;
//			}
//			if ((rn.vuorossa == 0 && tilannearvo < vert_arvo) || (rn.vuorossa == 1 && vert_arvo < tilannearvo))
//			{
//				vert_arvo = tilannearvo;
//			}
//			rn.kumoa_siirto();
//		}
//
//		rn.kumoa_siirto();
//		if ((rn.vuorossa == 0 && siirto_ja_arvo[1] < vert_arvo) || (rn.vuorossa == 1 && vert_arvo < siirto_ja_arvo[1]))
//		{
//			siirto_ja_arvo[0] = pot_siirto;
//			siirto_ja_arvo[1] = vert_arvo;
//		}
//	}
//	return siirto_ja_arvo;
//	
//	// jos voitto saadaan yhdella siirrolla, hyvahyva
//	/*if (!(rn.rivien_mlkm[rn.vuorossa][rn.vakiot.VIER_LKM - 1].empty()))
//	{
//		int rivi_index = *rn.rivien_mlkm[rn.vuorossa][rn.vakiot.VIER_LKM - 1].begin();
//		siirto_ja_arvo[0] = rn.rivit.rivit[rivi_index].vapaat()[0];
//		siirto_ja_arvo[1] = rn.vuorossa == 0 ? INT_MAX : INT_MIN;
//		return siirto_ja_arvo;
//	}*/
//	// jos tappio haamottaa, taytyy toimia
//	//int toinen = (rn.vuorossa + 1) % 2;
//	//if (!(rn.rivien_mlkm[toinen][rn.vakiot.VIER_LKM - 1].empty()))
//	//{
//	//	int rivi_index = *(rn.rivien_mlkm[toinen][rn.vakiot.VIER_LKM - 1].begin());
//	//	int siirto = rn.rivit.rivit[rivi_index].vapaat()[0];
//	//	siirto_ja_arvo[0] = siirto;
//	//	int vert_arvo = rn.vuorossa == 0 ? INT_MAX : INT_MIN;
//	//	rn.tee_siirto(siirto);
//	//	//siirto_ja_arvo[1] = siirto_arvon_perusteella_r0(rn, siirto_lkm - 1, nyk_arvo)[1];
//	//	//siirto_ja_arvo[1] = kay_siirrot_lapi(rn, siirto_lkm - 1, nyk_arvo);
//	//	for (size_t i = 0; i < rn.vapaat.size(); i++)
//	//	{
//	//		rn.tee_siirto(rn.vapaat[i]);
//	//		int tilannearvo = siirto_arvon_perusteella_r0(rn, siirto_lkm - 1, nyk_arvo)[1];
//	//		if ((rn.vuorossa == 0 && tilannearvo < nyk_arvo) || (rn.vuorossa == 1 && nyk_arvo < tilannearvo))
//	//		{
//	//			rn.kumoa_siirto();
//	//			rn.kumoa_siirto();
//	//			siirto_ja_arvo[1] = tilannearvo;
//	//			return siirto_ja_arvo;
//	//		}
//	//		if ((rn.vuorossa == 0 && tilannearvo < vert_arvo) || (rn.vuorossa == 1 && vert_arvo < tilannearvo))
//	//		{
//	//			vert_arvo = tilannearvo;
//	//		}
//
//	//		rn.kumoa_siirto();
//	//	}
//	
//		//rn.kumoa_siirto();
//		//if ((rn.vuorossa == 0 && nyk_arvo < vert_arvo) || (rn.vuorossa == 1 && vert_arvo < nyk_arvo))
//		//{
//			//siirto_ja_arvo[1] = vert_arvo;
//		//}
//		//return siirto_ja_arvo;
//	//}
//
//	//for (size_t i = 0; i < rn.vapaat.size(); i++)
//	//{
//	//	int vert_arvo = rn.vuorossa == 0 ? INT_MAX : INT_MIN;
//	//	int pot_siirto = rn.vapaat[i];
//	//	rn.tee_siirto(pot_siirto);
//	//	// katsotaan vastustajan siirrot
//	//	for (size_t j = 0; j < rn.vapaat.size(); j++)
//	//	{
//	//		rn.tee_siirto(rn.vapaat[j]);
//	//		int tilannearvo = siirto_arvon_perusteella_r0(rn, siirto_lkm - 1, nyk_arvo)[1];
//	//		if ((rn.vuorossa == 0 && tilannearvo < nyk_arvo) || (rn.vuorossa == 1 && nyk_arvo < tilannearvo))
//	//		{
//	//			vert_arvo = tilannearvo;
//	//			rn.kumoa_siirto();
//	//			break;
//	//		}
//	//		if ((rn.vuorossa == 0 && tilannearvo < vert_arvo) || (rn.vuorossa == 1 && vert_arvo < tilannearvo))
//	//		{
//	//			vert_arvo = tilannearvo;
//	//		}
//	//		rn.kumoa_siirto();
//	//	}
//	//	
//	//	rn.kumoa_siirto();
//	//	if ((rn.vuorossa == 0 && siirto_ja_arvo[1] < vert_arvo) || (rn.vuorossa == 1 && vert_arvo < siirto_ja_arvo[1]))
//	//	{
//	//		siirto_ja_arvo[0] = pot_siirto;
//	//		siirto_ja_arvo[1] = vert_arvo;
//	//	}
//	//}
//
//	//return siirto_ja_arvo;
//}
//
//// yritetaan maarittaa tilanteen arvo tutkimalla seuraavia siirtoja
//int rekursiivinen_arvo(Ristinolla ristinolla, int siirto_lkm) {
//	if (siirto_lkm <= 0)
//	{
//		return ristinolla.arvo();
//	}
//	// risti maksimoi
//	Ristinolla rn(ristinolla.vakiot, ristinolla.ristit, ristinolla.nollat);
//	if (rn.vuorossa == 0)
//	{
//		int max = INT_MIN;
//		for (size_t i = 0; i < rn.vapaat.size(); i++)
//		{
//			int pot_siirto = rn.vapaat[i];
//			rn.tee_siirto(pot_siirto);
//			int pot_arvo = rekursiivinen_arvo(rn, siirto_lkm - 1);
//			if (max < pot_arvo)
//			{
//				max = pot_arvo;
//			}
//
//			rn.kumoa_siirto();
//		}
//		return max;
//	}
//	// nolla minimoi
//	else if (rn.vuorossa == 1)
//	{
//		int min = INT_MAX;
//		for (size_t i = 0; i < rn.vapaat.size(); i++)
//		{
//			int pot_siirto = rn.vapaat[i];
//			rn.tee_siirto(pot_siirto);
//			int pot_arvo = rekursiivinen_arvo(rn, siirto_lkm - 1);
//			if (pot_arvo < min)
//			{
//				min = pot_arvo;
//			}
//
//			rn.kumoa_siirto();
//		}
//		return min;
//	}
//}
//
//int siirto_rek_arvon_perusteella(Ristinolla ristinolla, int siirto_lkm) {
//	int siirto = -1;
//	Ristinolla rn(ristinolla.vakiot, ristinolla.ristit, ristinolla.nollat);
//	if (rn.vuorossa == 0)
//	{
//		int max = INT_MIN;
//		for (size_t i = 0; i < rn.vapaat.size(); i++)
//		{
//			int pot_siirto = rn.vapaat[i];
//			rn.tee_siirto(pot_siirto);
//			int arvo = rekursiivinen_arvo(rn, siirto_lkm);
//			if (max < arvo)
//			{
//				max = arvo;
//				siirto = pot_siirto;
//			}
//			rn.kumoa_siirto();
//		}
//	}
//
//	if (rn.vuorossa == 1)
//	{
//		int min = INT_MAX;
//		for (size_t i = 0; i < rn.vapaat.size(); i++)
//		{
//			int pot_siirto = rn.vapaat[i];
//			rn.tee_siirto(pot_siirto);
//			int arvo = rekursiivinen_arvo(rn, siirto_lkm);
//			if (arvo < min)
//			{
//				min = arvo;
//				siirto = pot_siirto;
//			}
//			rn.kumoa_siirto();
//		}
//	}
//	// jos ei siirtoa saatu paatettya, valitaan satunnaisesti
//	if (siirto == -1)
//	{
//		siirto = ristinolla.vapaat[rand() % ristinolla.vapaat.size()];
//	}
//
//	return siirto;
//}
//
//
//// onko tarvetta jarjestyksen vaihdolle?
//std::vector<int> tee_siirtolista(std::vector<int> ristit, std::vector<int> nollat) {
//	std::vector<int> siirrot;
//	for (int i = 0; i < ristit.size() - 1; i++)
//	{
//		siirrot.push_back(ristit[i]);
//		siirrot.push_back(nollat[i]);
//	}
//	siirrot.push_back(ristit[ristit.size() - 1]);
//	if (ristit.size() == nollat.size())
//	{
//		siirrot.push_back(nollat[nollat.size() - 1]);
//	}
//	return siirrot;
//}
//
//std::vector<std::vector<int>> ristit_ja_nollat(std::vector<int> siirrot) {
//	std::vector<int> ristit, nollat;
//	for (int i = 0; i < siirrot.size(); i++)
//	{
//		if (i % 2 == 0) {
//			ristit.push_back(siirrot[i]);
//		}
//		else {
//			nollat.push_back(siirrot[i]);
//		}
//	}
//	std::vector<std::vector<int>> ristit_ja_nollat;
//	ristit_ja_nollat.push_back(ristit);
//	ristit_ja_nollat.push_back(nollat);
//	return ristit_ja_nollat;
//}
//
//
//PelattuPeli::PelattuPeli() {
//
//}
//
//PelattuPeli::PelattuPeli(int tulos, std::vector<int> ristivektori, std::vector<int> nollavektori) {
//	lopputulos = tulos;
//	siirrot = tee_siirtolista(ristivektori, nollavektori);
//	//ristit = ristivektori;
//	//nollat = nollavektori;
//}
//
//
//std::vector<PelattuPeli> simuloi_peleja(Vakiot vakio, int lukum) {
//	std::vector<PelattuPeli> pelit;
//	if (lukum < 1)
//	{
//		return pelit;
//	}
//	for (int i = 0; i < lukum; i++)
//	{
//		Ristinolla ristinolla(vakio, {}, {});
//		bool peli_menossa = true;
//		while (peli_menossa)
//		{
//			// valitaan satunnainen vapaa ruutu
//			// parempi strategia olisi syyta keksia
//			int seuraava_ruutu = ristinolla.vapaat[rand() % ristinolla.vapaat.size()];
//			ristinolla.tee_siirto(seuraava_ruutu);
//			if (ristinolla.risti_voitti())
//			{
//				PelattuPeli peli(1, ristinolla.ristit, ristinolla.nollat);
//				pelit.push_back(peli);
//				peli_menossa = false;
//			}
//			else if (ristinolla.nolla_voitti())
//			{
//				PelattuPeli peli(-1, ristinolla.ristit, ristinolla.nollat);
//				pelit.push_back(peli);
//				peli_menossa = false;
//			}
//			else if (ristinolla.on_ratkaisematon())
//			{
//				PelattuPeli peli(0, ristinolla.ristit, ristinolla.nollat);
//				pelit.push_back(peli);
//				peli_menossa = false;
//			}
//		}
//
//	}
//
//	return pelit;
//}
//
//
//// ja sitten bruteforce-funktio
//std::vector<PelattuPeli> pelaa_kaikki_pelit(Ristinolla ristinolla, std::vector<PelattuPeli> aiemmat_pelit) {
//	//std::vector<PelattuPeli> pelit;
//	//Ristinolla ristinolla(ristinolla0.vakiot, ristinolla0.ristit, ristinolla0.nollat);
//
//	// jos ei lisapelattavaa ole, tilanne on helppo
//	if (ristinolla.risti_voitti())
//	{
//		PelattuPeli peli(1, ristinolla.ristit, ristinolla.nollat);
//		aiemmat_pelit.push_back(peli);
//		return aiemmat_pelit;
//	}
//	else if (ristinolla.nolla_voitti())
//	{
//		PelattuPeli peli(-1, ristinolla.ristit, ristinolla.nollat);
//		aiemmat_pelit.push_back(peli);
//		return aiemmat_pelit;
//	}
//	else if (ristinolla.on_ratkaisematon())
//	{
//		PelattuPeli peli(0, ristinolla.ristit, ristinolla.nollat);
//		aiemmat_pelit.push_back(peli);
//		return aiemmat_pelit;
//	}
//
//	// muuten joutuu kaymaan lapi siirtoja
//	for (auto i = ristinolla.vapaat.begin(); i != ristinolla.vapaat.end(); i++)
//	{
//		std::vector<int> ristivektori = ristinolla.ristit;
//		std::vector<int> nollavektori = ristinolla.nollat;
//		ristinolla.tee_siirto(*i);
//		aiemmat_pelit = pelaa_kaikki_pelit(ristinolla, aiemmat_pelit);
//		ristinolla.kumoa_siirto();
//		//ristinolla = Ristinolla(ristinolla.vakiot, ristivektori, nollavektori);
//	}
//	return aiemmat_pelit;
//}
