#pragma once
#include <Dialogue\CBaseTickMethod.hpp>

namespace xihad { namespace dialogue
{
	class IDialogue;
	class CTickByWord : public CBaseTickMethod
	{
	public:
		explicit CTickByWord(IDialogue& target, float standardCycle, float initSpeed = 1.0f);

		virtual ~CTickByWord();

	protected:
		virtual bool onTick() override;

	private:
		IDialogue& mTarget;
	};
}}
