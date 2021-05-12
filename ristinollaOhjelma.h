#pragma once

#include "wx/wx.h"
#include "ristinollaIkkuna.h"

class ristinollaOhjelma : public wxApp
{
private:
	ristinollaIkkuna* ikkuna = nullptr;

public:
	virtual bool OnInit();
};

