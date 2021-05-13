#pragma once

#include "wx/wx.h"
#include "ristinollapeli.h"

class ristinollaIkkuna : public wxFrame
{
public:
	wxMenuBar* valikko = nullptr;
	wxButton** painikkeet = nullptr;
	wxPanel* statusrivi = nullptr;
	wxButton* vuororuutu = nullptr;
	Vakiot vakiot = Vakiot(24, 18, 5);
	//Ristinollapeli ristinolla;
	Ristinolla ristinolla;
	ristinollaIkkuna();
	~ristinollaIkkuna();
	void painallus(wxCommandEvent& evt);
	void aloita_alusta();
	void aloita_alusta(wxCommandEvent& evt);
	void lopeta(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

