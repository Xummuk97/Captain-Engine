function setup()
	core:loadTexture("test", "test1.png")

	core:spawn("Player", 1)
end

function init(obj)
	if obj:getType() == "Player" then
		obj:setTexture("test")
		obj:setTextureRect(0, 0, 32, 32)
	end
end

function update(obj)
	if obj:getType() == "Player" then
		obj:move(1.0, 0.0)
	end
end

function draw(obj)
	if obj:getType() == "Player" then
		obj:drawSprite()
	end
end