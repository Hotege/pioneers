button = {}

function button:new(t)
    self = {
        text = t,
        normalColor = { r = 0.0, g = 0.0, b = 0.0, a = 1.0 },
        display = function()
            
        end,
    }
    return self
end