#pragma once

#include "wx/wx.h"
#include "ristinollapeli.h"
#include <iostream>
#include <fstream>


class AsetusIkkuna : public wxFrame
{
public:
	
	wxTextCtrl* leveys_teksti = nullptr;
	wxTextCtrl* korkeus_teksti = nullptr;
	wxTextCtrl* vier_teksti = nullptr;

	wxButton* ok_painike = nullptr;
	wxButton* peru_painike = nullptr;

	AsetusIkkuna();
	~AsetusIkkuna();
};


class ristinollaIkkuna : public wxFrame
{
public:
	AsetusIkkuna* asetusikkuna = nullptr;
	wxMenuBar* valikko = nullptr;
	wxBoxSizer* sizer = nullptr;
	wxButton** painikkeet = nullptr;
	wxGridSizer* grid = nullptr;
	wxBoxSizer* ruudukko = nullptr;
	wxPanel* statusrivi = nullptr;
	wxButton* vuororuutu = nullptr;
	Vakiot vakiot;  // = Vakiot(3, 3, 3);  // 24, 16, 5
	//Ristinollapeli ristinolla;
	Ristinolla ristinolla;
	ristinollaIkkuna();
	~ristinollaIkkuna();
	void muuta_asetuksia(int leveys, int korkeus, int vier_lkm);
	//void tallenna_asetukset();
	//void lataa_asetukset();
	void painallus(wxCommandEvent& evt);
	void aloita_alusta();
	void aloita_alusta(wxCommandEvent& evt);
	void avaa_asetukset(wxCommandEvent& evt);
	void ok_asetukset(wxCommandEvent& evt);
	void peru_asetukset(wxCommandEvent& evt);
	void lopeta(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

Vakiot lataa_asetukset();
void tallenna_asetukset(int leveys, int korkeus, int vier_lkm);
