#pragma once
#include "Gates.h"
#include "Export.h"
namespace LE_Library {
	class AND : public Gate {
	public:
		EXPORT AND(gateType _type);
		void RefreshLogic();
		~AND();
	};
}