#include "Arrows.h"
#include "Soldiers.h"

namespace Lab4{
	class Universal : public Arrows, public Soldiers{
	public:
		Universal(): Arrows(), Soldiers(){}
		int gettype(){ return 3; }
	};
}