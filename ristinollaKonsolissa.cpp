#include "ristinolla.h"
#include "ai.h"
#include "ristinollaKonsolissa.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <stdio.h>
#include <Windows.h>



int valinta_vasemmalle(int valittu_ruutu, Ristinolla ristinolla) {
    int uusi_valittu_ruutu = valittu_ruutu;
    for (int i = 0; i < ristinolla.vakio.LEVEYS; i++)
    {
        if (uusi_valittu_ruutu % ristinolla.vakio.LEVEYS == 0)
            {
                uusi_valittu_ruutu += ristinolla.vakio.LEVEYS - 1;
            }
        else {
                uusi_valittu_ruutu -= 1;
            }
        if (ristinolla.onko_siirto_mahdollinen(uusi_valittu_ruutu))
        {
            return uusi_valittu_ruutu;
        }
    }

    return uusi_valittu_ruutu;
}

int valinta_oikealle(int valittu_ruutu, Ristinolla ristinolla) {
    int uusi_valittu_ruutu = valittu_ruutu;
    for (int i = 0; i < ristinolla.vakio.LEVEYS; i++)
    {
        if (uusi_valittu_ruutu % ristinolla.vakio.LEVEYS == ristinolla.vakio.LEVEYS  - 1)
            {
                uusi_valittu_ruutu -= ristinolla.vakio.LEVEYS - 1;
            }
        else {
                uusi_valittu_ruutu += 1;
            }
        if (ristinolla.onko_siirto_mahdollinen(uusi_valittu_ruutu))
        {
            return uusi_valittu_ruutu;
        }
    }
    
    return uusi_valittu_ruutu;
}

int valinta_ylos(int valittu_ruutu, Ristinolla ristinolla) {
    int uusi_valittu_ruutu = valittu_ruutu;
    for (int i = 0; i < ristinolla.vakio.KORKEUS; i++)
    {
        if (uusi_valittu_ruutu < ristinolla.vakio.LEVEYS)
            {
                uusi_valittu_ruutu = ristinolla.vakio.LEVEYS * (ristinolla.vakio.KORKEUS - 1) + uusi_valittu_ruutu % ristinolla.vakio.LEVEYS;
            }
        else {
                uusi_valittu_ruutu -= ristinolla.vakio.LEVEYS;
            }
        if (ristinolla.onko_siirto_mahdollinen(uusi_valittu_ruutu))
        {
            return uusi_valittu_ruutu;
        }
    }
    
    return uusi_valittu_ruutu;
}

int valinta_alas(int valittu_ruutu, Ristinolla ristinolla) {
    int uusi_valittu_ruutu = valittu_ruutu;
    for (int i = 0; i < ristinolla.vakio.KORKEUS; i++)
    {
        if (uusi_valittu_ruutu / ristinolla.vakio.LEVEYS > ristinolla.vakio.KORKEUS- 2)
            {
                uusi_valittu_ruutu = uusi_valittu_ruutu % ristinolla.vakio.LEVEYS;
            }
        else {
                uusi_valittu_ruutu += ristinolla.vakio.LEVEYS;
            }
        if (ristinolla.onko_siirto_mahdollinen(uusi_valittu_ruutu))
        {
            return uusi_valittu_ruutu;
        }
    }
    
    return uusi_valittu_ruutu;
}



void piirraRistinolla(Ristinolla ristinolla, int valittu_ruutu) {
    system("cls");
    // system("clear");
    std::cout << "|-";
        for (int j = 0; j < ristinolla.vakio.LEVEYS - 1; j++)
        {
            std::cout << "--+-";
        }
        std::cout << "--|\n";
    for (int i = 0; i < ristinolla.vakio.KORKEUS; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < ristinolla.vakio.LEVEYS; j++)
        {
            if (i * ristinolla.vakio.LEVEYS + j == valittu_ruutu)
            {
                std::cout << "*";
            }
            else
            {
                std::cout << MERKIT[ristinolla.ruudut[i * ristinolla.vakio.LEVEYS + j]];
            }
            
            
            std::cout << " | ";
        }
        std::cout << "\n";

        // std::cout << "merkkirivi " << i << " piirretty." << std::endl;

        std::cout << "|-";
        for (int j = 0; j < ristinolla.vakio.LEVEYS - 1; j++)
        {
            std::cout << "--+-";
        }
        std::cout << "--|\n";
    }
    if (!ristinolla.ohi_on)
    {
        std::cout << "Vuorossa: " << MERKIT[ristinolla.vuorossa] << "\n";
    }
    
     
}



