scene_title = {}
scene_title.texture = {}
scene_title.background = nil

function scene_title.initialize()
    scene_title.background = loadImage(data.title.image, data.encrypted)
    scene_title.texture.background = scene_title.background:generateTexture()
    return scene_title
end

function scene_title.render()
    clearScene(0.0, 0.5, 0.5, 1.0)
    scene_title.texture.background:draw(-1.0, -1.0, 1.0, 1.0)
end

function scene_title.terminate()
    print("scene title terminate")
end