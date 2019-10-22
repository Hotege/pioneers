button = {}

function button:new(t, s)
    nbc = { r = 0.0, g = 0.0, b = 0.0, a = 1.0 }
    nfc = { r = 1.0, g = 1.0, b = 1.0, a = 1.0 }
    hbc = { r = 0.0, g = 0.0, b = 0.0, a = 1.0 }
    hfc = { r = 1.0, g = 1.0, b = 1.0, a = 1.0 }
    abc = { r = 0.0, g = 0.0, b = 0.0, a = 1.0 }
    afc = { r = 1.0, g = 1.0, b = 1.0, a = 1.0 }
    self = {
        text = t,
        size = s,
        normalBackColor = nbc,
        normalFontColor = nfc,
        hoverBackColor = hbc,
        hoverFontColor = hfc,
        activeBackColor = abc,
        activeFontColor = afc,
        textureNormal = generateTextTexture(t, s, nbc, nfc),
        textureHover = generateTextTexture(t, s, hbc, hfc),
        textureActive = generateTextTexture(t, s, abc, afc),
        display = function()
            
        end,
    }
    return self
end