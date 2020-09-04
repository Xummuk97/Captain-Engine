o1 = VisualObject()

function setup()
	core:loadTexture("test1", "test1.png")

	o1:setTexture("test1")
	o1:setTextureRect(0, 0, 32, 32)
end

function update(deltaTime)
end 

function draw()
	o1:draw()
end