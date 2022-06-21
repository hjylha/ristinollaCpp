
#include "ai.h"




// kai sita voi aloitussiirron hardcodata (jonnekin keskelle)
int aloitussiirto(Vakiot vakio) {
	return (vakio.KORKEUS / 2) * vakio.LEVEYS + vakio.LEVEYS / 2;
}

int siirto_arvon_perusteella(Ristinolla0 ristinolla) {
	int siirto = -1;

	if (!ristinolla.rivit_joissa_k_merkkia[ristinolla.vakio.VIER_LKM - 1].empty())
	{
		return ristinolla.rivit[*ristinolla.rivit_joissa_k_merkkia[ristinolla.vakio.VIER_LKM - 1].begin()].vapaat_ruudut()[0];
	}

	Ristinolla0 rn(ristinolla.vakio, ristinolla.siirrot);
	int vuoro = rn.vuorossa;
	//int toinen = (rn.vuorossa + 1) % 2;
	int alkuarvo = !vuoro ? INT_MIN : INT_MAX;
	int arvo = alkuarvo;
	std::vector<int> mahdolliset_siirrot = rn.priorisoi_ruudut();
	for (int i = 0; i < mahdolliset_siirrot.size(); i++)
	{
		int pot_siirto = mahdolliset_siirrot[i];
		int siirron_arvo = !vuoro ? INT_MAX : INT_MIN;
		rn.tee_siirto(pot_siirto);
		// jos tuli voitto, niin ok siirto
		if (rn.voitti().voitto)
		{
			return pot_siirto;
		}
		// muuten katsotaan vastauksia
		std::vector<int> mahdolliset_siirrot2 = rn.priorisoi_ruudut();
		for (int j = 0; j < mahdolliset_siirrot2.size(); j++)
		{
			rn.tee_siirto(mahdolliset_siirrot2[j]);

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

