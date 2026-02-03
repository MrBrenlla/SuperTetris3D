#include "FPieceTemplate.h"

const TArray<FPieceTemplate>& PieceTemplate::GetDefaults()
{
	static const TArray<FPieceTemplate> Defaults =
	{
		
		// O
		{
			{ {0,0}, {1,0}, {0,1}, {1,1} },
			2, 2
		},

		// I
		{
			{ {0,0}, {1,0}, {2,0}, {3,0} },
			4, 1
		},

		// T
		{
			{ {1,0}, {0,1}, {1,1}, {2,1} },
			3, 2
		},

		// L
		{
			{ {0,0}, {0,1}, {0,2}, {1,0} },
			2,
			3
		},

		// J
		{
			{ {1,0}, {1,1}, {1,2}, {0,0} },
			2,
			3
		},

		// Z
		{
			{ {0,1}, {1,1}, {1,0}, {2,0} },
			3,
			2
		},

		// S
		{
			{ {1,1}, {2,1}, {0,0}, {1,0} },
			3,
			2
		},
	};

	return Defaults;
}