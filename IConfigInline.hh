#pragma once

class IConfigInline
{
public:
    IConfigInline() = default;
    virtual ~IConfigInline() = default;

    virtual void handleButtonUp() = 0;
    virtual void handleButtonDown() = 0;
    virtual void fillLabel(char*, int maxLen, bool prompt) = 0;
};