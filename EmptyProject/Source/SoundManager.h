#pragma once

namespace AK
{
namespace Sound
{

class SoundManager
{
public:
	SoundManager*	Create();
	void			Destroy();


private:
	SoundManager();
	virtual ~SoundManager();

};

};
};
//===============================================================
//	End of File
//===============================================================