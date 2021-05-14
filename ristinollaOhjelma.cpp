#include "ristinollaOhjelma.h"

wxIMPLEMENT_APP(ristinollaOhjelma);

bool ristinollaOhjelma::OnInit() {
	ikkuna = new ristinollaIkkuna;
	ikkuna->Show();

	return true;
}

// hotkey-juttuja
int ristinollaOhjelma::FilterEvent(wxEvent& evt) {
	if (evt.GetEventType() == wxEVT_KEY_DOWN && ((wxKeyEvent&)evt).GetKeyCode() == WXK_F2)
	{
		ikkuna->aloita_alusta();
		//evt.Skip();
		return true;
	}
	return -1;
}