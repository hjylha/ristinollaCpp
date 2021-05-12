#include "ristinollaOhjelma.h"

wxIMPLEMENT_APP(ristinollaOhjelma);

bool ristinollaOhjelma::OnInit() {
	ikkuna = new ristinollaIkkuna;
	ikkuna->Show();

	return true;
}