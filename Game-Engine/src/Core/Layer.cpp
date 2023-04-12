#include "Engine_pch.h"
#include "Layer.h"
namespace Engine 
{
	Layer::Layer(std::string name): m_debugName(name.substr(0, 100))
	{
		
	}
	Layer::~Layer()
	{

	}
}