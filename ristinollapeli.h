//#pragma once
//
//#include <string>
//#include <vector>
//#include <map>
//#include <set>
//#include <fstream>
//#include <cmath>
//#include <algorithm>
//
//class Vakiot {
//public:
//	int LEVEYS;
//	int KORKEUS;
//	int VIER_LKM;
//	char MERKIT[2] = {'X', '0'};
//	std::string SUUNNAT[4] = { "A", "O", "AO", "AV" };
//	Vakiot();
//	Vakiot(int leveys, int korkeus, int vier_lkm);
//};
//
//class Rivi {
//public:
//	Vakiot vakiot;
//	std::string suunta;
//	std::vector<int> ruudut;
//	std::vector<char> status;
//	//Rivi(int rivin_pituus);
//	Rivi();
//	// Rivi(Vakiot vakiot, std::string rivin_suunta, int rivin_alkuruutu);
//	Rivi(Vakiot vakiot, std::string rivin_suunta, int rivin_alkuruutu, std::vector<int> ristit, std::vector<int> nollat);
//	int ristien_lkm();
//	int nollien_lkm();
//	int merkkien_lkm(int merkki_indeksi);
//	bool sopii();
//	bool on_pelattavissa();
//	std::vector<int> vapaat();
//};
//
//class Rivit {
//public:
//	Vakiot vakiot;
//	//std::vector<int> aktiiviset_rivit;
//	std::vector<bool> aktiiviset_rivit;
//	std::vector<Rivi> rivit;
//	Rivit();
//	Rivit(Vakiot vakio, std::vector<int> ristit, std::vector<int> nollat);
//	//bool onko_ruudussa_risti(int ruutu);
//	//bool onko_ruudussa_nolla(int ruutu);
//	//bool onko_ruutu_vapaa(int ruutu);
//	std::vector<std::vector<int>> missa_riveissa_ruutu_on(int ruutu);
//};
//
//class Ristinolla_OG
//{
//public:
//	Vakiot vakiot;
//	std::vector<int> vapaat;
//	std::vector<int> ristit;
//	std::vector<int> nollat;
//	std::vector<int> siirrot;
//	int vuorossa;
//
//	Ristinolla_OG();
//	Ristinolla_OG(Vakiot vakio, std::vector<int> ristiruudut, std::vector<int> nollaruudut);
//
//	bool on_ratkaisematon();
//	bool risti_voitti();
//	bool nolla_voitti();
//	std::pair<bool, int> voitti();
//	bool onko_siirto_mahdollinen(int ruutu);
//	void tee_siirto(int ruutu);
//	void kumoa_siirto();
//	void aloita_alusta();
//	std::vector<char> status();
//
//	std::pair<bool, int> merkki_lkm_rivilla(int alkuruutu, std::string suunta);
//	int arvo();
//	std::pair<bool, int> onko_ruudun_etaisyys_pelista_pienempi(int ruutu, int ref_etaisyys);
//	std::vector<int> priorisoi_ruudut();
//};
//
//class Ristinolla : public Ristinolla_OG {
//public:
//	//Vakiot vakiot;
//	//std::vector<int> vapaat;
//	//std::vector<int> ristit;
//	//std::vector<int> nollat;
//	//std::vector<int> siirrot;
//	//int vuorossa;
//	//uudet ominaisuudet
//	Rivit rivit;
//	// merkki_lkm[0][i] on niiden (aktiivisten) rivien lkm, joissa on i ristia
//	std::vector<std::map<int, int>> merkki_lkm;
//	// rivien_mlkm[0][i] sisaltaa niiden rivien indeksit, joissa on i ristia
//	std::vector<std::map<int, std::set<int>>> rivien_mlkm;
//
//	Ristinolla();
//	Ristinolla(Vakiot vakio, std::vector<int> ristiruudut, std::vector<int> nollaruudut);
//
//	bool on_ratkaisematon();
//	std::pair<bool, int> voitti();
//	bool risti_voitti();
//	bool nolla_voitti();
//	bool onko_siirto_mahdollinen(int ruutu);
//	void tee_siirto(int ruutu);
//	//int edellinen_siirto();
//	void kumoa_siirto();
//	void aloita_alusta();
//	//bool poistetaan(int rivi_id);
//	int arvo();
//};
//
//class Ristinollapeli {
//public:
//	/*int KORKEUS;
//	int LEVEYS;
//	int VIER_LKM;
//	char MERKIT[2];
//	std::string SUUNNAT[4];*/
//	Vakiot vakiot;
//	Ristinolla ristinolla;
//	Ristinollapeli();
//	Ristinollapeli(Vakiot vakio);
//};
//
//
//// funktioita
//std::vector<int> tee_siirtolista(std::vector<int> ristit, std::vector<int> nollat);
//std::vector<std::vector<int>> ristit_ja_nollat(std::vector<int> siirrot);
//bool onko_ruudussa_risti(int ruutu, std::vector<int> ristit);
//bool onko_ruudussa_nolla(int ruutu, std::vector<int> nollat);
//bool onko_ruutu_vapaa(int ruutu, std::vector<int> ristit, std::vector<int> nollat);
//std::vector<int> vapaat_ruudut(Vakiot vakiot, std::vector<int> ristit, std::vector<int> nollat);
//int is_ruutu_rivilla(int i, int alkuruutu, std::string suunta, Vakiot vakio);
//// jarjestettyjen vektorien operaatioita
//std::vector<int> lisaa_ruutu(int ruutu, std::vector<int> vektori);
//int etsi_indeksi(int luku, std::vector<int> vektori);
//std::vector<std::pair<int, int>> lisaa_pari_toisen_luvun_mukaan(std::pair<int, int> pari, std::vector<std::pair<int, int>> vektori);
//int etsi_indeksi_toisen_luvun_mukaan(std::pair<int, int> pari, std::vector<std::pair<int, int>> vektori);
//
//
//
//// AI-juttuja/pelin tallennus
//std::vector<int> priorisoi_vapaat(Ristinolla ristinolla);
//int kay_siirrot_lapi(Ristinolla ristinolla, int siirto_lkm, int nyk_arvo);
//int aloitussiirto(Vakiot vakio);
//int siirto_arvon_perusteella(Ristinolla ristinolla);
//int siirto_arvon_perusteella(Ristinolla_OG ristinolla);
//std::vector<int> siirto_arvon_perusteella_r(Ristinolla_OG ristinolla, int siirto_lkm);
//std::vector<int> siirto_arvon_perusteella_r(Ristinolla ristinolla, int siirto_lkm);
//std::vector<int> siirto_arvon_perusteella_r0(Ristinolla_OG ristinolla, int siirto_lkm, int nyk_arvo);
//std::vector<int> siirto_arvon_perusteella_r0(Ristinolla ristinolla, int siirto_lkm, int nyk_arvo);
//int rekursiivinen_arvo(Ristinolla ristinolla, int siirto_lkm);
//int siirto_rek_arvon_perusteella(Ristinolla ristinolla, int siirto_lkm);
//
//
//class PelattuPeli {
//public:
//	int lopputulos;
//	//std::vector<int> ristit;
//	//std::vector<int> nollat;
//	std::vector<int> siirrot;
//	PelattuPeli();
//	PelattuPeli(int tulos, std::vector<int>ristivektori, std::vector<int> nollavektori);
//};
//
//void tallenna_pelit(Vakiot vakio, std::vector<PelattuPeli> pelit);
//std::vector<PelattuPeli> lataa_pelit(Vakiot vakio);
//int ovatko_jarjestyksessa(std::vector<int> siirrot1, std::vector<int> siirrot2);
//std::vector<PelattuPeli> lisaa_peli(PelattuPeli peli, std::vector<PelattuPeli> pelit);
//int etsi_peli(PelattuPeli peli, std::vector<PelattuPeli> pelit);
//bool loytyyko_osa_pelia(std::vector<int> siirrot, std::vector<PelattuPeli> pelit);
//std::vector<PelattuPeli> etsi_osa_pelia(std::vector<int> siirrot, std::vector<PelattuPeli> pelit, int max_num);
//
//
//
