#include "ristinollaIkkuna.h"
//#include "ristinollapeli.h"

wxBEGIN_EVENT_TABLE(ristinollaIkkuna, wxFrame)
	EVT_MENU(314, ristinollaIkkuna::aloita_alusta)
	EVT_MENU(315, ristinollaIkkuna::lopeta)
wxEND_EVENT_TABLE()

ristinollaIkkuna::ristinollaIkkuna() : wxFrame(nullptr, wxID_ANY, "Ristinolla", wxPoint(30, 30), wxSize(800, 600))
{
	//luodaan valikko
	valikko = new wxMenuBar();
	this->SetMenuBar(valikko);
	wxMenu* menu = new wxMenu();
	menu->Append(314, "Uusi peli\tF2");
	menu->Append(315, "Lopeta");
	valikko->Append(menu, "Valikko");


	//vakiot = Vakiot(12, 10, 5);
	//ristinolla = Ristinollapeli(vakiot);
	ristinolla = Ristinolla(vakiot, {}, {});
	//painike = new wxButton(this, wxID_ANY, "Click this", wxPoint(10, 10), wxSize(150, 50));
	painikkeet = new wxButton * [vakiot.KORKEUS * vakiot.LEVEYS];
	wxGridSizer* grid = new wxGridSizer(vakiot.KORKEUS, vakiot.LEVEYS, 0, 0);

	statusrivi = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 50));
	wxStaticText* teksti = new wxStaticText(statusrivi, wxID_ANY, "Vuorossa: ", wxPoint(20, 15));
	//teksti->AppendString
	vuororuutu = new wxButton(statusrivi, wxID_ANY, "", wxPoint(100, 10), wxSize(30, 30));
	vuororuutu->Enable(false);
	vuororuutu->SetLabel(vakiot.MERKIT[ristinolla.vuorossa]);
	
	for (int i = 0; i < vakiot.LEVEYS * vakiot.KORKEUS; i++)
	{
		painikkeet[i] = new wxButton(this, 1000 + i);
		grid->Add(painikkeet[i], 1, wxEXPAND | wxALL);
		painikkeet[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ristinollaIkkuna::painallus, this);
	}

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(grid, 1, wxEXPAND);
	sizer->Add(statusrivi, 0, wxEXPAND);

	this->SetSizer(sizer);
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
		vuororuutu->SetLabel(vakiot.MERKIT[ristinolla.vuorossa]);
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
		if (alusta)
		{
			//this->aloita_alusta();
			// jos peli loppunut, deaktivoidaan painikkeet
			for (int i = 0; i < vakiot.LEVEYS * vakiot.KORKEUS; i++)
			{
				painikkeet[i]->Enable(false);
			}
		}
	}
	evt.Skip();
}

void ristinollaIkkuna::aloita_alusta() {
	for (int i = 0; i < vakiot.LEVEYS * vakiot.KORKEUS; i++)
	{
		painikkeet[i]->SetLabel("");
		painikkeet[i]->Enable(true);
	}
	ristinolla.aloita_alusta();
}

void ristinollaIkkuna::aloita_alusta(wxCommandEvent& evt) {
	for (int i = 0; i < vakiot.LEVEYS * vakiot.KORKEUS; i++)
	{
		painikkeet[i]->SetLabel("");
		painikkeet[i]->Enable(true);
	}
	ristinolla.aloita_alusta();
	evt.Skip();
}

void ristinollaIkkuna::lopeta(wxCommandEvent& evt) {
	Close();
	evt.Skip();
}
