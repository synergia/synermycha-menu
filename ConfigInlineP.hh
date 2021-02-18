#pragma once

#include "IConfigInline.hh"

class ConfigInlineP : public IConfigInline
{
public:
    ConfigInlineP(int P);
    virtual ~ConfigInlineP() = default;

    void handleButtonUp() override;
    void handleButtonDown() override;
    void fillLabel(char*, int maxLen, bool prompt) override;

private:
    int mP;
};