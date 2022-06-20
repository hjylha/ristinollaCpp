#include "testit.h"



Vakiot testivakio = Vakiot(5, 5, 5);


TestiTulos setup::test_vakiot() {
	Vakiot oletusvakio = Vakiot();
	bool oletustesti = oletusvakio.LEVEYS == 3 && oletusvakio.KORKEUS == 3 && oletusvakio.VIER_LKM == 3;
	int leveys = 35;
	int korkeus = 17;
	int vier_lkm = 5;
	Vakiot vakio = Vakiot(leveys, korkeus, vier_lkm);
	bool toinen_testi = vakio.LEVEYS == leveys && vakio.KORKEUS == korkeus && vakio.VIER_LKM == vier_lkm;
	TestiTulos tulos;
	tulos.kuvaus = "Vakiot-structin constructor";
	tulos.lapi = oletustesti && toinen_testi;
	return tulos;
}

TestiTulos setup::test_paikkarivilla() {
	int rivin_id = 538;
	int paikka_indeksi = 7;
	PaikkaRivilla paikka_rivilla = PaikkaRivilla(rivin_id, paikka_indeksi);

	bool testi = paikka_rivilla.rivi_id == rivin_id && paikka_rivilla.paikka == paikka_indeksi;

	TestiTulos tulos;
	tulos.kuvaus = "PaikkaRivilla-structin constructor";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos setup::test_sopiiko_rivi() {
	int leveys = 24;
	int korkeus = 16;
	int vier_lkm = 5;
	Vakiot vakio = Vakiot(leveys, korkeus, vier_lkm);

	int ruutu_ja_suunta = -1;
	bool virhetesti = !sopiiko_rivi(ruutu_ja_suunta, vakio);

	// testataan vasemmasta ylakulmasta lahtevia riveja
	// alas vasemmalle kulkeva rivi ei sovi
	ruutu_ja_suunta = 3;  
	bool vasen_ylakulma_testi = !sopiiko_rivi(ruutu_ja_suunta, vakio);
	// muut sopivat
	for (int rs = 0; rs < 3; rs++)
	{
		vasen_ylakulma_testi = vasen_ylakulma_testi && sopiiko_rivi(rs, vakio);
	}

	// oikeasta ylakulmasta lahtevat rivit
	int ruutu = leveys - 1;
	// alas ja alavasemmalle kulkevat rivit sopivat
	bool oikea_ylakulma_testi = sopiiko_rivi(ruutu * 4 + alas, vakio) && sopiiko_rivi(ruutu * 4 + alasvasemmalle, vakio);
	// oikealle ja alaoikealle kulkevat rivit eivat sovi
	oikea_ylakulma_testi = oikea_ylakulma_testi && !sopiiko_rivi(ruutu * 4 + oikealle, vakio) && !sopiiko_rivi(ruutu * 4 + alasoikealle, vakio);
	
	// vasemmasta alakulmasta lahtevat rivit
	ruutu = leveys * (korkeus - 1);
	// oikealle kulkeva rivi sopii, muut eivat
	bool vasen_alakulma_testi = true;
	for (int suunta = 0; suunta < 4; suunta++)
		{
		if (suunta == oikealle)
		{
			vasen_alakulma_testi = vasen_alakulma_testi && sopiiko_rivi(ruutu * 4 + suunta, vakio);
		}
		else
		{
			vasen_alakulma_testi = vasen_alakulma_testi && !sopiiko_rivi(ruutu * 4 + suunta, vakio);
		}
			
		}
	
	// oikeasta alakulmasta lahtevat rivit eivat sovi
	ruutu = leveys * korkeus - 1;
	bool oikea_alakulma_testi = true;
	for (int suunta = 0; suunta < 4; suunta++)
	{
		vasen_alakulma_testi = vasen_alakulma_testi && !sopiiko_rivi(ruutu * 4 + suunta, vakio);
	}



	TestiTulos tulos;
	tulos.kuvaus = "sopiiko_rivi-funktio";
	tulos.lapi = virhetesti && vasen_ylakulma_testi && oikea_ylakulma_testi && vasen_alakulma_testi && oikea_alakulma_testi;

	return tulos;

}

TestiTulos setup::test_is_ruutu_rivilla() {
	// int leveys = 5;
	// int korkeus = 5;
	// int vier_lkm = 5;
	// Vakiot vakio = Vakiot(leveys, korkeus, vier_lkm);

	bool testi = true;

	int ruutu = 0;
	suunnat suunta = alas;
	for (int i = 1; i < 4; i++)
	{
		bool alatesti = is_ruutu_rivilla(0, ruutu * 4 + i, testivakio) == ruutu;
		testi = testi && alatesti;
		if (!alatesti)
		{
			std::cout << "nollaindeksi FAIL, suunta " << i << std::endl;
		}
	}

	bool alatesti = is_ruutu_rivilla(1, oikealle, testivakio) == 1;
	testi = testi && alatesti;
	if (!alatesti) 
	{
		std::cout << "nollasta 1 oikealle FAIL: ei ole 1" << std::endl;
	}
	alatesti = is_ruutu_rivilla(2, alasoikealle, testivakio) == 12;
	testi = testi && alatesti;
	if (!alatesti) 
	{
		std::cout << "nollasta 2 alaoikealle FAIL: ei ole 12" << std::endl;
	}

	alatesti = is_ruutu_rivilla(3, 4*4 + alasvasemmalle, testivakio) == 16;
	if (!alatesti) 
	{
		std::cout << "oikeasta ylakulmasta (4) 3 alavasemmalle FAIL: ei ole 16" << std::endl;
	}
	testi = testi && alatesti;

	TestiTulos tulos;
	tulos.kuvaus = "is_ruutu_rivilla-funktio";
	tulos.lapi = testi;

	return tulos;
}


TestiTulos setup::test_rivi_constructor() {
	// int leveys = 5;
	// int korkeus = 5;
	// int vier_lkm = 5;
	// Vakiot vakio = Vakiot(leveys, korkeus, vier_lkm);

	std::vector<int> sopivat_rivit = {0, 1, 2, 4, 8, 12, 16, 19, 21, 41, 61, 81};

	bool testi = true;

	std::vector<Rivi> rivit;

	// testataan sopivuus
	for (int i = 0; i < testivakio.LEVEYS * testivakio.KORKEUS * 4; i++)
	{
		Rivi testirivi = Rivi(testivakio, i);
		rivit.push_back(testirivi);
		if (std::find(sopivat_rivit.begin(), sopivat_rivit.end(), i) == sopivat_rivit.end())
		{
			testi = testi && !testirivi.on_pelattavissa;
		}
		else{
			testi = testi && testirivi.on_pelattavissa;
		}
	}

	// testataan status
	std::vector<int> odotettu_status = {2, 2, 2, 2, 2};
	for (auto &rivinro: sopivat_rivit)
	{
		testi = testi && rivit[rivinro].status == odotettu_status;
	}

	// testataan diagonaalirivien ruudut
	std::vector<int> diagonaali1 = {0, 6, 12, 18, 24};
	testi = testi && rivit[2].ruudut == diagonaali1;

	std::vector<int> diagonaali2 = {4, 8, 12, 16, 20};
	testi = testi && rivit[19].ruudut == diagonaali2;

	testi = testi && rivit[8].ristien_lkm == 0 && rivit[41].nollien_lkm == 0;
	

	TestiTulos tulos;
	tulos.kuvaus = "Rivi-luokan constructor";
	tulos.lapi = testi;

	return tulos;
}


TestiTulos setup::test_laske_ristien_lkm()
{
	Rivi testirivi = Rivi(testivakio, 2);

	bool testi = true;

	// aluksi rivi on tyhja
	testi = testi && testirivi.laske_ristien_lkm() == 0;

	// lisataan risti
	testirivi.status[0] = 0;

	testi = testi && testirivi.laske_ristien_lkm() == 1;

	// lisataan toinen risti
	testirivi.status[1] = 0;

	testi = testi && testirivi.laske_ristien_lkm() == 2;

	TestiTulos tulos;
	tulos.kuvaus = "Rivi-luokan laske_ristien_lkm-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos setup::test_laske_nollien_lkm()
{
	Rivi testirivi = Rivi(testivakio, 61);

	bool testi = true;

	// aluksi rivi on tyhja
	testi = testi && testirivi.laske_nollien_lkm() == 0;

	// lisataan risti
	testirivi.status[0] = 1;

	testi = testi && testirivi.laske_nollien_lkm() == 1;

	// lisataan toinen risti
	testirivi.status[1] = 1;

	testi = testi && testirivi.laske_nollien_lkm() == 2;

	TestiTulos tulos;
	tulos.kuvaus = "Rivi-luokan laske_nollien_lkm-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos setup::test_onko_pelattavissa() {
	bool testi = true;

	Rivi testirivi = Rivi(testivakio, 41);

	// aluksi on pelattavissa
	testi = testi && testirivi.onko_pelattavissa() && testirivi.on_pelattavissa;

	// testirivi.status[0] = 1;
	// testirivi.status[1] = 0;
	testirivi.ristien_lkm = 1;
	testirivi.nollien_lkm = 1;

	testi = testi && !testirivi.onko_pelattavissa();


	TestiTulos tulos;
	tulos.kuvaus = "Rivi-luokan onko_pelattavissa-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos setup::test_tee_siirto() {
	bool testi = true;
	Rivi testirivi = Rivi(testivakio, 12);

	int paikka = 0;
	int symboli = 0;
	testirivi.tee_siirto(paikka, symboli);

	testi = testi && testirivi.ristien_lkm == 1 && testirivi.status[paikka] == symboli;
	
	paikka = 1;
	symboli = 1;
	testirivi.tee_siirto(paikka, symboli);

	testi = testi && testirivi.nollien_lkm == 1 && testirivi.status[paikka] == symboli;

	// ei enaa pelattavissa
	testi = testi && !testirivi.on_pelattavissa;

	TestiTulos tulos;
	tulos.kuvaus = "Rivi-luokan tee_siirto-metodi";
	tulos.lapi = testi;

	return tulos;
}

TestiTulos setup::test_kumoa_siirto() {
	bool testi = true;
	Rivi testirivi = Rivi(testivakio, 12);

	int paikka1 = 0;
	int symboli1 = 0;
	testirivi.tee_siirto(paikka1, symboli1);
	// tehdaan toinenkin siirto kun kerran siirrellaan...
	int paikka2 = 1;
	int symboli2 = 1;
	testirivi.tee_siirto(paikka2, symboli2);

	testi = testi && !testirivi.on_pelattavissa;

	// kumous ei tapahdu silla vuorolla jota kumotaan
	testirivi.kumoa_siirto(paikka1, symboli2);

	testi = testi && testirivi.status[paikka1] == 2 && testirivi.status[paikka2] == symboli2;
	// kumoa tekee
	testi = testi && testirivi.ristien_lkm == 0 && testirivi.nollien_lkm == 1;
	testi = testi && testirivi.on_pelattavissa;

	TestiTulos tulos;
	tulos.kuvaus = "Rivi-luokan kumoa_siirto-metodi";
	tulos.lapi = testi;

	return tulos;	
}

TestiTulos setup::test_tyhjenna() {
	bool testi = true;
	Rivi testirivi = Rivi(testivakio, 81);

	int paikka1 = 0;
	int symboli1 = 0;
	testirivi.tee_siirto(paikka1, symboli1);
	int paikka2 = 1;
	int symboli2 = 1;
	testirivi.tee_siirto(paikka2, symboli2);

	testirivi.tyhjenna();

	std::vector<int> odotettu_status = {2, 2, 2, 2, 2};
	testi = testi && testirivi.status == odotettu_status && testirivi.on_pelattavissa;
	testi = testi && testirivi.ristien_lkm == 0 && testirivi.nollien_lkm == 0;

	TestiTulos tulos;
	tulos.kuvaus = "Rivi-luokan tyhjenna-metodi";
	tulos.lapi = testi;

	return tulos;	
}

TestiTulos setup::test_vapaat_ruudut() {
	bool testi = true;
	Rivi testirivi = Rivi(testivakio, 2);

	int paikka1 = 0;
	int symboli1 = 0;
	testirivi.tee_siirto(paikka1, symboli1);
	int paikka2 = 1;
	int symboli2 = 1;
	testirivi.tee_siirto(paikka2, symboli2);

	std::vector<int> odotetut_vapaat = {12, 18, 24};

	testi = testi && testirivi.vapaat_ruudut() == odotetut_vapaat;



	TestiTulos tulos;
	tulos.kuvaus = "Rivi-luokan vapaat_ruudut-metodi";
	tulos.lapi = testi;

	return tulos;
}

bool vertaa_PaikkaRivilla(PaikkaRivilla paikka1, PaikkaRivilla paikka2) {
	if (paikka1.paikka == paikka2.paikka && paikka1.rivi_id == paikka2.rivi_id)
	{
		return true;
	}
	return false;
}


TestiTulos setup::test_missa_riveissa_ruutu_on() {
	bool testi = true;

	int ruutu = 12;

	std::vector<PaikkaRivilla> odotetut_paikat;
	odotetut_paikat.push_back(PaikkaRivilla(2, 2));
	odotetut_paikat.push_back(PaikkaRivilla(8, 2));
	odotetut_paikat.push_back(PaikkaRivilla(19, 2));
	odotetut_paikat.push_back(PaikkaRivilla(41, 2));

	std::vector<PaikkaRivilla> oikeat_paikat = missa_riveissa_ruutu_on(testivakio, ruutu);

	testi = testi && odotetut_paikat.size() == oikeat_paikat.size();
	
	for (int i = 0; i < oikeat_paikat.size(); i++)
	{
		bool loytyi = false;
		for (int j = 0; j < odotetut_paikat.size(); j++)
		{
			if (vertaa_PaikkaRivilla(odotetut_paikat[j], oikeat_paikat[i]))
			{
				loytyi = true;
			}
		}
		testi = testi && loytyi;
	}

	TestiTulos tulos;
	tulos.kuvaus = "missa_riveissa_ruutu_on-funktio";
	tulos.lapi = testi;

	return tulos;
}