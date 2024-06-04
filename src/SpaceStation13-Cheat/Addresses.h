#pragma once

namespace Addresses {

	// Wallhack
	const char* Wallhack_pattern = "8B 89 1C 02 00 00";
	char Wallhack_off[] = "\x8B\x89\x1C\x02\x00\x00";
	char Wallhack_on[] = "\xB9\x56\x02\x00\x00\x90";

	// Fullbright
	const char* Fullbright_pattern = "0F B6 88 2A 02 00 00 0F BE 46 38";
	char Fullbright_off[] = "\x0F\xB6\x88\x2A\x02\x00\x00\x0F\xBE\x46\x38";
	char Fullbright_on[] = "\xB9\x01\x00\x00\x00\x66\x90\x0F\xBE\x46\x38";
}