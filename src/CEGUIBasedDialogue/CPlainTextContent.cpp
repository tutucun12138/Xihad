#include "CPlainTextContent.h"
#include "CDialogueContext.h"
#include <CEGUI\TextUtils.h>
#include <CEGUI\FontManager.h>
#include <xutility>
#include <assert.h>
#include <iostream>

using namespace CEGUI;

namespace xihad { namespace dialogue
{
	CEGUI::String CPlainTextContent::WORD_FOLLOW_SYMBOL
		((CEGUI::utf8*)	"·~！@#￥%…&*（）—+{}|：”《》？-=【】、；‘，。、");

	CPlainTextContent::CPlainTextContent(const Font& font, const CEGUI::String& text )
		: mFont(&font), mText(text)
	{

	}

	unsigned CPlainTextContent::getNextWordIndex( unsigned bgn ) const
	{
		return mText.find_first_not_of(WORD_FOLLOW_SYMBOL, bgn);
	}

	void CPlainTextContent::getLetterRange( unsigned& bgnIndex, unsigned* endIndex /*= 0 */ ) const 
	{
		assert(bgnIndex < mText.length());
		// bgnIndex = bgnIndex;
		if (endIndex) 
			*endIndex = bgnIndex + 1;
	}

	void CPlainTextContent::getWordRange( unsigned& bgnIndex, unsigned* endIndex /*= 0 */ ) const 
	{
		assert(bgnIndex < mText.length());
		// bgnIndex = bgnIndex;
		if (endIndex) 
			*endIndex = getNextWordIndex(bgnIndex + 1);
	}

	ITextContent* CPlainTextContent::split( unsigned index )
	{
		String tail = mText.substr(index);
		mText = mText.substr(0, index);

		return new CPlainTextContent(*mFont, tail);
	}

	unsigned CPlainTextContent::endIndex() const 
	{
		return mText.length();
	}

	bool CPlainTextContent::empty() const 
	{
		return mText.empty();
	}

	ITextContent::SFillResult CPlainTextContent::fillHorizontal
		( unsigned widthLimit, bool allowEmpty /*= true */ ) const 
	{
		unsigned bgn = 0, end;

		SFillResult result = { 0, 0, 0 };
		result.height = (int) getHeight();

		do {
			end = getNextWordIndex(bgn);
			unsigned expanded = (int) (result.width + getWidth(bgn, end));

			// Need to contain current word
			if (expanded > widthLimit) 
				break;

			result.splitIndex = end;
			result.width = expanded;
			bgn = end;
		} while(bgn != mText.length());

		if (result.splitIndex == 0 && !allowEmpty)
		{
			result.splitIndex = std::min(1u, mText.length());
			result.width = (int) (result.width + getWidth(0, result.splitIndex));
		}

		return result;
	}

	float CPlainTextContent::getWidth( unsigned bgn, unsigned end /*= CEGUI::String::npos*/ ) const
	{
		return mFont->getTextExtent(mText.substr(bgn, end));
	}

	float CPlainTextContent::getHeight() const
	{
		return mFont->getFontHeight();
	}

	CEGUI::String CPlainTextContent::substr( unsigned bgn, unsigned end /*= CEGUI::String::npos*/ ) const
	{
		return mText.substr(bgn, end);
	}

	const CEGUI::String& CPlainTextContent::getType() const
	{
		const static CEGUI::String type("PlainText");
		return type;
	}

	CPlainTextContent::~CPlainTextContent()
	{
#ifdef _DEBUG
		std:: cout << "CPlainTextContent(" << mText << ") deleted." << std::endl;
#endif // _DEBUG
	}

}}