void pelaaRistinollaa(int leveys, int korkeus, int vier_lkm, int ai_moodi) {
    Ristinolla rn = Ristinolla(Vakiot(leveys, korkeus, vier_lkm), {}, ai_moodi);
    int valittu_ruutu = (leveys + 1) * korkeus / 2;

    bool painetut_painikkeet[5];

    bool peli_ohi = false;

    if (rn.ai_moodi == 0)
    {
        rn.tee_siirto(aloitussiirto(rn.vakio));
    }
    

    piirraRistinolla(rn, valittu_ruutu);
    while (!peli_ohi)
    {
        
        std::this_thread::sleep_for(std::chrono::milliseconds(40));

        for (int i = 0; i < 5; i++)
        {
            painetut_painikkeet[i] = (0x8000 & GetAsyncKeyState((unsigned char)("\x20\x25\x26\x27\x28"[i]))) != 0; // nuolet
            // painetut_painikkeet[i] = (0x8000 & GetAsyncKeyState((unsigned char)("\x20\x41\x57\x44\x53"[i]))) != 0; // awds
        }
        
        // valilyonti
        if (painetut_painikkeet[0])
        {
            // std::cout << "painettu valilyontia" << std::endl;
            rn.tee_siirto(valittu_ruutu);
            rn.voitti();
            peli_ohi = rn.ohi_on;
            if (rn.ohi_on)
            {
                piirraRistinolla(rn, -1);
                std::cout << "Voittaja on " << MERKIT[rn.voittaja] << "\n";
            }
            
            else if (!rn.ohi_on && rn.ai_moodi != -1)
            {
                piirraRistinolla(rn, -1);
                rn.tee_siirto(siirto_arvon_perusteella(rn));
                
                rn.voitti();
                peli_ohi = rn.ohi_on;
                if (rn.ohi_on)
                {
                    piirraRistinolla(rn, -1);
                    std::cout << "Voittaja on " << MERKIT[rn.voittaja] << "\n";
                }
            }
            if (!rn.ohi_on)
            {
                valittu_ruutu = rn.priorisoi_ruudut()[0];
            
                piirraRistinolla(rn, valittu_ruutu);
            }
        }
        // vasemmalle
        if (painetut_painikkeet[1])
        {
            // if (valittu_ruutu % leveys == 0)
            // {
            //     valittu_ruutu += leveys - 1;
            // }
            // else {
            //     valittu_ruutu -= 1;
            // }
            valittu_ruutu = valinta_vasemmalle(valittu_ruutu, rn);
            piirraRistinolla(rn, valittu_ruutu);
            // std::cout << "painettu vasemmalle: " << valittu_ruutu << std::endl;
        }
        // ylos
        if (painetut_painikkeet[2])
        {
            // if (valittu_ruutu < leveys)
            // {
            //     valittu_ruutu = (leveys - 1) * korkeus + valittu_ruutu % leveys;
            // }
            // else {
            //     valittu_ruutu -= leveys;
            // }
            valittu_ruutu = valinta_ylos(valittu_ruutu, rn);
            piirraRistinolla(rn, valittu_ruutu);
            // std::cout << "painettu ylos: " << valittu_ruutu << std::endl;
        }

        // oikealle
        if (painetut_painikkeet[3])
        {
            // if (valittu_ruutu % leveys == leveys - 1)
            // {
            //     valittu_ruutu -= leveys - 1;
            // }
            // else {
            //     valittu_ruutu += 1;
            // }
            valittu_ruutu = valinta_oikealle(valittu_ruutu, rn);
            piirraRistinolla(rn, valittu_ruutu);
            // std::cout << "painettu oikealle: " << valittu_ruutu << std::endl;
        }

        // alas
        if (painetut_painikkeet[4])
        {
            // if (valittu_ruutu / leveys > korkeus - 2)
            // {
            //     valittu_ruutu = valittu_ruutu % leveys;
            // }
            // else {
            //     valittu_ruutu += leveys;
            // }
            valittu_ruutu = valinta_alas(valittu_ruutu, rn);
            piirraRistinolla(rn, valittu_ruutu);
            // std::cout << "painettu alas: " << valittu_ruutu << std::endl;
        }
        
        
        // peli_ohi = true;
    }
    
}

