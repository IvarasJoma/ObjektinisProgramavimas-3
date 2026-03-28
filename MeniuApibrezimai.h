#ifndef MENIUAPIBREZIMAI_H
#define MENIUAPIBREZIMAI_H

#include <array>
#include <string_view>

using MeniuEilute = std::string_view;

extern const std::array<MeniuEilute, 14> PAGRINDINIS_MENIU;
extern const std::array<MeniuEilute, 7> RIKIAVIMO_MENIU;
extern const std::array<MeniuEilute, 4> RIKIAVIMO_MENIU_TIK_DIDEJANCIAI;
extern const std::array<MeniuEilute, 7> PAZANGIU_RIKIAVIMO_MENIU;
extern const std::array<MeniuEilute, 7> SILPNU_RIKIAVIMO_MENIU;
extern const std::array<MeniuEilute, 3> ISVEDIMO_MENIU;
extern const std::array<MeniuEilute, 6> ISVEDIMO_I_FAILA_MENIU;

#endif