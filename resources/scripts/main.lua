function setup()
	core:loadTexture("test", "test1.png")

	core:addObject("Player")
end

function init(obj)
	if obj:getType() == "Player" then
		obj:setTexture("test")
		obj:setTextureRect(0, 0, 32, 32)
	end
end

function update(obj)
	if obj:getType() == "Player" then
		if core:isKeyPressed(KB_D) then
			obj:move(1.0, 0.0)
		end
	end
end

function draw(obj)
	if obj:getType() == "Player" then
		obj:drawSprite()
	end
end