#pragma once

#include "wx/wx.h"
#include "ristinollapeli.h"

class ristinollaIkkuna : public wxFrame
{
public:
	wxButton** painikkeet = nullptr;
	Vakiot vakiot;
	//Ristinollapeli ristinolla;
	Ristinolla ristinolla;
	ristinollaIkkuna();
	~ristinollaIkkuna();
	void painallus(wxCommandEvent& evt);
};

