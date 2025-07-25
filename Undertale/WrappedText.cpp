#include "stdafx.h"
#include "WrappedText.h"

WrappedText::WrappedText()
{
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(24);
}

void WrappedText::setString(const std::wstring& str)
{
    std::wstringstream currentLine;
    std::wstring finalText;

    text.setString(L"");
    for (wchar_t ch : str)
    {
        currentLine << ch;
        text.setString(currentLine.str());

        if (text.getLocalBounds().width > maxWidth && ch != L'\n')
        {
            finalText += L'\n';
            currentLine.str(L"");
            currentLine.clear();
            currentLine << ch;
        }

        finalText += ch;
    }

    text.setString(finalText);
}
