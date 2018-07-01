#pragma once
#include "Gates.h"
#include "Export.h" 
namespace LE_Library {
	class NOR : public Gate {
	public:
		EXPORT NOR(gateType _type);
		void RefreshLogic();
		~NOR();
	};
}