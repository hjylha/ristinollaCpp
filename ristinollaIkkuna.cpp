#include "ristinollaIkkuna.h"
//#include "ristinollapeli.h"

wxBEGIN_EVENT_TABLE(ristinollaIkkuna, wxFrame)
	EVT_MENU(314, ristinollaIkkuna::aloita_alusta)
	EVT_MENU(315, ristinollaIkkuna::avaa_asetukset)
	EVT_MENU(316, ristinollaIkkuna::lopeta)
wxEND_EVENT_TABLE()


AsetusIkkuna::AsetusIkkuna() : wxFrame(nullptr, wxID_ANY, "Asetukset", wxDefaultPosition, wxDefaultSize)
{

}

AsetusIkkuna::AsetusIkkuna(std::map<std::string, int> asetukset) : wxFrame(nullptr, wxID_ANY, "Asetukset", wxDefaultPosition, wxSize(400, 300))
{
	std::string leveys_str = std::to_string(asetukset["leveys"]);
	wxBoxSizer* rivi1 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* leveys_selitys = new wxStaticText(this, wxID_ANY, "Leveys (ruutuina): ");
	rivi1->Add(leveys_selitys, 1);
	leveys_teksti = new wxTextCtrl(this, wxID_ANY, leveys_str);
	rivi1->Add(leveys_teksti, 0);

	std::string korkeus_str = std::to_string(asetukset["korkeus"]);
	wxBoxSizer* rivi2 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* korkeus_selitys = new wxStaticText(this, wxID_ANY, "Korkeus (ruutuina): ");
	rivi2->Add(korkeus_selitys, 1);
	korkeus_teksti = new wxTextCtrl(this, wxID_ANY, korkeus_str);
	rivi2->Add(korkeus_teksti, 0);

	std::string vier_str = std::to_string(asetukset["vier_lkm"]);
	wxBoxSizer* rivi3 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* vier_selitys = new wxStaticText(this, wxID_ANY, "Merkkejä halutaan vierekkäin: ");
	rivi3->Add(vier_selitys, 1);
	vier_teksti = new wxTextCtrl(this, wxID_ANY, vier_str);
	rivi3->Add(vier_teksti, 0);

	// satunnainen rivi
	wxBoxSizer* rivi3_vali = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* vali = new wxStaticText(this, wxID_ANY, "");
	rivi3_vali->Add(vali, 1);

	// Valinta, pelataanko AI:ta vastaan, ja onko AI risti vai nolla
	wxBoxSizer* rivi4 = new wxBoxSizer(wxHORIZONTAL);
	ai_paalla_check = new wxCheckBox(this, wxID_ANY, "Vastustajana AI");
	ai_paalla_check->Bind(wxEVT_CHECKBOX, &AsetusIkkuna::ai_vaihto, this);
	// jos AI pelaa, tama on valittuna
	if (asetukset["ai_moodi"] != -1)
	{
		ai_paalla_check->SetValue(true);
	}
	rivi4->Add(ai_paalla_check, 0);

	wxStaticText* ai_vali = new wxStaticText(this, wxID_ANY, "\t");
	rivi4->Add(ai_vali, 0);

	//wxBoxSizer* rivi5 = new wxBoxSizer(wxHORIZONTAL);
	wxString vaihtoehdot[] = { "Risti", "Nolla" };
	ai_valinta = new wxRadioBox(this, wxID_ANY, "AI-pelaajan puoli", wxDefaultPosition, wxDefaultSize, 2, vaihtoehdot);
	if (!(ai_paalla_check->IsChecked()))
	{
		ai_valinta->Enable(0, false);
		ai_valinta->Enable(1, false);
	}
	else if (asetukset["ai_moodi"] == 1)
	{
		ai_valinta->SetSelection(1);
	}
	// muuten kai oletuksena 0 on valittu?
	rivi4->Add(ai_valinta, 0);

	// satunnainen rivi
	wxBoxSizer* rivi6_vali = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* vali1 = new wxStaticText(this, wxID_ANY, "");
	rivi6_vali->Add(vali1, 1);

	wxBoxSizer* rivi7 = new wxBoxSizer(wxHORIZONTAL);
	ok_painike = new wxButton(this, wxID_ANY, "OK");
	rivi7->Add(ok_painike);
	peru_painike = new wxButton(this, wxID_ANY, "Peruuta");
	rivi7->Add(peru_painike);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(rivi1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	sizer->Add(rivi2, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	sizer->Add(rivi3, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	sizer->Add(rivi3_vali, 0, wxEXPAND, 10);
	sizer->Add(rivi4, 0, wxALIGN_CENTER, 10);
	//sizer->Add(rivi5, 0, wxEXPAND, 10);
	sizer->Add(rivi6_vali, 0, wxEXPAND, 10);
	sizer->Add(rivi7, 0, wxALIGN_CENTER | wxBOTTOM, 10);

	this->SetSizer(sizer);
}

AsetusIkkuna::~AsetusIkkuna() {

}

// jos AI pelaa, voidaan vaihtaa AI ristin ja nollan valilla, muuten ei
void AsetusIkkuna::ai_vaihto(wxCommandEvent& evt) {

	if (ai_paalla_check->IsChecked())
	{
		ai_valinta->Enable(0, true);
		ai_valinta->Enable(1, true);
	}
	else
	{
		ai_valinta->Enable(0, false);
		ai_valinta->Enable(1, false);
	}

	evt.Skip();
}


//wxPoint(30, 30), wxSize(800, 600)
ristinollaIkkuna::ristinollaIkkuna() : wxFrame(nullptr, wxID_ANY, "Ristinolla", wxPoint(30, 30), wxSize(800, 600))
{
	//vakiot = Vakiot(12, 10, 5);
	asetukset = lataa_asetukset();
	vakiot = Vakiot(asetukset["leveys"], asetukset["korkeus"], asetukset["vier_lkm"]);

	// asetusikkuna on olemassa, vaikkei ehka nakyvilla
	asetusikkuna = new AsetusIkkuna(asetukset);

	//luodaan valikko
	valikko = new wxMenuBar();
	this->SetMenuBar(valikko);
	wxMenu* menu = new wxMenu();
	menu->Append(314, "Uusi peli\tF2");
	menu->Append(315, "Asetukset");
	menu->Append(316, "Lopeta");
	valikko->Append(menu, "Valikko");

	// ai_moodi pitaisi ladata asetustiedostosta
	//ai_moodi = 0; asetukset["ai_moodi"]
	ennakoitujen_siirtojen_lkm = 4;
	ristinolla = Ristinolla_OG(vakiot, {}, {});
	//ristinolla = Ristinolla(vakiot, {}, {});
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

	// jos AI aloittaa, sen siirron kai tulee maaraytya tassa
	if (asetukset["ai_moodi"] == 0)
	{
		//int siirto = siirto_arvon_perusteella(ristinolla);
		//int siirto = siirto_arvon_perusteella_e(ristinolla, ennakoitujen_siirtojen_lkm, 0)[0];
		//int siirto = siirto_rek_arvon_perusteella(ristinolla, ennakoitujen_siirtojen_lkm);
		int siirto = aloitussiirto(vakiot);
		painikkeet[siirto]->SetLabel(vakiot.MERKIT[ristinolla.vuorossa]);
		painikkeet[siirto]->Enable(false);
		ristinolla.tee_siirto(siirto);
		vuororuutu->SetLabel(vakiot.MERKIT[ristinolla.vuorossa]);
		// peli ei kai voi paattya yhteen siirtoon?
	}
}

ristinollaIkkuna::~ristinollaIkkuna() {
	delete[] painikkeet;
}

bool ristinollaIkkuna::siirra(int ruutu) {
	bool alusta = false;
	painikkeet[ruutu]->SetLabel(vakiot.MERKIT[ristinolla.vuorossa]);
	painikkeet[ruutu]->Enable(false);
	ristinolla.tee_siirto(ruutu);
	vuororuutu->SetLabel(vakiot.MERKIT[ristinolla.vuorossa]);
	// tarkistetaan, onko peli ohi
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
	// jos peli loppunut, deaktivoidaan painikkeet
	if (alusta)
	{
		for (int i = 0; i < vakiot.LEVEYS * vakiot.KORKEUS; i++)
		{
			painikkeet[i]->Enable(false);
		}
	}
	return alusta;
}

void ristinollaIkkuna::painallus(wxCommandEvent& evt) {
	int ruutu = evt.GetId() - 1000;
	if (ristinolla.onko_siirto_mahdollinen(ruutu))
	{
		bool alusta = siirra(ruutu);
		// AI siirtaa, jos peli ei ole ohi, ja pelataan AI:ta vastaan
		if (!alusta && asetukset["ai_moodi"] != -1)
		{
			// ai katsoo viela pelaajan seuraavan siirron
			int siirto = siirto_arvon_perusteella(ristinolla);
			// jostain syysta tama on paljon hitaampi
			//int siirto = siirto_arvon_perusteella_r(ristinolla, ennakoitujen_siirtojen_lkm)[0];
			// tama ei oikein toimi
			//int siirto = siirto_rek_arvon_perusteella(ristinolla, ennakoitujen_siirtojen_lkm);
			siirra(siirto);
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

	// jos AI aloittaa, sen siirto maaraytynee tassa
	if (asetukset["ai_moodi"] == 0)
	{
		//int siirto = siirto_arvon_perusteella(ristinolla);
		// int siirto = siirto_arvon_perusteella_e(ristinolla, ennakoitujen_siirtojen_lkm, 0)[0];
		//int siirto = siirto_rek_arvon_perusteella(ristinolla, ennakoitujen_siirtojen_lkm);
		int siirto = aloitussiirto(vakiot);
		siirra(siirto);
	}
}

void ristinollaIkkuna::aloita_alusta(wxCommandEvent& evt) {
	for (int i = 0; i < vakiot.LEVEYS * vakiot.KORKEUS; i++)
	{
		painikkeet[i]->SetLabel("");
		painikkeet[i]->Enable(true);
	}
	ristinolla.aloita_alusta();
	vuororuutu->SetLabel(vakiot.MERKIT[ristinolla.vuorossa]);

	// jos AI aloittaa, sen siirto maaraytynee tassa
	if (asetukset["ai_moodi"] == 0)
	{
		//int siirto = siirto_arvon_perusteella(ristinolla);
		// int siirto = siirto_arvon_perusteella_e(ristinolla, ennakoitujen_siirtojen_lkm, 0)[0];
		//int siirto = siirto_rek_arvon_perusteella(ristinolla, ennakoitujen_siirtojen_lkm);
		int siirto = aloitussiirto(vakiot);
		siirra(siirto);
	}

	evt.Skip();
}

void ristinollaIkkuna::avaa_asetukset(wxCommandEvent& evt) {
	
	asetusikkuna = new AsetusIkkuna(asetukset);
	asetusikkuna->ok_painike->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ristinollaIkkuna::ok_asetukset, this);
	asetusikkuna->peru_painike->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ristinollaIkkuna::peru_asetukset, this);
	asetusikkuna->Show();
	evt.Skip();
}

void ristinollaIkkuna::muuta_asetuksia(int leveys, int korkeus, int vier_lkm) {
	// poistetaan vanhat kaiketi???
	ruudukko->Clear();
	for (int i = 0; i < vakiot.LEVEYS * vakiot.KORKEUS; i++)
	{
		painikkeet[i]->Destroy();
	}
	delete[] painikkeet;
	//delete[] grid;
	
	tallenna_asetukset(leveys, korkeus, vier_lkm, asetukset["ai_moodi"]);
	// ja sitten uutta kehiin!
	asetukset["leveys"] = leveys;
	asetukset["korkeus"] = korkeus;
	asetukset["vier_lkm"] = vier_lkm;
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
	if (asetusikkuna->ai_paalla_check->IsChecked())
	{
		asetukset["ai_moodi"] = asetusikkuna->ai_valinta->GetSelection();
	}
	else
	{
		asetukset["ai_moodi"] = -1;
	}
	// ei sallita 1x1-peliruutuja
	// ja jotain satunnaisia maksimeja
	if (1 < korkeus && korkeus < 41 && 1 < leveys && leveys < 41 && 1 < vier_lkm && vier_lkm < 11)
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
	//asetusikkuna->Destroy();
	Close();
	evt.Skip();
}


// varmistetaan etta asetusvektorin arvot ovat jarkevia
std::vector<int> tarkasta_asetusvektori(std::vector<int> asetusvektori, std::vector<int> ylarajat) {
	return asetusvektori;
}

// luetaan asetukset asetustiedostosta
std::map<std::string, int> lataa_asetukset() {
	std::map<std::string, int> asetukset;
	std::vector<int> asetusvektori;
	std::ifstream asetustiedosto("asetukset.txt");
	std::string data;
	while (std::getline(asetustiedosto, data))
	{
		int luku = std::stoi(data);
		// pitaisiko tarkastaa, etta luku on jarkeva?
		asetusvektori.push_back(luku);
	}
	asetustiedosto.close();
	asetukset["leveys"] = asetusvektori[0];
	asetukset["korkeus"] = asetusvektori[1];
	asetukset["vier_lkm"] = asetusvektori[2];
	asetukset["ai_moodi"] = asetusvektori[3];
	return asetukset;
}

//Vakiot lataa_asetukset() {
//	std::vector<int> vakiot;
//	std::ifstream asetustiedosto("asetukset.txt");
//	std::string data;
//	while (std::getline(asetustiedosto, data))
//	{
//		int luku = std::stoi(data);
//		// pitaisiko tarkastaa, etta luku on jarkeva?
//		vakiot.push_back(luku);
//	}
//	asetustiedosto.close();
//	return Vakiot(vakiot[0], vakiot[1], vakiot[2]);
//}

// tallennetaan asetukset
void tallenna_asetukset(int leveys, int korkeus, int vier_lkm, int ai_moodi) {
	std::ofstream asetustiedosto;
	asetustiedosto.open("asetukset.txt");
	asetustiedosto << leveys << std::endl;
	asetustiedosto << korkeus << std::endl;
	asetustiedosto << vier_lkm << std::endl;
	asetustiedosto << ai_moodi << std::endl;
	asetustiedosto.close();
}

//void tallenna_asetukset(int leveys, int korkeus, int vier_lkm) {
//	std::ofstream asetustiedosto;
//	asetustiedosto.open("asetukset.txt");
//	asetustiedosto << leveys << std::endl;
//	asetustiedosto << korkeus << std::endl;
//	asetustiedosto << vier_lkm << std::endl;
//	asetustiedosto.close();
//}