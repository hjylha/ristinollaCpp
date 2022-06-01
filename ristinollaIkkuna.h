#pragma once

#include "wx/wx.h"
#include "ai.h"
#include <map>
#include <iostream>
#include <fstream>


class AsetusIkkuna : public wxFrame
{
public:
	
	wxTextCtrl* leveys_teksti = nullptr;
	wxTextCtrl* korkeus_teksti = nullptr;
	wxTextCtrl* vier_teksti = nullptr;

	wxCheckBox* ai_paalla_check = nullptr;
	wxRadioBox* ai_valinta = nullptr;

	wxButton* ok_painike = nullptr;
	wxButton* peru_painike = nullptr;

	AsetusIkkuna();
	//AsetusIkkuna(Vakiot vakio);
	AsetusIkkuna(std::map<std::string, int> asetukset);
	~AsetusIkkuna();
	//void ai_valinnat_paalle();
	void ai_vaihto(wxCommandEvent& evt);
};


class ristinollaIkkuna : public wxFrame
{
public:
	// GUI-juttuja
	AsetusIkkuna* asetusikkuna = nullptr;
	wxMenuBar* valikko = nullptr;
	wxBoxSizer* sizer = nullptr;
	wxButton** painikkeet = nullptr;
	wxGridSizer* grid = nullptr;
	wxBoxSizer* ruudukko = nullptr;
	wxPanel* statusrivi = nullptr;
	wxButton* vuororuutu = nullptr;

	// pelijuttuja
	std::map<std::string, int> asetukset;
	int ennakoitujen_siirtojen_lkm;
	//int ai_moodi;  // pelaako AI ristilla (0), nollalla (1) vai ei ollenkaan (-1)
	//Vakiot vakiot;  // = Vakiot(3, 3, 3);  // 24, 16, 5
	Ristinolla0 ristinolla;
	//Ristinolla ristinolla;
	ristinollaIkkuna();
	~ristinollaIkkuna();
	void muuta_asetuksia(int leveys, int korkeus, int vier_lkm);
	//void tallenna_asetukset();
	//void lataa_asetukset();
	bool siirra(int ruutu);
	void painallus(wxCommandEvent& evt);
	void aloita_alusta();
	void aloita_alusta(wxCommandEvent& evt);
	void avaa_asetukset(wxCommandEvent& evt);
	void ok_asetukset(wxCommandEvent& evt);
	void peru_asetukset(wxCommandEvent& evt);
	void lopeta(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

std::map<std::string, int> tarkasta_asetukset(std::map<std::string, int> asetukset, std::map<std::string, int> ylarajat);
std::map<std::string, int> lataa_asetukset();
//Vakiot lataa_asetukset();
void tallenna_asetukset(int leveys, int korkeus, int vier_lkm, int ai_moodi);
//void tallenna_asetukset(int leveys, int korkeus, int vier_lkm);
