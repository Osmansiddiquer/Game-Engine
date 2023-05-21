#include "Engine_pch.h"
#include "UID.h"
namespace Engine
{
	//Gets time in milliseconds since epoch
	uint64_t UID::seed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	int UID::GenerateID()
	{
		int ID;
		srand(seed);
		do
		{
			ID = rand();
		} while (Already_Exists(ID));
		return ID;
	}

	bool UID::Already_Exists(int ID)
	{
		return std::find(m_alreadyGenerated.begin(), m_alreadyGenerated.end(), ID) != m_alreadyGenerated.end();
	}
}