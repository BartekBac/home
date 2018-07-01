#pragma once
#include "Gates.h"
#include "Export.h"
namespace LE_Library {
	class XOR : public Gate {
	public:
		EXPORT XOR(gateType _type);
		void RefreshLogic();
		~XOR();
	};
}