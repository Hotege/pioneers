scene_title = {}

function scene_title:new(nilObject)
    self = {}
    self.render = scene_title.render
    self.release = scene_title.release
    self.background = loadImage(data.title.image, data.encrypted)
    self.texture = {}
    self.texture.background = self.background:generateTexture()
    return self
end

function scene_title:render()
    clearScene(0.0, 0.5, 0.5, 1.0)
    self.texture.background:draw(-1.0, -1.0, 1.0, 1.0)
end

function scene_title:release()
    print("scene title release")
end