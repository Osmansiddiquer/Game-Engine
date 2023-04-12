#pragma once
namespace Engine
{
	class UID //Make sure the class is never instantiated
	{
	private:
		static uint64_t seed;
		static bool Already_Exists(int);
		static std::vector<int> m_alreadyGenerated;
	public:
		int GenerateID();
	protected:
		UID(){}
		virtual ~UID() = 0;
	};
	std::vector<int> UID::m_alreadyGenerated;
}