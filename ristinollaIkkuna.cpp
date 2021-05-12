#include "ristinollaIkkuna.h"
//#include "ristinollapeli.h"

ristinollaIkkuna::ristinollaIkkuna() : wxFrame(nullptr, wxID_ANY, "Ristinolla", wxPoint(30, 30), wxSize(800, 600))
{
	vakiot = Vakiot(12, 10, 5);
	//ristinolla = Ristinollapeli(vakiot);
	ristinolla = Ristinolla(vakiot, {}, {});
	//painike = new wxButton(this, wxID_ANY, "Click this", wxPoint(10, 10), wxSize(150, 50));
	painikkeet = new wxButton * [vakiot.KORKEUS * vakiot.LEVEYS];
	wxGridSizer* grid = new wxGridSizer(vakiot.KORKEUS, vakiot.LEVEYS, 0, 0);
	
	for (int i = 0; i < vakiot.LEVEYS * vakiot.KORKEUS; i++)
	{
		painikkeet[i] = new wxButton(this, 1000 + i);
		grid->Add(painikkeet[i], 1, wxEXPAND | wxALL);
		painikkeet[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ristinollaIkkuna::painallus, this);
	}

	this->SetSizer(grid);
	grid->Layout();
}

ristinollaIkkuna::~ristinollaIkkuna() {
	delete[] painikkeet;
}

void ristinollaIkkuna::painallus(wxCommandEvent& evt) {
	int ruutu = evt.GetId() - 1000;
	if (ristinolla.onko_siirto_mahdollinen(ruutu))
	{
		bool alusta = false;
		painikkeet[ruutu]->SetLabel(vakiot.MERKIT[ristinolla.vuorossa]);
		painikkeet[ruutu]->Enable(false);
		ristinolla.tee_siirto(ruutu);
		if (ristinolla.risti_voitti())
		{
			alusta = true;
			wxMessageBox("Risti voitti!!!!!");
		}
		else if (ristinolla.nolla_voitti())
		{
			alusta = true;
			wxMessageBox("Nolla voitti!!!!!");
		}
		else if (ristinolla.on_ratkaisematon())
		{
			alusta = true;
			wxMessageBox("Kumpikaan ei voi voittaa.");
		}
	}
	evt.Skip();
}
