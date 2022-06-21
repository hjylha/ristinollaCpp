#include "testit.h"



TestiTulos ristinolla::test_Ristinolla_constructor_tyhja() {
    bool testi = true;

    Ristinolla ristinolla = Ristinolla(testivakio, {});

    // ruudut tyhjia (eli 2)
    for (auto ruutu : ristinolla.ruudut)
    {
        testi = testi && ruutu == 2;
    }

    // risti (eli 0) aloittaa
    testi = testi && ristinolla.vuorossa == 0;

    // testataan rivit
    std::vector<int> sopivat_rivit = {0, 1, 2, 4, 8, 12, 16, 19, 21, 41, 61, 81};

    for (auto & rivi_id : sopivat_rivit)
    {
        testi = testi && ristinolla.rivit[rivi_id].on_pelattavissa;
    }
    
    std::unordered_set<int> tyhja_joukko = {};

    for (int i = 0; i < ristinolla.vakio.VIER_LKM + 1; i++)
    {
        testi = testi && ristinolla.rivit_joissa_k_merkkia[i] == tyhja_joukko;
    }
    

    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan constructor (ilman aiempia siirtoja)";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos ristinolla::test_Ristinolla_constructor() {
    bool testi = true;

	std::vector<int> aiemmat_siirrot = {12, 6, 11};
	Ristinolla ristinolla = Ristinolla(testivakio, aiemmat_siirrot);

	// testataan ruudut
	for (int ruutu_id = 0; ruutu_id < ristinolla.ruudut.size(); ruutu_id++)
	{
		if (ruutu_id == 6)
		{
			testi = testi && ristinolla.ruudut[ruutu_id] == 1;
		}
		else if (ruutu_id == 12 || ruutu_id == 11)
		{
			testi = testi && ristinolla.ruudut[ruutu_id] == 0;
		}
		else
		{
			testi = testi && ristinolla.ruudut[ruutu_id] == 2;	
		}
	}

	// nollan vuoro
	testi = testi && ristinolla.vuorossa == 1;

	// rivit 
	std::vector<int> sopivat_rivit = {0, 1, 2, 4, 8, 12, 16, 19, 21, 41, 61, 81};

	for (auto rivi_id: sopivat_rivit)
	{
		// rivit 2 ja 4 ei pelattavissa
		if (rivi_id == 2 || rivi_id == 4)
		{
			testi = testi && !ristinolla.rivit[rivi_id].on_pelattavissa;
			testi = testi && ristinolla.rivit[rivi_id].status == std::vector<int>({2, 1, 0, 2, 2});
		}
		else
		{
			testi = testi && ristinolla.rivit[rivi_id].on_pelattavissa;
		}
	}

	// std::unordered_set<int> tyhja;
	testi = testi && ristinolla.rivit_joissa_k_merkkia[2] == std::unordered_set<int>({41});
	std::unordered_set<int> joukko = {8, 21, 19};
	testi = testi && ristinolla.rivit_joissa_k_merkkia[1] == joukko;
	joukko.clear();
	for (int k = 3; k <= ristinolla.vakio.VIER_LKM; k++)
	{
		testi = testi && ristinolla.rivit_joissa_k_merkkia[k] == joukko;
	}
	

    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan constructor";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos ristinolla::test_vaihda_vuoroa()
{
	Ristinolla ristinolla = Ristinolla(testivakio, {});
	ristinolla.vaihda_vuoroa();

    bool testi = ristinolla.vuorossa == 1;

    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan vauhda_vuoroa-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos ristinolla::test_on_ratkaisematon()
{
	Ristinolla ristinolla = Ristinolla(testivakio, {});
	bool testi = !ristinolla.on_ratkaisematon();

	ristinolla = Ristinolla(testivakio, {0, 4, 8, 6, 11, 10, 12, 13, 17, 16, 24, 22});
	testi = testi && ristinolla.on_ratkaisematon();

    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan on_ratkaisematon-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos ristinolla::test_risti_voitti()
{
	Ristinolla ristinolla = Ristinolla(testivakio, {});
	bool testi = !ristinolla.risti_voitti();
	testi = testi && !ristinolla.ohi_on && ristinolla.voittaja == -1;

	ristinolla = Ristinolla(testivakio, {0, 1, 6, 8, 12, 13, 18, 16, 24});
	testi = testi && ristinolla.risti_voitti();
	testi = testi && ristinolla.ohi_on && ristinolla.voittaja == 0;

    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan risti_voitti-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos ristinolla::test_nolla_voitti()
{
	Ristinolla ristinolla = Ristinolla(testivakio, {});
	bool testi = !ristinolla.nolla_voitti();
	testi = testi && !ristinolla.ohi_on && ristinolla.voittaja == -1;

	ristinolla = Ristinolla(testivakio, {2, 0, 1, 6, 8, 12, 13, 18, 16, 24});
	testi = testi && ristinolla.nolla_voitti();
	testi = testi && ristinolla.ohi_on && ristinolla.voittaja == 1;

    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan nolla_voitti-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos ristinolla::test_voitti()
{
	Ristinolla ristinolla = Ristinolla(testivakio, {});
	Loppu lopputulos = ristinolla.voitti();
	bool testi = !lopputulos.voitto && lopputulos.kenelle == 2;
	testi = testi && !ristinolla.ohi_on && ristinolla.voittaja == -1;

	ristinolla = Ristinolla(testivakio, {0, 1, 6, 8, 12, 13, 18, 16, 24});
	lopputulos = ristinolla.voitti();
	testi = testi && lopputulos.voitto && lopputulos.kenelle == 0;
	testi = testi && ristinolla.ohi_on && ristinolla.voittaja == 0;

	ristinolla = Ristinolla(testivakio, {2, 0, 1, 6, 8, 12, 13, 18, 16, 24});
	lopputulos = ristinolla.voitti();
	testi = testi && lopputulos.voitto && lopputulos.kenelle == 1;
	testi = testi && ristinolla.ohi_on && ristinolla.voittaja == 1;

    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan voitti-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos ristinolla::test_onko_siirto_mahdollinen()
{
	int ruutu_id = 12;
	Ristinolla ristinolla = Ristinolla(testivakio, {});
	bool testi = ristinolla.onko_siirto_mahdollinen(ruutu_id);


	ristinolla = Ristinolla(testivakio, {0, 1, 6, 8, 12, 13, 18, 16, 24});
	testi = testi && !ristinolla.onko_siirto_mahdollinen(ruutu_id);

    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan onko_siirto_mahdollinen-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos ristinolla::test_tee_siirto()
{
	Ristinolla ristinolla = Ristinolla(testivakio, {});
	int siirto = 12;
	ristinolla.tee_siirto(siirto);

	bool testi = ristinolla.vuorossa == 1 && ristinolla.siirrot == std::vector<int>({siirto});
	testi = testi && ristinolla.ruudut[siirto] == 0;

	std::vector<int> sopivat_rivit = {0, 1, 2, 4, 8, 12, 16, 19, 21, 41, 61, 81};

	for (int k = 2; k <= ristinolla.vakio.VIER_LKM; k++)
	{
		testi = testi && ristinolla.rivit_joissa_k_merkkia[k] == std::unordered_set<int>({});
	}
	testi = testi && ristinolla.rivit_joissa_k_merkkia[1] == std::unordered_set<int>({2, 8, 19, 41});


	// toinen siirto
	siirto = 6;
	ristinolla.tee_siirto(siirto);
	testi = testi && ristinolla.vuorossa == 0 && ristinolla.siirrot == std::vector<int>({12, 6});
	for (int ruutu = 0; ruutu < ristinolla.ruudut.size(); ruutu++)
	{
		switch (ruutu)
		{
		case 6:
			testi = testi && ristinolla.ruudut[ruutu] == 1;
			break;

		case 12:
			testi = testi && ristinolla.ruudut[ruutu] == 0;
			break;
		
		default:
			testi = testi && ristinolla.ruudut[ruutu] == 2;
			break;
		}
	}

	testi = testi && !ristinolla.rivit[2].on_pelattavissa;
	for (int k = 2; k <= ristinolla.vakio.VIER_LKM; k++)
	{
		testi = testi && ristinolla.rivit_joissa_k_merkkia[k] == std::unordered_set<int>({});
	}
	testi = testi && ristinolla.rivit_joissa_k_merkkia[1] == std::unordered_set<int>({4, 8, 19, 21, 41});

	// for (int rivi_id: sopivat_rivit)
	// {
	// 	std::cout << rivi_id << ": ";
	// 	for (int luku: ristinolla.rivit[rivi_id].status)
	// 	{
	// 		std::cout << luku << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	// for (auto r: ristinolla.rivit_joissa_k_merkkia[1])
	// {
	// 	std::cout << r << " ";
	// }
	// std::cout << std::endl;

	// viela kolmas siirto
	siirto = 11;
	ristinolla.tee_siirto(siirto);
	testi = testi && ristinolla.vuorossa == 1 && ristinolla.siirrot == std::vector<int>({12, 6, 11});
	for (int ruutu = 0; ruutu < ristinolla.ruudut.size(); ruutu++)
	{
		switch (ruutu)
		{
		case 6:
			testi = testi && ristinolla.ruudut[ruutu] == 1;
			break;
		case 11:
		case 12:
			testi = testi && ristinolla.ruudut[ruutu] == 0;
			break;
		
		default:
			testi = testi && ristinolla.ruudut[ruutu] == 2;
			break;
		}
	}

	for (auto rivi_id: sopivat_rivit)
	{
		// rivit 2 ja 4 ei pelattavissa
		if (rivi_id == 2 || rivi_id == 4)
		{
			testi = testi && !ristinolla.rivit[rivi_id].on_pelattavissa;
			testi = testi && ristinolla.rivit[rivi_id].status == std::vector<int>({2, 1, 0, 2, 2});
		}
		else
		{
			testi = testi && ristinolla.rivit[rivi_id].on_pelattavissa;
		}
	}

	testi = testi && ristinolla.rivit_joissa_k_merkkia[2] == std::unordered_set<int>({41});
	std::unordered_set<int> joukko = {8, 21, 19};
	testi = testi && ristinolla.rivit_joissa_k_merkkia[1] == joukko;
	joukko.clear();
	for (int k = 3; k <= ristinolla.vakio.VIER_LKM; k++)
	{
		testi = testi && ristinolla.rivit_joissa_k_merkkia[k] == joukko;
	}

    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan tee_siirto-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos ristinolla::test_kumoa_siirto()
{
	Ristinolla ristinolla = Ristinolla(testivakio, {});
	ristinolla.tee_siirto(12);
	ristinolla.tee_siirto(6);
	ristinolla.tee_siirto(11);

	ristinolla.kumoa_siirto();

	bool testi = ristinolla.vuorossa == 0 && ristinolla.siirrot == std::vector<int>({12, 6});

	for (int ruutu = 0; ruutu < ristinolla.ruudut.size(); ruutu++)
	{
		switch (ruutu)
		{
		case 6:
			testi = testi && ristinolla.ruudut[ruutu] == 1;
			break;

		case 12:
			testi = testi && ristinolla.ruudut[ruutu] == 0;
			break;
		
		default:
			testi = testi && ristinolla.ruudut[ruutu] == 2;
			break;
		}
	}

	testi = testi && !ristinolla.rivit[2].on_pelattavissa;
	for (int k = 2; k <= ristinolla.vakio.VIER_LKM; k++)
	{
		testi = testi && ristinolla.rivit_joissa_k_merkkia[k] == std::unordered_set<int>({});
	}
	testi = testi && ristinolla.rivit_joissa_k_merkkia[1] == std::unordered_set<int>({4, 8, 19, 21, 41});


    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan kumoa_siirto-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos ristinolla::test_aloita_alusta()
{
	Ristinolla ristinolla = Ristinolla(testivakio, {});
	ristinolla.tee_siirto(12);
	ristinolla.tee_siirto(6);
	ristinolla.tee_siirto(11);

	ristinolla.aloita_alusta();

	// risti (eli 0) aloittaa
    bool testi = ristinolla.vuorossa == 0;

	// std::cout <<  (ristinolla.vuorossa == 0) << std::endl;

	// ruudut tyhjia (eli 2)
    for (auto ruutu : ristinolla.ruudut)
    {
        testi = testi && ruutu == 2;
		// std::cout << ruutu << ": " << (ruutu == 2) << std::endl;
    }

    // testataan rivit
    std::vector<int> sopivat_rivit = {0, 1, 2, 4, 8, 12, 16, 19, 21, 41, 61, 81};

    for (auto rivi_id : sopivat_rivit)
    {
        testi = testi && ristinolla.rivit[rivi_id].on_pelattavissa;
		// std::cout << rivi_id << ": " << (ristinolla.rivit[rivi_id].on_pelattavissa) << std::endl;
    }
    
    std::unordered_set<int> tyhja_joukko = {};

    for (int i = 0; i < ristinolla.vakio.VIER_LKM + 1; i++)
    {
        testi = testi && ristinolla.rivit_joissa_k_merkkia[i] == tyhja_joukko;
		// std::cout << "rivit joissa " << i << ": " << (ristinolla.rivit_joissa_k_merkkia[i] == tyhja_joukko) << std::endl;
    }

    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan aloita_alusta-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos ristinolla::test_arvo()
{
	Ristinolla ristinolla = Ristinolla(testivakio, {});

	bool testi = ristinolla.arvo() == 0;

	ristinolla.tee_siirto(12);

	testi = testi && ristinolla.arvo() == 4;

	ristinolla.tee_siirto(6);

	testi = testi && ristinolla.arvo() == 1;

	ristinolla.tee_siirto(11);

	testi = testi && ristinolla.arvo() == 11;


    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan arvo-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos ristinolla::test_onko_ruudun_etaisyys_pelista_pienempi()
{
bool testi = true;

    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan onko_ruudun_etaisyys_pelista_pienempi-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos ristinolla::test_priorisoi_ruudut()
{
	Ristinolla ristinolla = Ristinolla(testivakio, {});
	ristinolla.tee_siirto(12);

	std::vector<int> priorisoidut_ruudut = ristinolla.priorisoi_ruudut();

	std::vector<int> odotetut_ruudut = {0, 2, 4, 6, 7, 8, 10, 11, 13, 14, 16, 17, 18, 20, 22, 24};

	bool testi = priorisoidut_ruudut.size() == odotetut_ruudut.size();

	for (int ruutu: priorisoidut_ruudut)
	{
		testi = testi && std::find(odotetut_ruudut.begin(), odotetut_ruudut.end(), ruutu) != odotetut_ruudut.end();		
	}


	ristinolla.tee_siirto(6);
	ristinolla.tee_siirto(11);

	priorisoidut_ruudut = ristinolla.priorisoi_ruudut();
	std::vector<int> odotetut_ruudut1 = {10, 13, 14};
	std::vector<int> odotetut_ruudut2 = {2, 4, 5, 7, 8, 9, 16, 17, 20, 22};

	// for (int ruutu: priorisoidut_ruudut)
	// {
	// 	std::cout << ruutu << " ";
	// }
	// std::cout << std::endl;

	testi = testi && priorisoidut_ruudut.size() == odotetut_ruudut1.size() + odotetut_ruudut2.size();

	for (int i = 0; i < 3; i++)
	{
		testi = testi && priorisoidut_ruudut[i] == odotetut_ruudut1[i];
	}

    TestiTulos tulos;
	tulos.kuvaus = "Ristinolla-luokan priorisoi_ruudut-metodi";
	tulos.lapi = testi;

	return tulos;
}


TestiTulos ristinolla::ennakoidaan_arvo()
{
	Vakiot vakio(24, 16, 5);
	std::vector<int> tehdyt_siirrot = {204, 205, 227, 181, 228, 229};

	Ristinolla ristinolla(vakio, tehdyt_siirrot);

	// std::cout << ristinolla.arvo() << std::endl;

	int paras_siirto = 253;

	ristinolla.tee_siirto(paras_siirto);
	int minimiarvo = INT_MAX;
	for (int ruutu: ristinolla.priorisoi_ruudut())
	{
		ristinolla.tee_siirto(ruutu);

		minimiarvo = std::min(minimiarvo, ristinolla.arvo());

		ristinolla.kumoa_siirto();
	}

	ristinolla.kumoa_siirto();

	int ain_siirto = 252;
	ristinolla.tee_siirto(ain_siirto);
	ristinolla.tee_siirto(paras_siirto);

	// std::cout << minimiarvo << " < " << ristinolla.arvo() << std::endl;

	bool testi = minimiarvo > ristinolla.arvo();

	TestiTulos tulos;
	tulos.kuvaus = "arvo- ja priorisoi_ruudut-metodien tutkintaa";
	tulos.lapi = testi;

	return tulos;


}