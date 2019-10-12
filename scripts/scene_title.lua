scene_title = {}

function scene_title:new(nilObject)
    self = {
        texture = {
            background = loadImage(data.title.image, data.encrypted):generateTexture(),
        },
        button = {
            start = button:new(data.button.start.name),
            continue = button:new(data.button.continue.name),
            option = button:new(data.button.option.name),
            exit = button:new(data.button.exit.name),
        },
        render = function()
            clearScene(0.0, 0.5, 0.5, 1.0)
            self.texture.background:display(-1.0, -1.0, 1.0, 1.0)
            self.button.start:display()
            self.button.continue:display()
            self.button.option:display()
            self.button.exit:display()
        end,
        release = function()
            print("scene title release")
        end,
    }
    return self
end
