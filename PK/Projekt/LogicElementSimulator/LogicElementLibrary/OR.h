#pragma once
#include "Gates.h"
#include "Export.h"
namespace LE_Library {
	class OR : public Gate {
	public:
		EXPORT OR(gateType _type);
		void RefreshLogic();
		~OR();
	};
}