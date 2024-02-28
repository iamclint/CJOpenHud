#include "pch.h"
#include "vectors.h"
#include "game.h"


float convert_to_cod_pitch(float pitch)
{
	if (pitch > 0)
		pitch = 360 - pitch;
	else
		pitch = fabs(pitch);
	return pitch;
}
