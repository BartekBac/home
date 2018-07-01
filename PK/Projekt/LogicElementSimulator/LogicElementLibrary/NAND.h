#pragma once
#include "Gates.h"
#include "Export.h"
namespace LE_Library {
	class NAND : public Gate {
	public:
		EXPORT NAND(gateType _type);
		void RefreshLogic();
		~NAND();
	};
}