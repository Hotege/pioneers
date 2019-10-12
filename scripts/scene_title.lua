scene_title = {}

function scene_title:new(nilObject)
    self = {}
    self.render = function()
        clearScene(0.0, 0.5, 0.5, 1.0)
        self.texture.background:draw(-1.0, -1.0, 1.0, 1.0)
    end
    self.release = function()
        print("scene title release")
    end
    self.background = loadImage(data.title.image, data.encrypted)
    self.texture = {}
    self.texture.background = self.background:generateTexture()
    return self
end