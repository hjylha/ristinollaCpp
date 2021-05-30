#include "ristinollaIkkuna.h"
//#include "ristinollapeli.h"

wxBEGIN_EVENT_TABLE(ristinollaIkkuna, wxFrame)
	EVT_MENU(314, ristinollaIkkuna::aloita_alusta)
	EVT_MENU(315, ristinollaIkkuna::avaa_asetukset)
	EVT_MENU(316, ristinollaIkkuna::lopeta)
wxEND_EVENT_TABLE()


AsetusIkkuna::AsetusIkkuna() : wxFrame(nullptr, wxID_ANY, "Asetukset", wxDefaultPosition, wxDefaultSize)
{
	leveys_teksti = new wxTextCtrl(this, wxID_ANY, "");
	korkeus_teksti = new wxTextCtrl(this, wxID_ANY, "");
	vier_teksti = new wxTextCtrl(this, wxID_ANY, "");

	ok_painike = new wxButton(this, wxID_ANY, "OK");
	peru_painike = new wxButton(this, wxID_ANY, "Peruuta");

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(leveys_teksti, 0, wxEXPAND);
	sizer->Add(korkeus_teksti, 0, wxEXPAND);
	sizer->Add(vier_teksti, 0, wxEXPAND);
	sizer->Add(ok_painike, 0, wxEXPAND);
	sizer->Add(peru_painike, 0, wxEXPAND);

	this->SetSizer(sizer);
}

AsetusIkkuna::~AsetusIkkuna() {

}


//wxPoint(30, 30), wxSize(800, 600)
ristinollaIkkuna::ristinollaIkkuna() : wxFrame(nullptr, wxID_ANY, "Ristinolla", wxPoint(30, 30), wxDefaultSize)
{
	// asetusikkuna on olemassa, vaikkei ehka nakyvilla
	asetusikkuna = new AsetusIkkuna();

	//luodaan valikko
	valikko = new wxMenuBar();
	this->SetMenuBar(valikko);
	wxMenu* menu = new wxMenu();
	menu->Append(314, "Uusi peli\tF2");
	menu->Append(315, "Asetukset");
	menu->Append(316, "Lopeta");
	valikko->Append(menu, "Valikko");


	//vakiot = Vakiot(12, 10, 5);
	vakiot = lataa_asetukset();
	//ristinolla = Ristinollapeli(vakiot);
	ristinolla = Ristinolla(vakiot, {}, {});
	//painike = new wxButton(this, wxID_ANY, "Click this", wxPoint(10, 10), wxSize(150, 50));
	painikkeet = new wxButton * [vakiot.KORKEUS * vakiot.LEVEYS];
	grid = new wxGridSizer(vakiot.KORKEUS, vakiot.LEVEYS, 0, 0);

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

	sizer = new wxBoxSizer(wxVERTICAL);
	ruudukko = new wxBoxSizer(wxVERTICAL);
	ruudukko->Add(grid, 1, wxEXPAND);
	sizer->Add(ruudukko, 1, wxEXPAND);
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
	vuororuutu->SetLabel(vakiot.MERKIT[ristinolla.vuorossa]);
}

void ristinollaIkkuna::aloita_alusta(wxCommandEvent& evt) {
	for (int i = 0; i < vakiot.LEVEYS * vakiot.KORKEUS; i++)
	{
		painikkeet[i]->SetLabel("");
		painikkeet[i]->Enable(true);
	}
	ristinolla.aloita_alusta();
	vuororuutu->SetLabel(vakiot.MERKIT[ristinolla.vuorossa]);
	evt.Skip();
}

void ristinollaIkkuna::avaa_asetukset(wxCommandEvent& evt) {
	
	asetusikkuna = new AsetusIkkuna();
	asetusikkuna->ok_painike->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ristinollaIkkuna::ok_asetukset, this);
	asetusikkuna->peru_painike->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ristinollaIkkuna::peru_asetukset, this);
	asetusikkuna->Show();
	evt.Skip();
}

void ristinollaIkkuna::muuta_asetuksia(int leveys, int korkeus, int vier_lkm) {
	// poistetaan vanhat kaiketi???
	ruudukko->Clear();
	//sizer->Clear();
	for (int i = 0; i < vakiot.LEVEYS * vakiot.KORKEUS; i++)
	{
		painikkeet[i]->Destroy();
	}
	delete[] painikkeet;
	//delete[] grid;
	
	tallenna_asetukset(leveys, korkeus, vier_lkm);
	// ja sitten uutta kehiin!
	vakiot = Vakiot(leveys, korkeus, vier_lkm);
	ristinolla = Ristinolla(vakiot, {}, {});
	painikkeet = new wxButton * [vakiot.KORKEUS * vakiot.LEVEYS];
	grid = new wxGridSizer(vakiot.KORKEUS, vakiot.LEVEYS, 0, 0);
	for (int i = 0; i < vakiot.LEVEYS * vakiot.KORKEUS; i++)
	{
		painikkeet[i] = new wxButton(this, 1000 + i);
		grid->Add(painikkeet[i], 1, wxEXPAND | wxALL);
		painikkeet[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ristinollaIkkuna::painallus, this);
	}
	ruudukko->Add(grid, 1, wxEXPAND);
	//sizer->Add(ruudukko, 1, wxEXPAND);
	//sizer->Add(statusrivi, 0, wxEXPAND);

	this->SetSizer(sizer);
	grid->Layout();
	//ruudukko->Layout();
	sizer->Layout();


	// varmuuden vuoksi viela aloitusfunktio
	aloita_alusta();
}

void ristinollaIkkuna::ok_asetukset(wxCommandEvent& evt) {
	int korkeus, leveys, vier_lkm;
	//wxString kork = asetusikkuna->korkeus_teksti->GetValue();
	leveys = wxAtoi(asetusikkuna->leveys_teksti->GetValue());
	korkeus = wxAtoi(asetusikkuna->korkeus_teksti->GetValue());
	vier_lkm = wxAtoi(asetusikkuna->vier_teksti->GetValue());
	if (korkeus > 0 && leveys > 0 && vier_lkm > 0)
	{
		asetusikkuna->Destroy();
		muuta_asetuksia(leveys, korkeus, vier_lkm);
	}
	evt.Skip();
}

void ristinollaIkkuna::peru_asetukset(wxCommandEvent& evt) {
	asetusikkuna->Destroy();
	evt.Skip();
}

void ristinollaIkkuna::lopeta(wxCommandEvent& evt) {
	asetusikkuna->Destroy();
	Close();
	evt.Skip();
}

Vakiot lataa_asetukset() {
	std::vector<int> vakiot;
	std::ifstream asetustiedosto("asetukset.txt");
	std::string data;
	while (std::getline(asetustiedosto, data))
	{
		vakiot.push_back(std::stoi(data));
	}
	asetustiedosto.close();
	return Vakiot(vakiot[0], vakiot[1], vakiot[2]);
}

void tallenna_asetukset(int leveys, int korkeus, int vier_lkm) {
	std::ofstream asetustiedosto;
	asetustiedosto.open("asetukset.txt");
	asetustiedosto << leveys << std::endl;
	asetustiedosto << korkeus << std::endl;
	asetustiedosto << vier_lkm << std::endl;
	asetustiedosto.close();
}